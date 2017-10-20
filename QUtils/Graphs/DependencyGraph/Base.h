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
		typedef typename Node::Priority_t Priority_t;
		
		
		
		protected:
		
		typedef Node BaseNode;
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::shared_ptr<const Node> Node_ptr_c;
		
		
		std::deque<std::shared_ptr<Node>> roots;
		std::shared_timed_mutex roots_m;
		typedef std::lock_guard<decltype(roots_m)> roots_lock_t;
		
		virtual std::shared_ptr<Node> createNode(const Priority_t)
		{
			throw NotImp();
		}
		
		std::shared_ptr<Node> getNewNode();
		
		void push_back(const Node_ptr)
		{
			throw NotImp();
		}
		
		public:
		
		
		
		
		
		std::size_t ready() const
		{
			return roots.size();
			throw NotImp();
		}
		
	};
	
	
	
	
}
}
}