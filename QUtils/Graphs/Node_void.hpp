#pragma once


#include "Node.h"
#include "Node.hpp"

namespace QUtils { namespace Graphs {
	
	template <class Wgt_t>
	std::set<const typename Node<void, Wgt_t>::Node_sptr> Node<void, Wgt_t>::getDescendants() const
	{
		std::set<const Node_sptr> nodes;
		getDescendants(nodes);
		return nodes;
	}
	
	template <class Wgt_t>
	std::set<typename Node<void, Wgt_t>::Node_sptr> Node<void, Wgt_t>::getDescendants()
	{
		std::set<Node_sptr> nodes;
		getDescendants(nodes);
		return nodes;
	}
	
	template <class Wgt_t>
	void Node<void, Wgt_t>::getDescendants(std::set<const Node_sptr>& nodes) const
	{
		GET_DESCS
	}
	
	template <class Wgt_t>
	void Node<void, Wgt_t>::getDescendants(std::set<Node_sptr>& nodes)
	{
		GET_DESCS
	}
	
	
	
	
	
	
	
	
	
}
}