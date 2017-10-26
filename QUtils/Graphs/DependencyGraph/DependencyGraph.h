#pragma once

#include "Node.h"
#include "Base.h"


namespace QUtils { namespace Graphs {
	
	template <class T = void>
	class DependencyGraph : public DependencyGraph_NS::DependencyGraph_Base
	{
		private:
		typedef DependencyGraph_NS::DependencyGraph_Base Base;
		public:
		
		class Node_t : public DependencyGraph_NS::Node
		{
			protected:
			T item;
			public:
			
			Node_t(const T t) : DependencyGraph_NS::Node(), item(t)
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
		
		
		std::shared_ptr<const Node_t> push_back(const T t)
		{
			auto ptr = std::make_shared<Node_t>(t);
			Base::push_back(ptr);
			return ptr;
		}
		
		std::shared_ptr<Node_t> getNext()
		{
			return std::static_pointer_cast<Node_t>(Base::getNext());
		}
	};
	
	template <>
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
		
	};
	
	
	/*template <class T>
	class DependencyGraph : public DependencyGraph<void>
	{
		protected:
		typedef DependencyGraph_NS::Node<T> NodeT_t;
		virtual std::shared_ptr<Node_t> createNode(const Priority_t) override;
		
		public:
		
		using DependencyGraph<void>::push_back;
		
		std::shared_ptr<Node_t> push_back(const T t)
		{
			
			std::shared_ptr<Node_t> node = getNewNode();
			
			auto Tnode = std::static_pointer_cast<NodeT_t>(node);
			Tnode->set(t);
			
			
			this->push_back(node);
			//TODO
			
			return node;
		}
	};*/
}
}