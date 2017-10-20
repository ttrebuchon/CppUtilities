#pragma once

#include "../Node.h"


namespace QUtils { namespace Graphs {
namespace DependencyGraph_NS {
	
	
	
	
	class Node : public Graphs::Node, public Graphs::BackLinked
	{
		public:
		typedef signed long long Priority_t;
		
		private:
		Priority_t priority;
		
		
		
		protected:
		
		
		public:
		constexpr static NodeDetails Details = Graphs::Node::Details | Graphs::BackLinked::Details;
		
		Node(/*const Priority_t priority*/) : Graphs::Node(Details), Graphs::BackLinked()/*, priority(priority)*/
		{
			
		}
		
		inline Priority_t nodePriority() const
		{
			return priority;
		}
	};
}
}
}