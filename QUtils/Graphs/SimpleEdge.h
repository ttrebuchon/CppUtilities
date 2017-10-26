#pragma once

#include "Edge.h"

namespace QUtils { namespace Graphs {
	
	class SimpleEdge : public Edge
	{
		private:
		
		protected:
		Node_wptr end0;
		Node_ptr end1;
		
		virtual void push_back_end(const std::size_t end, Node_ptr node) override;
		
		public:
		SimpleEdge(Node_ptr, Node_ptr);
		SimpleEdge(Node_ptr);
		SimpleEdge();
		
		inline std::size_t endCount() const override { return 2; }
		
		
		inline Node_ptr getEnd(const std::size_t end) const override
		{
			if (end == 0)
			{
				return end0.lock();
			}
			else if (end == 1)
			{
				return end1;
			}
			return NULL;
		}
		
		inline Node_wptr& parent()
		{
			return end0;
		}
		
		inline const Node_wptr& parent() const
		{
			return end0;
		}
		
		inline Node_ptr& child()
		{
			return end1;
		}
		
		inline const Node_ptr& child() const
		{
			return end1;
		}
	};
}
}