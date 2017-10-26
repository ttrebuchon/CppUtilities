#pragma once


#include "../Graph.h"
#include "Node.h"

#include <atomic>
#include <deque>
#include <memory>
#include <shared_mutex>

#include <QUtils/Exception/NotImplemented.h>


namespace QUtils { namespace Graphs {
namespace DependencyGraph_NS {
	
	class DependencyGraph_Base : public Graphs::Graph
	{
		public:
		typedef typename Node::Weight_t Weight_t;
		
		
		
		protected:
		
		typedef Node BaseNode;
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::shared_ptr<const Node> Node_ptr_c;
		
		DependencyGraph_Base();
		
		
		std::deque<std::shared_ptr<Node>> roots;
		mutable std::shared_timed_mutex roots_m;
		typedef std::lock_guard<decltype(roots_m)> roots_lock;
		typedef std::shared_lock<decltype(roots_m)> roots_shared_lock;
		
		virtual std::shared_ptr<Node> createNode(const Weight_t) const = 0;
		
		std::shared_ptr<Node> getNewNode();
		
		void push_back(const Node_ptr);
		
		std::shared_ptr<Node> getNext();
		
		public:
		
		
		
		
		
		std::size_t ready() const;
		
	};
	
	
	
	
}
}
}