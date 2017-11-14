#pragma once
#include "Iterator.h"
#include "IIterable_Ptr.h"
#include "IIterable_Ptr/Types.h"
#include <vector>
#include <list>
#include <functional>

namespace QUtils { namespace Iterable {
	
	template <class T>
	class IIterable
	{
		public:
		typedef Iterator<T> iterator;
		//typedef Iterator<const T> const_iterator;
		
		
		private:
		
		protected:
		std::unique_ptr<IIterable_Ptr<T>> ptr;
		
		IIterable(std::unique_ptr<IIterable_Ptr<T>>&& ptr) : ptr()
		{
			this->ptr.swap(ptr);
		}
		
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
		
		auto begin() const
		{
			return ptr->cbegin();
		}
		
		auto end() const
		{
			return ptr->cend();
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
		
		virtual T& at(const size_t index)
		{
			auto it = begin();
			auto e = end();
			size_t i;
			for (i = 0; i < index && it != e; ++i)
			{
				++it;
			}
			if (i < index && it == e)
			{
				//TODO: throw out of bounds
			}
			return *it;
		}
		
		IIterable<T> where(std::function<bool(const T&)> pred) const
		{
			return std::move(IIterable<T>(std::make_unique<Internal::Where_IIterable_Ptr<T>>(pred, begin(), end())));
		}
		
		auto& getConst() const
		{
			//ptr = NULL;
			return *this;
		}
	};
}
}