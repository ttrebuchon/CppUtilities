#pragma once
#include "../IIterable_Ptr.h"
#include <list>

namespace QUtils { namespace Iterable { namespace Internal {
	
	template <class T>
	class Where_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;
		
		
		private:
		
		protected:
		std::list<T> list;
		
		public:
		
		template <class F, class Iter>
		Where_IIterable_Ptr(const F pred, Iter start, Iter end) : list()
		{
			for (Iter it = start; it != end; ++it)
			{
				if (pred(*it))
				{
					list.push_back(*it);
				}
			}
		}
		
		
		virtual iterator begin() override
		{
			return list.begin();
		}
		
		virtual iterator end() override
		{
			return list.end();
		}
		
		virtual const_iterator cbegin() const override
		{
			return list.begin();
		}
		
		virtual const_iterator cend() const override
		{
			return list.end();
		}
	};
	
}
}
}