#pragma once
#include "IString.h"

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IList : public IString<T>
	{
		protected:
		
		public:
		
		
		//Modifiers
		virtual void assign(size_t, const T&) = 0;
		virtual void push_front(const T&) = 0;
		virtual void push_front(T&&) = 0;
		virtual void pop_front() = 0;
		
		template <class... Args>
		void emplace_front(Args&&... args)
		{
			this->push_front((T&&)T(args...));
		}
		
		
	};
	
}
}