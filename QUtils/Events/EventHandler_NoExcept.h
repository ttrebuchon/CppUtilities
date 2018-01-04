#pragma once
#include "EventHandler.h"

namespace QUtils {
	
	template <class... Args>
	class EventHandler_Noexcept : public EventHandler<Args...>
	{
		
		public:
		virtual void operator()(Args... args) const
		{
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