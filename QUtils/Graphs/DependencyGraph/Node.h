#pragma once

#include "../Node.h"
#include <mutex>


namespace QUtils { namespace Graphs {
namespace DependencyGraph_NS {
	
	
	
	
	class Node : public Graphs::Node, public Graphs::BackLinked
	{
		public:
		typedef long double Weight_t;
		
		private:
		Weight_t wgt;
		
		
		
		protected:
		std::mutex mutex;
		
		
		public:
		constexpr static NodeDetails Details = Graphs::Node::Details | Graphs::BackLinked::Details;
		
		Node(/*const Wight_t wgt*/) : Graphs::Node(Details), Graphs::BackLinked()/*, wgt(wgt)*/
		{
			
		}
		
		inline Weight_t nodeWeight() const
		{
			return wgt;
		}
	};
}
}
}