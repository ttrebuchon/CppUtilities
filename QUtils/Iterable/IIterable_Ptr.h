#pragma once
#include "Iterator.h"
#include <vector>

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IIterable_Ptr
	{
		public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;
		
		private:
		
		protected:
		
		
		
		public:
		
		
		
		virtual iterator begin() = 0;
		virtual iterator end() = 0;
		virtual const_iterator cbegin() const = 0;
		virtual const_iterator cend() const = 0;
		inline const_iterator begin() const
		{ return cbegin(); }
		inline const_iterator end() const
		{ return cend(); }
		virtual std::unique_ptr<IIterable_Ptr<T>> reference() const = 0;
		
		
		
		
		//Element Access
		virtual const T& front() const
		{
			return *cbegin();
		}
		virtual T& front()
		{
			return *begin();
		}
	};
}
}