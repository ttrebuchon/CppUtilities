#pragma once
#include "EventHandler.h"

namespace QUtils {
	
	template <class... Args>
	class EventHandler_Noexcept : public EventHandler<Args...>
	{
		
		public:
		virtual void operator()(Args... args) const
		{
			std::shared_lock<std::shared_timed_mutex> lock(this->handlers_m);
			for (auto& handler : this->handlers)
			{
				try
				{
					handler(args...);
				}
				catch (...)
				{
					
				}
			}
		}
	};
}