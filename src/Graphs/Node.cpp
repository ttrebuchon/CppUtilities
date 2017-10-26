#include <QUtils/Graphs/Node.h>
#include <QUtils/Graphs/SimpleEdge.h>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Graphs {
	
	Node::Node(NodeDetails details, const size_t childCount) : details(details | Node::Details), children(childCount)
	{
	}
	
	Node::Node(NodeDetails details) : Node(details, 0)
	{
		
	}
	
	Node::Node(const size_t childCount) : Node(NodeDetails::None, childCount)
	{
	}
	
	Node::Node() : Node(0)
	{
		
	}
	
	Node::~Node()
	{
		
	}
	
	
	
	
	void Node::push_back_child(Node_ptr ptr)
	{
		//children.push(std::make_shared<SimpleEdge>(shared_from_this(), ptr));
		children.push_back(ptr);
	}
	
	/*void Node::push_back_edge(Edge_ptr ptr)
	{
		children.push(ptr);
	}*/
	
	
	
	
	
	
	
	
	
	
	
	
	typename Node::Node_ptr Node::removeChildAt(const size_t index, bool checkConnections)
	{
		if (index >= children.size())
		{
			throw std::out_of_range("Node children");
		}
		auto it = children.begin() + index;
		
		auto ptr = *it;
		children.erase(it);
		throw NotImp();
		
		
		return ptr;
	}
	
	
	typename Node::Node_ptr Node::removeChild(const Node_ptr node, bool checkConnections)
	{
		throw NotImp();
		/*
		auto it = std::find(children.begin(), children.end(), node);
		if (it == children.end())
		{
			throw std::out_of_range("Node children");
		}
		
		auto ptr = *it;
		children.erase(it);
		
		
		if (checkConnections && NodeHasFlag<NodeDetails::BackLinked, Node>::Check(ptr))
		{
			auto bl = std::dynamic_pointer_cast<BackLinked>(ptr);
			if (bl)
			{
				bl->removeParent(this->shared_from_this());
			}
		}
		
		return ptr;*/
	}
	
	std::set<Node::Node_ptr> Node::getAllChildNodes() const
	{
		std::set<Node_ptr> nodes;
		getAllChildNodes(nodes);
		return nodes;
	}
	
	void Node::getAllChildNodes(std::set<Node_ptr>& nodes) const
	{
		/*for (const auto& edge : children)
		{
			for (int i = 1; i < edge->endCount(); ++i)
			{
				auto n = edge->getEnd(i);
				if (n != NULL && nodes.count(n) == 0)
				{
					nodes.insert(n);
					n->getAllChildNodes(nodes);
				}
				
			}
		}*/
		
		for (auto child : children)
		{
			if (child != NULL && nodes.count(child) <= 0)
			{
			nodes.insert(child);
			child->getAllChildNodes(nodes);
			}
		}
	}
	
	
	
	std::set<Node::Node_ptr> Node::getAllChildNodesAndSelf()
	{
		std::set<Node_ptr> nodes;
		getAllChildNodesAndSelf(nodes);
		return nodes;
	}
	
	void Node::getAllChildNodesAndSelf(std::set<Node_ptr>& nodes)
	{
		nodes.insert(shared_from_this());
		getAllChildNodes(nodes);
	}
	
	void Node::replaceAllOfNode(const std::shared_ptr<Node> target, const std::shared_ptr<Node> replacement, std::set<std::shared_ptr<Node>>& alreadyChecked)
	{
		
		for (auto& child : children)
		{
			if (child == target)
			{
				child = replacement;
			}
			
			
			if (alreadyChecked.count(child) <= 0)
			{
				alreadyChecked.insert(child);
				if (child == NULL)
				{
					continue;
				}
				child->replaceAllOfNode(target, replacement, alreadyChecked);
			}
		}
	}
	
	void Node::replaceAllOfNode(const std::shared_ptr<Node> target, const std::shared_ptr<Node> replacement)
	{
		std::set<std::shared_ptr<Node>> nodes;
		replaceAllOfNode(target, replacement, nodes);
	}
	
	
	std::size_t Node::childSize() const
	{
		return children.size();
	}
	
	std::size_t Node::childNodeSize() const
	{
		/*std::size_t s = 0;
		for (const auto& edge : children)
		{
			s += (edge->endCount()-1);
		}
		return s;*/
		return children.size();
	}
	
	std::shared_ptr<Node> Node::clone(std::map<Node_ptr, Node_ptr>& nodes) const
	{
		auto shared = const_cast<Node*>(this)->shared_from_this();
		if (nodes.count(shared) > 0)
		{
			return nodes.at(shared);
		}
		
		auto copy = std::make_shared<Node>();
		
		nodes[shared] = copy;
		
		
		for (const auto child : children)
		{
			auto cCopy = child->clone(nodes);
			copy->push_back_child(cCopy);
		}
		
		
		
		return copy;
		
		throw std::exception();
	}
}
}