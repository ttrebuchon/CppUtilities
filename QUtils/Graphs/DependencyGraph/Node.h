#pragma once

#include "../Node.h"
#include <mutex>


namespace QUtils { namespace Graphs {
namespace DependencyGraph_NS {
	
	
	
	
	/*class Node : public Graphs::Node<
	{
		public:
		typedef long double Weight_t;
		
		private:
		Weight_t wgt;
		
		
		
		protected:
		std::mutex mutex;
		
		
		public:
		constexpr static NodeDetails Details = Graphs::Node::Details | Graphs::BackLinked::Details;
		
		Node() : Graphs::Node(Details), Graphs::BackLinked()
		{
			
		}
		
		inline Weight_t nodeWeight() const
		{
			return wgt;
		}
	};*/
	
	template <class T>
	using Node = Graphs::Node<T, long double>;
}
}
}