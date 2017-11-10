#pragma once
#include <memory>
#include "GraphObject.h"


namespace QUtils { namespace Graphs {
	
	template <class Node_t, class Wgt_t = void>
	class Edge;
	
	template <class Node_t>
	class Edge<Node_t, void> : public GraphObject
	{
		private:
		
		protected:
		
		public:
		std::weak_ptr<Node_t> in;
		std::weak_ptr<Node_t> out;
	};
	
	template <class Node_t, class Wgt_t>
	class Edge : public Edge<Node_t, void>
	{
		private:
		
		protected:
		
		public:
		Wgt_t value;
	};
}
}