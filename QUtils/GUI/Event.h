#pragma once
#include <functional>
#include <list>

namespace QUtils::GUI
{
	template <class... T>
	class Event
	{
		protected:
		std::list<std::function<void(T...)>> handlers;
		
		public:
		
		void operator()(T... t) const
		{
			for (const auto& callback : handlers)
			{
				callback(t...);
			}
		}
		
		template <class F>
		Event<T...>& operator+=(const F f)
		{
			return (*this) += std::function<void(T...)>(
			[f](auto... x)
			{
				f(x...);
			});
		}
		template <class Ret, class... Args>
		Event<T...>& operator+=(const std::function<Ret(Args...)> f)
		{
			handlers.push_back(f);
			return *this;
		}
		
	};
}