#pragma once


#include "Node.h"

namespace QUtils { namespace Graphs {
	
	template <class T, class Wgt_t>
	std::set<const typename Node<T, Wgt_t>::Node_sptr> Node<T, Wgt_t>::getDescendants() const
	{
		std::set<const Node_sptr> nodes;
		getDescendants(nodes);
		return nodes;
	}
	
	template <class T, class Wgt_t>
	std::set<typename Node<T, Wgt_t>::Node_sptr> Node<T, Wgt_t>::getDescendants()
	{
		std::set<Node_sptr> nodes;
		getDescendants(nodes);
		return nodes;
	}
	
	template <class T, class Wgt_t>
	void Node<T, Wgt_t>::getDescendants(std::set<const Node_sptr>& nodes) const
	{
		for (const auto& o : out)
		{
			auto locked = o.out.lock();
			if (locked)
			{
				if (nodes.count(locked) <= 0)
				{
					nodes.insert(locked);
					locked->getDescendants(nodes);
				}
			}
		}
	}
	
	template <class T, class Wgt_t>
	void Node<T, Wgt_t>::getDescendants(std::set<Node_sptr>& nodes)
	{
		for (auto& o : out)
		{
			auto locked = o.out.lock();
			if (locked)
			{
				if (nodes.count(locked) <= 0)
				{
					nodes.insert(locked);
					locked->getDescendants(nodes);
				}
			}
		}
	}
	
	
	
	
	
	
	
	
	
}
}