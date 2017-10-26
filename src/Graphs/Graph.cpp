#include <QUtils/Graphs/Graph.h>
#include <QUtils/Exception/NotImplemented.h>
#include <map>

namespace QUtils { namespace Graphs {
	
	Graph::Graph(const size_t rootCount) : roots()
	{
		roots.reserve(rootCount);
	}
	
	std::set<Graph::Node_ptr> Graph::getAll() const
	{
		std::set<Node_ptr> nodes;
		getAll(nodes);
		return nodes;
	}
	
	void Graph::getAll(std::set<Node_ptr>& nodes) const
	{
		for (const auto& root : roots)
		{
			nodes.insert(root);
			root->getAllChildNodes(nodes);
		}
	}
	
	Graph::Node_ptr Graph::removeRoot(const Node_ptr node)
	{
		auto it = std::find(roots.begin(), roots.end(), node);
		if (it == roots.end())
		{
			throw std::out_of_range("Graph roots");
		}
		
		auto ptr = *it;
		roots.erase(it);
		
		return ptr;
	}
	
	Graph::Node_ptr Graph::removeRootAt(const size_t index)
	{
		if (index >= roots.size())
		{
			throw std::out_of_range("BackLinked parents");
		}
		auto it = roots.begin() + index;
		
		auto ptr = *it;
		roots.erase(it);
		
		return ptr;
	}
	
	std::shared_ptr<Graph> Graph::clone() const
	{
		auto copy = std::make_shared<Graph>(roots.size());
		std::map<Node_ptr, Node_ptr> nodeMap;
		//std::map<Edge_ptr, Edge_ptr> edgeMap;
		for (auto i = 0; i < roots.size(); ++i)
		{
			if (roots.at(i) != NULL)
			{
				//copy->roots.at(i) = this->roots.at(i)->clone(nodeMap/*, edgeMap*/);
				copy->roots.push_back(this->roots.at(i)->clone(nodeMap/*, edgeMap*/));
			}
			else
			{
				throw std::exception();
			}
		}
		
		return copy;
	}
}
}