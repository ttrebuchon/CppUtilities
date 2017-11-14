#pragma once
#include <memory>
#include <typeindex>

namespace QUtils { namespace Iterable {
	
	template <class T>
	class Iterator_Ptr
	{
		private:
		
		protected:
		
		public:
		std::type_index it_type;
		Iterator_Ptr(std::type_index ind) : it_type(ind)
		{}
		
		virtual T& operator*() = 0;
		
		virtual Iterator_Ptr<T>& operator++() = 0;
		virtual std::unique_ptr<Iterator_Ptr<T>> operator++(int) = 0;
		virtual bool equals(const Iterator_Ptr<T>&) const = 0;
		virtual std::unique_ptr<Iterator_Ptr<T>> clone() const = 0;
		
	};
	
	template <class T>
	bool operator==(const Iterator_Ptr<T>& it1, const Iterator_Ptr<T>& it2)
	{
		if (it1.it_type == it2.it_type)
		{
			return it1.equals(it2);
		}
		
		return false;
	}
	
	template <class T>
	inline bool operator!=(const Iterator_Ptr<T>& it1, const Iterator_Ptr<T>& it2)
	{
		return !(it1 == it2);
	}
	
	template <class T, class iterator>
	class Wrapper_Iterator_Ptr : public Iterator_Ptr</*typename std::remove_reference<decltype(*std::declval<iterator>())>::type*/T>
	{
		private:
		protected:
		iterator it;
		
		
		public:
		//typedef typename std::remove_reference<decltype(*std::declval<iterator>())>::type value_type;
		typedef T value_type;
		
		private:
		typedef Iterator_Ptr<value_type> Base;
		
		public:
		
		
		
		Wrapper_Iterator_Ptr(iterator it) : Base(std::type_index(typeid(iterator))), it(it)
		{
			
		}
		
		
		virtual value_type& operator*() override
		{
			return *it;
		}
		
		Iterator_Ptr<value_type>& operator++() override
		{
			++it;
			return *this;
		}
		
		std::unique_ptr<Iterator_Ptr<value_type>> operator++(int) override
		{
			auto it2 = it++;
			return std::make_unique<Wrapper_Iterator_Ptr<T, iterator>>(it2);
		}
		
		virtual bool equals(const Iterator_Ptr<value_type>& other) const override
		{
			return (it == ((Wrapper_Iterator_Ptr<T, iterator>&)other).it);
		}
		
		virtual std::unique_ptr<Iterator_Ptr<value_type>> clone() const override
		{
			return std::make_unique<Wrapper_Iterator_Ptr<T, iterator>>(it);
		}
		
	};
}
}