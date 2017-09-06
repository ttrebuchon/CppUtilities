#pragma once
#include <functional>
#include <map>

#include <QUtils/Exception/Aggregate.h>

namespace QUtils::GUI
{
	template <class... T>
	class Event
	{
		protected:
		typedef unsigned long long ID_t;
		
		
		
		private:
		ID_t counter = 0;
		
		protected:
		std::map<ID_t, std::function<void(T...)>> handlers;
		
		bool _enabled;
		
		public:
		
		Event() : Event(true) {}
		Event(bool _enabled) : handlers(), _enabled(_enabled) {}
		
		void operator()(T... t) const
		{
			if (_enabled)
			{
				std::list<std::exception_ptr> exceptions;
				for (const auto& callback : handlers)
				{
					try
					{
					callback.second(t...);
					}
					catch (...)
					{
						exceptions.push_back(std::current_exception());
					}
				}
				
				
				if (exceptions.size() > 1)
				{
					throw QUtils::AggregateException(exceptions);
				}
				
				if (exceptions.size() > 0)
				{
					std::rethrow_exception(exceptions.front());
				}
			}
		}
		
		template <class F>
		ID_t operator+=(const F f)
		{
			return (*this) += std::function<void(T...)>(
			[f](auto... x)
			{
				f(x...);
			});
		}
		template <class Ret, class... Args>
		ID_t operator+=(const std::function<Ret(Args...)> f)
		{
			handlers[counter] = f;
			return counter++;
		}
		
		
		std::function<void(T...)> operator-=(const ID_t id)
		{
			auto func = handlers[id];
			handlers.erase(id);
			return func;
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