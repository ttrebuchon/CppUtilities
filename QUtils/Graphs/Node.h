#pragma once

#include "NodeDetails.h"
#include "EdgeCollection.h"

#include <vector>
#include <memory>
#include <set>
#include <map>
#include "Helpers/CheckFlags.h"
#include "Errors.h"

namespace QUtils { namespace Graphs {
	
	
	class BackLinked;
	class Edge;
	
	class Node : virtual public std::enable_shared_from_this<Node>
	{
		private:
		NodeDetails details;
		
		
		
		protected:
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::shared_ptr<Edge> Edge_ptr;
		typedef std::vector<Node_ptr> Nodes_t;
		//typedef std::vector<Edge_ptr> Edges_t;
		
		typedef Nodes_t Children_t;
		//typedef EdgeCollection Children_t;
		//typedef NodeCollection Children_t;
		Children_t children;
		
		Node(NodeDetails, const size_t childCount);
		Node(NodeDetails);
		
		virtual void push_back_child(Node_ptr);
		//virtual void push_back_edge(Edge_ptr);
		
		public:
		constexpr static NodeDetails Details = NodeDetails::None;
		
		
		Node(const size_t childCount);
		Node();
		
		virtual ~Node();
		
		
		template <class NodeType>
		inline std::enable_if_t<std::is_base_of<Node, NodeType>::value, void> addChild(std::shared_ptr<NodeType> node, bool checkConnections = true)
		{
			std::shared_ptr<const NodeType> node_c = node;
			
			if (!node)
			{
				throw NullNodeException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Cannot add NULL child to Node");
			}
			
			this->push_back_child(node);
			if (checkConnections && NodeHasFlag<NodeDetails::BackLinked, NodeType>::Check(node_c))
			{
				auto bl = std::dynamic_pointer_cast<BackLinked>(node);
				if (bl)
				{
					bl->addParent(this->shared_from_this());
				}
			}
		}
		
		
		
		inline NodeDetails getDetails() const
		{ return details; }
		
		inline const Children_t& getChildren() const
		{ return children; }
		
		Node_ptr removeChildAt(const size_t index, bool checkConnections = true);
		
		Node_ptr removeChild(const Node_ptr node, bool checkConnections = true);
		
		Node_ptr removeChild(const Edge_ptr node, bool checkConnections = true);
		
		
		
		inline auto cbegin() const
		{
			return children.cbegin();
		}
		
		/*inline auto begin()
		{
			return children.begin();
		}*/
		
		inline auto cend() const
		{
			return children.cend();
		}
		
		/*inline auto end()
		{
			return children.end();
		}*/
		
		std::set<Node_ptr> getAllChildNodes() const;
		void getAllChildNodes(std::set<Node_ptr>&) const;
		
		std::set<Node_ptr> getAllChildNodesAndSelf();
		void getAllChildNodesAndSelf(std::set<Node_ptr>&);
		void replaceAllOfNode(const Node_ptr target, const Node_ptr replacement, std::set<Node_ptr>& alreadyChecked);
		void replaceAllOfNode(const Node_ptr target, const Node_ptr replacement);
		
		std::size_t childSize() const;
		std::size_t childNodeSize() const;
		
		
		virtual Node_ptr clone(std::map<Node_ptr, Node_ptr>&) const;
	};
	
	
}
}

#include "BacklinkedNode.h"