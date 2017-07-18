#pragma once

#include <future>

#include "Message.h"

namespace QUtils
{
namespace Network
{
	template <class Ret = void>
	class ReturnMessage : public Message
	{
		private:
		
		protected:
		std::promise<Ret> prom;
		
		public:
		
		virtual std::future<Ret> future() const
		{
			return prom.future();
		}
		
	};
	
}
}