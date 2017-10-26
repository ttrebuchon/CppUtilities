#pragma once

#include <memory>
#include <set>
#include "Node.h"
//#include "NodeContainer.h"
//#include <QUtils/Types/TryMakeShared.h>


namespace QUtils { namespace Graphs {
	
	
	class Graph
	{
		private:
		
		protected:
		typedef std::shared_ptr<Node> Node_ptr;
		typedef std::shared_ptr<Edge> Edge_ptr;
		typedef std::set<Node_ptr> Nodes_t;
		typedef std::set<Edge_ptr> Edges_t;
		typedef std::vector<Node_ptr> NodeList_t;
		
		NodeList_t roots;
		
		public:
		
		Graph(const size_t = 1);
		
		template <class NodeType>
		std::enable_if_t<std::is_base_of<Node, NodeType>::value, void> addRoot(std::shared_ptr<NodeType> node)
		{
			roots.push_back(node);
		}
		
		
		Nodes_t getAll() const;
		void getAll(Nodes_t&) const;
		
		Node_ptr removeRoot(const Node_ptr);
		Node_ptr removeRootAt(const size_t);
		
		virtual std::shared_ptr<Graph> clone() const;
	};
	
	
}
}