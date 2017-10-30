#include <QUtils/Graphs/BackLinkedNode.h>
#include <QUtils/Graphs/Node.h>

#include <iostream>

namespace QUtils { namespace Graphs {
	
	BackLinked::BackLinked(const size_t parentCount) : parents(parentCount)
	{
		
	}
	
	BackLinked::BackLinked(NodeDetails& details, const size_t parentCount) : BackLinked(parentCount)
	{
		details &= BackLinked::Details;
	}
	
	BackLinked::BackLinked(NodeDetails& details) : BackLinked(details, 0)
	{
		
	}
	
	BackLinked::BackLinked() : BackLinked(0)
	{
		
	}
	
	BackLinked::~BackLinked()
	{
		
	}
	
	
	
	
	typename BackLinked::Node_wptr BackLinked::removeParentAt(const size_t index)
	{
		if (index >= parents.size())
		{
			throw std::out_of_range("BackLinked parents");
		}
		auto it = parents.begin() + index;
		
		auto ptr = *it;
		parents.erase(it);
		
		return ptr;
	}
	
	
	typename BackLinked::Node_wptr BackLinked::removeParent(const Node_ptr node)
	{
		auto predicate = [node](auto wk_ptr)
		{
			return (wk_ptr.lock() == node);
		};
		auto it = std::find_if(parents.begin(), parents.end(), predicate);
		if (it == parents.end())
		{
			throw std::out_of_range("BackLinked parents");
		}
		
		auto ptr = *it;
		parents.erase(it);
		
		return ptr;
	}
	
	std::set<std::shared_ptr<Node>> BackLinked::getAllParents() const
	{
		std::set<Node_ptr> nodes;
		getAllParents(nodes);
		return nodes;
	}
	
	void BackLinked::getAllParents(std::set<Node_ptr>& nodes) const
	{
		for (auto wParent : parents)
		{
			auto parent = wParent.lock();
			if (parent != NULL)
			{
				nodes.insert(parent);
				if (parent->getDetails() && NodeDetails::BackLinked)
				{
					std::dynamic_pointer_cast<BackLinked>(parent)->getAllParents(nodes);
				}
			}
		}
	}
}
}