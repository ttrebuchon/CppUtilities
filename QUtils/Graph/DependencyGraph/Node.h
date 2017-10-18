#pragma once

#include "../Node.h"


namespace QUtils { namespace Graph {
namespace DependencyGraph_NS {
	
	
	template <class = void>
	class Node;
	
	
	
	
	template <>
	class Node<void> : public Graph::Node, public Graph::BackLinked
	{
		public:
		typedef signed long long Priority_t;
		
		private:
		Priority_t priority;
		
		
		
		protected:
		
		
		public:
		constexpr static NodeDetails Details = Graph::Node::Details | Graph::BackLinked::Details;
		
		Node(const Priority_t priority) : Graph::Node(Details), Graph::BackLinked(), priority(priority)
		{
			
		}
		
		inline Priority_t nodePriority() const
		{
			return priority;
		}
	};
	
	
	
	
	
	template <class T>
	class Node : public Node<void>
	{
		private:
		
		protected:
		T element;
		
		public:
		Node(const Priority_t priority, const T elem) : Node<void>(priority), element(elem)
		{
			
		}
		
		Node(const Priority_t priority) : Node<T>(priority, T())
		{
			
		}
		
		inline const T& get() const
		{
			return element;
		}
		
		inline void set(const T& t)
		{
			element = t;
		}
	};
}
}
}