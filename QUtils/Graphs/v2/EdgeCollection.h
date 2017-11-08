#pragma once

#include "Edges_t.h"
#include <memory>
#include <vector>
#include "Edge.h"

namespace QUtils { namespace Graphs {
	
	namespace Helpers
	{
		template <class Node_t, class Wgt_t>
		std::weak_ptr<Node_t>& node(Edge<Node_t, Wgt_t>& t)
		{
			return t.out;
		}
	}
	
	template <class Node_t, class Wgt_t = void>
	class EdgeCollection : 
	public std::vector<Edge<Node_t, Wgt_t>>,
	public Edges_t<Node_t>
	{
		private:
		typedef Edge<Node_t, Wgt_t> Edge_t;
		
		typedef std::weak_ptr<Node_t> Node_ptr;
		protected:
		Node_ptr owner;
		
		public:
		EdgeCollection(Node_ptr owner) : std::vector<Edge_t>(), owner(owner)
		{
			
		}
		
		EdgeCollection() : EdgeCollection(Node_ptr())
		{
			
		}
		
		virtual Node_ptr& node(const size_t index)
		{
			return (*this)[index].out;
		}
		
		const Node_ptr& node(const size_t index) const
		{
			return (*const_cast<EdgeCollection<Node_t, Wgt_t>*>(this))[index].out;
		}
		
		void push_back(const Node_ptr node)
		{
			std::vector<Edge_t>::push_back(Edge_t());
			this->back().out = node;
			this->back().in = owner;
		}
		
		void push_back(nullptr_t)
		{
			std::vector<Edge_t>::push_back(Edge_t());
			this->back().out = Node_ptr();
			this->back().in = owner;
		}
		
		void setOwner(Node_ptr owner)
		{
			this->owner = owner;
		}
	};
}
}