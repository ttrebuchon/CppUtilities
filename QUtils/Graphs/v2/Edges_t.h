#pragma once
#include <memory>

namespace QUtils { namespace Graphs {
	
	template <class Node_t>
	class Edges_t
	{
		public:
		virtual std::weak_ptr<Node_t>& node(const size_t index) = 0;
		
		virtual const std::weak_ptr<Node_t>& node(const size_t index) const = 0;
	};
}
}