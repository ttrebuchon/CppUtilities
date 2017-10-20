#include <QUtils/Graph/Node.h>

namespace QUtils { namespace Graphs {
	
	Node::Node(NodeDetails details) : details(details | Node::Details)
	{
		
	}
	
	
	Node::Node() : Node(NodeDetails::None)
	{
		
	}
}
}