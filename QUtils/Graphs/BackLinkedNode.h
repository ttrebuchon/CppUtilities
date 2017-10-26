#pragma once
#include <vector>
#include <memory>
#include <set>
#include "NodeDetails.h"

#include "Errors.h"

namespace QUtils { namespace Graphs {
	
	class Node;
	
	class BackLinked : virtual public std::enable_shared_from_this<Node>
	{
		protected:
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::weak_ptr<Node> Node_wptr;
		typedef std::vector<Node_wptr> Nodes_wt;
		Nodes_wt parents;
		
		BackLinked(const size_t parentCount);
		BackLinked(NodeDetails&, const size_t parentCount);
		BackLinked(NodeDetails&);
		BackLinked();
		
		
		public:
		constexpr static NodeDetails Details = NodeDetails::BackLinked;
		
		
		
		template <class NodeType>
		inline std::enable_if_t<std::is_base_of<Node, NodeType>::value, void> addParent(std::shared_ptr<NodeType> node)
		{
			if (!node)
			{
				throw NullNodeException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Cannot add NULL child to Node");
			}
			parents.push_back(node);
		}
		
		inline const Nodes_wt& getParents() const
		{
			return parents;
		}
		
		
		
		Node_wptr removeParentAt(const size_t index);
		
		Node_wptr removeParent(const Node_ptr node);
		
		std::set<Node_ptr> getAllParents() const;
		void getAllParents(std::set<Node_ptr>&) const;
		
	};
}
}