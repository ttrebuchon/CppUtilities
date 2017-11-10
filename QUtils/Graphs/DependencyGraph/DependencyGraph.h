#pragma once

#include "Node.h"
#include "../Graph.h"


namespace QUtils { namespace Graphs {
	
	template <class T = void>
	class DependencyGraph : public Graph<T, long double, Graphs::Node>
	{
		private:
		typedef Graph<T, long double, Graphs::Node> Base;
		
		
		public:
		
		/*class Node_t : public DependencyGraph_NS::Node
		{
			protected:
			T item;
			public:
			
			Node_t(const T t) : DependencyGraph_NS::Node(), item(t)
			{
				
			}
		};*/
		
		typedef Graphs::Node<T, long double> Node_t;
		typedef std::shared_ptr<Node_t> Node_ptr;
		
		
		protected:
		
		virtual Node_ptr createNode(const long double) const
		{
			throw NotImp();
		}
		
		public:
		DependencyGraph() : Base()
		{
			
		}
		
		
		std::shared_ptr<const Node_t> push_back(const T t)
		{
			throw NotImp();
			/*auto ptr = std::make_shared<Node_t>(t);
			Base::push_back(ptr);
			return ptr;*/
		}
		
		std::shared_ptr<Node_t> getNext()
		{
			throw NotImp();
			/*return std::static_pointer_cast<Node_t>(Base::getNext());*/
		}
		
		bool ready() const
		{
			throw NotImp();
		}
	};
	
	/*template <>
	class DependencyGraph<void> : public DependencyGraph_NS::DependencyGraph_Base
	{
		private:
		typedef DependencyGraph_NS::DependencyGraph_Base Base;
		public:
		
		class Node_t : public DependencyGraph_NS::Node
		{
			public:
			Node_t() : DependencyGraph_NS::Node()
			{
				
			}
		};
		
		
		protected:
		
		virtual std::shared_ptr<BaseNode> createNode(const Weight_t) const override
		{
			throw NotImp();
		}
		
		public:
		DependencyGraph() : Base()
		{
			
		}
		
		std::shared_ptr<const Node_t> push_back()
		{
			auto ptr = std::make_shared<Node_t>();
			Base::push_back(ptr);
			return ptr;
		}
		
		std::shared_ptr<Node_t> getNext()
		{
			return std::static_pointer_cast<Node_t>(Base::getNext());
		}
		
	};*/
	
	
	
}
}