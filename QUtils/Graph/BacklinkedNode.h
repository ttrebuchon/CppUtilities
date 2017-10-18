#pragma once
#include <vector>
#include <memory>
#include "NodeDetails.h"

namespace QUtils { namespace Graph {
	
	class Node;
	
	class BackLinked
	{
		protected:
		std::vector<std::shared_ptr<Node>> in;
		
		
		BackLinked() : in()
		{}
		
		BackLinked(NodeDetails& details) : BackLinked()
		{
			details &= NodeDetails::BackLinked;
		}
		
		
		public:
		constexpr static NodeDetails Details = NodeDetails::BackLinked;
		
	};
}
}