#pragma once

#include "ReturnMessage.h"
#include "JsonMessage.h"

#include <QUtils/JSON/JSON.h>

namespace QUtils
{
namespace Network
{
	class Client
	{
		private:
		
		protected:
		std::shared_ptr<Router> router;
		
		template <class Ret, class ...T>
		std::future<Ret> sendJSONRequestAsync(std::string name, T... t)
		{
			auto args = QJSON::JSON::Serialize(t...);
			
			auto msg = std::make_shared<JsonMessage<Ret, T...>>(name, args);
			
			auto fut = msg->future();
			router->send(msg);
		}
		
		template <class Ret, class ...T>
		Ret sendJSONRequest(std::string name, T... t)
		{
			return sendJSONRequestAsync<Ret, T...>(name, t...).get();
			
		}
		
		template <class Ret>
		std::future<Ret> sendJSONRequestAsync(std::string name)
		{
			auto msg = std::make_shared<JsonMessage<Ret>>(name);
			auto fut = msg->future();
			router->send(msg);
		}
		
		template <class Ret>
		Ret sendJSONRequest(std::string name)
		{
			return sendJSONRequestAsync<Ret>(name).get();
		}
		
		
		
		public:
		
		
		
		
	};
}
}