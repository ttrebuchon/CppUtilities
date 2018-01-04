#pragma once
#include <functional>
#include <set>

namespace QUtils {
	
	template <class... Args>
	class EventHandler
	{
		protected:
		std::vector<std::function<void(Args...)>> handlers;
		
		public:
		
		template <class T>
		EventHandler& operator+=(const std::function<T(Args...)> handler)
		{
			return *this += std::function<void(Args...)>(handler);
		}
		
		EventHandler& operator+=(const std::function<void(Args...)> handler)
		{
			handlers.push_back(handler);
			return *this;
		}
		
		virtual void operator()(Args... args) const
		{
			for (const auto& hand : handlers)
			{
				hand(args...);
			}
		}
		
		void clear()
		{
			handlers.clear();
		}
		
	};
}