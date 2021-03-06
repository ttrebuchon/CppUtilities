#pragma once
#include <functional>
#include <set>
#include <mutex>
#include <shared_mutex>
#include <list>

namespace QUtils {
	
	template <class... Args>
	class EventHandler
	{
		protected:
		mutable std::shared_timed_mutex handlers_m;
		std::list<std::function<void(Args...)>> handlers;
		
		public:
		
		template <class T>
		EventHandler& operator+=(const std::function<T(Args...)> handler)
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			return *this += std::function<void(Args...)>(handler);
		}
		
		EventHandler& operator+=(const std::function<void(Args...)> handler)
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			handlers.push_back(handler);
			return *this;
		}
		
		EventHandler& operator+=(const std::function<void()> handler)
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			handlers.push_back([=](auto... args) { handler(); });
			return *this;
		}
		
		virtual void operator()(Args... args) const
		{
			std::shared_lock<std::shared_timed_mutex> lock(handlers_m);
			for (const auto& hand : handlers)
			{
				hand(args...);
			}
		}
		
		void clear()
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			handlers.clear();
		}
		
		size_t size() const
		{
			return handlers.size();
		}
	};
	
	
	
	
	template <>
	class EventHandler<>
	{
		protected:
		mutable std::shared_timed_mutex handlers_m;
		std::list<std::function<void()>> handlers;
		
		public:
		
		template <class T>
		EventHandler& operator+=(const std::function<T()> handler)
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			return *this += std::function<void()>(handler);
		}
		
		EventHandler& operator+=(const std::function<void()> handler)
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			handlers.push_back(handler);
			return *this;
		}
		
		virtual void operator()() const
		{
			std::shared_lock<std::shared_timed_mutex> lock(handlers_m);
			for (const auto& hand : handlers)
			{
				hand();
			}
		}
		
		void clear()
		{
			std::lock_guard<std::shared_timed_mutex> lock(handlers_m);
			handlers.clear();
		}
		
		size_t size() const
		{
			return handlers.size();
		}
	};
}