#pragma once

#include "NodeDetails.h"

#include <vector>
#include <memory>

namespace QUtils { namespace Graph {
	
	class Node
	{
		private:
		NodeDetails details;
		
		protected:
		std::vector<std::shared_ptr<Node>> out;
		
		Node(NodeDetails);
		
		public:
		constexpr static NodeDetails Details = NodeDetails::None;
		
		
		Node();
	};
	
	
}
}

#include "BacklinkedNode.h"