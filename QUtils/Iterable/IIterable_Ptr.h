#pragma once
#include "Iterator.h"
#include <vector>

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IIterable_Ptr
	{
		public:
		typedef Iterator<T> iterator;
		
		
		private:
		
		protected:
		
		
		
		public:
		
		
		
		virtual iterator begin() = 0;
		virtual iterator end() = 0;
		
	};
}
}