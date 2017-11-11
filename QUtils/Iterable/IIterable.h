#pragma once
#include "Iterator.h"
#include "IIterable_Ptr.h"
#include "IIterable_Ptr/Types.h"
#include <vector>
#include <list>

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IIterable
	{
		public:
		typedef Iterator<T> iterator;
		
		
		private:
		
		protected:
		std::unique_ptr<IIterable_Ptr<T>> ptr;
		
		
		public:
		
		template <class It>
		IIterable(const It& start, const It& end) : ptr(std::make_unique<Internal::Start_End_IIterable_Ptr<T>>(start, end))
		{}
		
		template <class G>
		IIterable(G& g) : ptr(std::make_unique<Internal::Reference_IIterable_Ptr<T, G>>(g))
		{
			
		}
		
		iterator begin()
		{
			return ptr->begin();
		}
		
		iterator end()
		{
			return ptr->end();
		}
		
		std::vector<T> toVector()
		{
			std::vector<T> vec(begin(), end());
			return vec;
		}
		
		std::list<T> toList()
		{
			std::list<T> list(begin(), end());
			return list;
		}
	};
}
}