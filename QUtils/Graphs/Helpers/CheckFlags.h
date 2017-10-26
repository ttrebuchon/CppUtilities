#pragma once

#include "../NodeDetails.h"
#include "../BackLinkedNode.h"
#include <type_traits>
#include <memory>

namespace QUtils { namespace Graphs {
	
	class Node;
	
	namespace CheckBackLinked_Helper
	{
		
	}
	
	
	template <NodeDetails flag, class NodeType>
	struct NodeHasFlag
	{
		constexpr static bool Check(const std::shared_ptr<const NodeType> node)
		{
			static_assert(std::is_base_of<Node, NodeType>::value, "Type must be a Node");
			
			return (node->getDetails() && flag);
		}
	};
	
	
	
	
	template <class NodeType>
	struct NodeHasFlag<NodeDetails::BackLinked, NodeType>
	{
		constexpr static bool Check(const std::shared_ptr<const NodeType> node)
		{
			static_assert(std::is_base_of<Node, NodeType>::value, "Type must be a Node");
			
			if (std::is_base_of<BackLinked, NodeType>::value)
			{
				return true;
			}
			
			return (node->getDetails() && NodeDetails::BackLinked);
		}
	};
	
	/*template <class NodeType>
	constexpr bool nodeHasFlag<NodeDetails::BackLinked, NodeType>(const std::shared_ptr<const NodeType> node)
	{
		static_assert(std::is_base_of<Node, NodeType>::value, "Type must be a Node");
		
		if (std::is_base_of<BackLinked, NodeType>::value)
		{
			return true;
		}
		
		return (node->getDetails() && NodeDetails::BackLinked);
		
	}*/
	
}
}