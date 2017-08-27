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
		bool _enabled;
		
		public:
		
		Event() : Event(true) {}
		Event(bool _enabled) : handlers(), _enabled(_enabled) {}
		
		void operator()(T... t) const
		{
			if (_enabled)
			{
				for (const auto& callback : handlers)
				{
					callback(t...);
				}
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
		
		void enable()
		{
			_enabled = true;
		}
		
		void disable()
		{
			_enabled = false;
		}
		
		bool enabled() const
		{
			return _enabled;
		}
		
	};
}