#pragma once

#include "DependencyGraph/Node.h"
#include <atomic>
#include <type_traits>
#include <deque>
#include <QUtils/Types/TypeSequence.h>


namespace QUtils { namespace Graph {
	
	
	
	template <class T = void>
	class DependencyGraph
	{
		public:
		typedef typename DependencyGraph_NS::Node<T> Node_t;
		typedef typename Node_t::Priority_t Priority_t;
		
		
		private:
		Priority_t nextPriority;
		
		protected:
		std::deque<std::shared_ptr<Node_t>> roots;
		
		public:
		DependencyGraph() : roots()
		{
			
		}
		
		template <class... F>
		std::enable_if_t<std::is_same<typename QUtils::Types::FirstTypeOrVoid<F...>::type, T>::value, std::shared_ptr<Node_t>> push_back(F... f)
		{
			static_assert(sizeof...(F) < 2, "insert() only takes one argument");
			
			auto node = std::make_shared<Node_t>(nextPriority++, f...);
			
			//TODO
			
			return node;
		}
		
		
	};
}
}