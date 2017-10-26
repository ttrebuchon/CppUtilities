#pragma once

#include "Helpers/CheckFlags.h"
#include "Errors.h"

#include <memory>

namespace QUtils { namespace Graphs {
	
	class Node;
	
	class Edge : public std::enable_shared_from_this<Edge>
	{
		private:
		
		protected:
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::shared_ptr<Edge> Edge_ptr;
		typedef std::weak_ptr<Node> Node_wptr;
		typedef std::weak_ptr<Edge> Edge_wptr;
		
		virtual void push_back_end(const std::size_t end, Node_ptr node) = 0;
		
		
		public:
		Edge();
		
		virtual std::size_t endCount() const = 0;
		
		template <class NodeType>
		inline std::enable_if_t<std::is_base_of<Node, NodeType>::value, void> addToEnd(const std::size_t end, std::shared_ptr<NodeType> node, bool checkConnections = true)
		{
			std::shared_ptr<const NodeType> node_c = node;
			
			if (!node)
			{
				throw NullNodeException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Cannot add NULL Node to Edge");
			}
			
			this->push_back_end(end, node);
			if (checkConnections && NodeHasFlag<NodeDetails::BackLinked, NodeType>::Check(node_c))
			{
				auto bl = std::dynamic_pointer_cast<BackLinked>(node);
				if (bl)
				{
					bl->addParent(this->shared_from_this());
				}
			}
		}
		
		virtual Node_ptr getEnd(const std::size_t) const = 0;
		
		
	};
}
}