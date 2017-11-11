#pragma once
#include "../IIterable_Ptr.h"

namespace QUtils { namespace Iterable { namespace Internal {
	
	template <class T>
	class Start_End_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		
		
		private:
		
		protected:
		iterator it1, it2;
		
		
		
		public:
		
		template <class It>
		Start_End_IIterable_Ptr(const It& start, const It& end) : it1(start), it2(end)
		{}
		
		virtual iterator begin() override
		{
			return it1;
		}
		
		virtual iterator end() override
		{
			return it2;
		}
	};
}
}
}