#pragma once
#include <memory>
#include <iterator>
#include "Iterator_Ptr.h"

namespace QUtils { namespace Iterable {
	
	template <class T>
	class Iterator : public std::iterator<std::input_iterator_tag, T>
	{
		private:
		
		protected:
		std::unique_ptr<Iterator_Ptr<T>> ptr;
		
		public:
		//typedef T value_type;
		
		
		template <class It>
		Iterator(It it) : ptr(nullptr)
		{
			static_assert(std::is_same<T, typename std::remove_reference<decltype(*std::declval<It>())>::type>::value, "");
			static_assert(std::is_same<T, typename Wrapper_Iterator_Ptr<It>::value_type>::value, "");
			ptr = std::make_unique<Wrapper_Iterator_Ptr<It>>(it);
		}
		
		Iterator(const Iterator<T>& it) : ptr(nullptr)
		{
			ptr = it.ptr->clone();
		}
		
		Iterator() : ptr()
		{}
		
		T& operator*()
		{
			return **ptr;
		}
		
		const T& operator*() const
		{
			return **ptr;
		}
		
		T& operator->()
		{
			return **ptr;
		}
		
		const T& operator->() const
		{
			return **ptr;
		}
		
		Iterator<T>& operator++()
		{
			ptr->operator++();
			return *this;
		}
		
		Iterator<T> operator++(int);
		
		template <class G>
		friend bool operator==(const Iterator<G>& it1, const Iterator<G>& it2);
	};
	
	template <class T>
	inline bool operator==(const Iterator<T>& it1, const Iterator<T>& it2)
	{
		if (!it1.ptr || !it2.ptr)
		{
			return false;
		}
		return *it1.ptr == *it2.ptr;
	}
	
	template <class T>
	inline bool operator!=(const Iterator<T>& it1, const Iterator<T>& it2)
	{
		return !(it1 == it2);
	}
}
}