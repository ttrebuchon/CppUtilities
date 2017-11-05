#pragma once
#include <memory>
#include <vector>
#include <set>
#include "EdgeCollection.h"
#include "GraphObject.h"

namespace QUtils { namespace Graphs {
	
	template <class T = void, class Wgt_t = void>
	class Node : public std::enable_shared_from_this<Node<T, Wgt_t>>, public GraphObject
	{
		private:
		typedef std::weak_ptr<Node<T, Wgt_t>> Node_ptr;
		typedef std::shared_ptr<Node<T, Wgt_t>> Node_sptr;
		
		typedef Node<T, Wgt_t> this_t;
		
		protected:
		
		
		public:
		typedef Node_sptr ptr_t;
		typedef Node_ptr wptr_t;
		
		T value;
		EdgeCollection<Node<T, Wgt_t>, Wgt_t> in;
		EdgeCollection<Node<T, Wgt_t>, Wgt_t> out;
		
		Node(const T& t) : value(t), in(), out()
		{}
		
		Node() : value(), in(), out()
		{}
		
		
		static inline Node_sptr Create(const T& t)
		{ return Node_sptr(new this_t(t)); }
		static inline Node_sptr Create()
		{ return Node_sptr(new this_t()); }
		
		std::set<const Node_sptr> getDescendants() const;
		std::set<Node_sptr> getDescendants();
		void getDescendants(std::set<const Node_sptr>&) const;
		void getDescendants(std::set<Node_sptr>&);
	};
	
	template <class Wgt_t>
	class Node<void, Wgt_t> : public std::enable_shared_from_this<Node<void, Wgt_t>>, public GraphObject
	{
		private:
		typedef std::weak_ptr<Node<void, Wgt_t>> Node_ptr;
		typedef std::shared_ptr<Node<void, Wgt_t>> Node_sptr;
		
		typedef Node<void, Wgt_t> this_t;
		
		protected:
		
		public:
		typedef Node_sptr ptr_t;
		typedef Node_ptr wptr_t;
		
		EdgeCollection<Node<void, Wgt_t>, Wgt_t> in;
		EdgeCollection<Node<void, Wgt_t>, Wgt_t> out;
		
		
		Node() {}
		
		
		static inline Node_sptr Create()
		{ return Node_sptr(new this_t()); }
		
		std::set<const Node_sptr> getDescendants() const;
		std::set<Node_sptr> getDescendants();
		void getDescendants(std::set<const Node_sptr>&) const;
		void getDescendants(std::set<Node_sptr>&);
	};
}
}

#include "Node.hpp"
#include "Node_void.hpp"