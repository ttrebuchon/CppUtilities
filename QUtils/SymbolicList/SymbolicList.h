#pragma once
#include <vector>
#include <functional>
#include <memory>


namespace QUtils
{
namespace SymbolicList
{
	template <class T>
	class SymList
	{
		
		
		public:
		T& operator[](const int index)
		{
			return at(index);
		}
		
		virtual T& at(const int index) = 0;
		
	};
	
	template <class T, class Container>
	class PointerSymList : public SymList<T>
	{
		private:
		std::shared_ptr<Container> container;
		std::function<T&(std::shared_ptr<Container>, const int)> accessor;
		std::function<int(const std::shared_ptr<Container>)> sizer;
		
		
		public:
		template <class F, class S>
		PointerSymList(std::shared_ptr<Container> ptr, const F f, const S s) : container(ptr), accessor([f](std::shared_ptr<Container> cont, const int index) -> T& {return f(*cont, index);}), sizer([s](const std::shared_ptr<Container> cont) -> int {return s(*cont);})
		{
			
		}
		
		template <class F, class S>
		PointerSymList(Container* ptr, const F f, const S s) : container(ptr), accessor([f](std::shared_ptr<Container> cont, const int index) -> T& {return f(*cont, index);}), sizer([s](const std::shared_ptr<Container> cont) -> int {return s(*cont);})
		{
			
		}
		
		
		virtual T& at(const int index) override
		{
			return accessor(container, index);
		}
		
		virtual int size() const
		{
			return sizer(container);
		}
	};
	
	template <class T, class Iterator>
	class IteratorSymList : public SymList<T>
	{
		private:
		Iterator beginIt;
		Iterator endIt;
		int count;
		std::function<T&(decltype(*std::declval<Iterator>()))> accessor;
		public:
		template <class F>
		IteratorSymList(F& f) : SymList<T>(), beginIt(f.begin()), endIt(f.end()), count(0), accessor()
		{
			accessor = [](auto& x) -> T& { return x; };
			
			for (auto it = beginIt; it != endIt; it++)
			{
				count++;
			}
		}
		
		virtual T& at(const int index) override
		{
			auto it = beginIt;
			for (int i = 0; i < index; i++)
			{
				it++;
			}
			return accessor(*it);
		}
	};
}
}