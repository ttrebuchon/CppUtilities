#include <QUtils/Graphs/SimpleEdge.h>

namespace QUtils { namespace Graphs {
	
	SimpleEdge::SimpleEdge(Node_ptr end0, Node_ptr end1) : Edge(), end0(end0), end1(end1)
	{
		
	}
	
	SimpleEdge::SimpleEdge(Node_ptr end0) : SimpleEdge(end0, NULL)
	{
		
	}
	
	SimpleEdge::SimpleEdge() : SimpleEdge(NULL, NULL)
	{
		
	}
	
	void SimpleEdge::push_back_end(const std::size_t end, Node_ptr node)
	{
		switch (end)
		{
			case 0:
			end0 = node;
			break;
			
			case 1:
			end1 = node;
			break;
			
			default:
			//TODO
			throw std::exception();
		}
	}
}
}