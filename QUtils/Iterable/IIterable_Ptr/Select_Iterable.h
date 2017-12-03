#pragma once
#include "../IIterable_Ptr.h"
#include "SharedPtr_Iterable.h"
#include <list>

namespace QUtils { namespace Iterable { namespace Internal {
	
	
	
	template <class T>
	class Select_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;
		
		
		private:
		
		protected:
		std::shared_ptr<std::list<T>> list;
		
		public:
		
		template <class F, class Iter>
		Select_IIterable_Ptr(const F func, Iter start, Iter end) : list(std::make_shared<std::list<T>>())
		{
			for (Iter it = start; it != end; ++it)
			{
				list->push_back(func(*it));
			}
			
		}
		
		
		virtual iterator begin() override
		{
			return list->begin();
		}
		
		virtual iterator end() override
		{
			return list->end();
		}
		
		virtual const_iterator cbegin() const override
		{
			return list->begin();
		}
		
		virtual const_iterator cend() const override
		{
			return list->end();
		}
		
		virtual std::unique_ptr<IIterable_Ptr<T>> reference() const override
		{
			return std::make_unique<SharedPtr_IIterable_Ptr<T, std::list<T>>>(this->list);
		}
	};
	
}
}
}