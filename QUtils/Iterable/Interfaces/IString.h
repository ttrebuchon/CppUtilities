#pragma once
#include "../IIterable_Ptr.h"

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IString : public IIterable_Ptr<T>
	{
		protected:
		
		public:
		using typename IIterable_Ptr<T>::iterator;
		using typename IIterable_Ptr<T>::const_iterator;
		
		//Capacity
		virtual bool empty() const = 0;
		virtual size_t max_size() const = 0;
		virtual size_t size() const = 0;
		virtual void resize(size_t) = 0;
		virtual void resize(size_t, const T&) = 0;
		
		/* //Element Access
		virtual const T& front() const = 0;
		virtual T& front() = 0;
		virtual const T& back() const = 0;
		virtual T& back() = 0;*/
		
		//Modifiers
		virtual void push_back(const T&) = 0;
		virtual void push_back(T&&) = 0;
		virtual void pop_back() = 0;
		
		template <class... Args>
		void emplace_back(Args&&... args)
		{
			this->push_back((T&&)T(args...));
		}
		
		virtual void clear() = 0;
		virtual void insert(const_iterator, const T&) = 0;
		virtual void insert(const_iterator, size_t, const T&) = 0;
		virtual void insert(const_iterator, T&&) = 0;
		virtual void insert(const_iterator, std::initializer_list<T>) = 0;
		
		virtual void erase(const_iterator) = 0;
		virtual void erase(const_iterator, const_iterator) = 0;
		
	};
	
}
}