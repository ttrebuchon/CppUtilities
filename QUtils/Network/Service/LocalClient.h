#pragma once

#include "Client.h"
#include "ReturnMessage.h"
#include "JsonMessage.h"
#include "RPCMessage.h"
#include "LocalChannel.h"

#include <QUtils/JSON/JSON.h>

namespace QUtils
{
namespace Network
{
	template <class Service_t>
	class LocalClient : public Client<Service_t>
	{
		private:
		
		protected:/*
		std::shared_ptr<LocalChannel> channel;
		
		template <class Ret, class ...T>
		std::future<Ret> sendJSONRequestAsync(std::string name, T... t)
		{
			auto args = QJSON::JSON::Serialize(t...);
			
			auto msg = std::make_shared<JsonMessage<Ret, T...>>(name, args);
			
			auto fut = msg->future();
			channel->send(msg);
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
			channel->send(msg);
		}
		
		template <class Ret>
		Ret sendJSONRequest(std::string name)
		{
			return sendJSONRequestAsync<Ret>(name).get();
		}
		
		
		template <class Ret, class ...Args>
		Ret sendRPCRequest(std::string name, Args... args, int priority = 1)
		{
			auto msg = std::make_shared<RPCMessage<Service_t, Ret, Args...>>(name, args..., priority);
			channel->send(msg);
			if (!msg->future().valid())
			{
				throw std::future_error(std::future_errc::no_state);
			}
			return msg->future().get();
		}
		
		template <class Ret, class ...Args>
		std::shared_future<Ret> sendRPCRequestAsync(std::string name, Args... args, int priority = 1)
		{
			auto msg = std::make_shared<RPCMessage<Service_t, Ret, Args...>>(name, args..., priority);
			channel->send(msg);
			return msg->future();
		}
		
		
		
		
		
		template <class Ret, class ...Args>
		Ret sendRPCRequest(std::string name, Args... args, int priority = 1) const
		{
			auto msg = std::make_shared<RPCMessage<const Service_t, Ret, Args...>>(name, args..., priority);
			channel->send(msg);
			if (!msg->future().valid())
			{
				throw std::future_error(std::future_errc::no_state);
			}
			return msg->future().get();
		}
		
		template <class Ret, class ...Args>
		std::shared_future<Ret> sendRPCRequestAsync(std::string name, Args... args, int priority = 1) const
		{
			auto msg = std::make_shared<RPCMessage<const Service_t, Ret, Args...>>(name, args..., priority);
			channel->send(msg);
			return msg->future();
		}
		*/
		
		public:
		
		LocalClient(std::shared_ptr<LocalChannel> channel) : Client<Service_t>(channel)
		{}
		
		LocalClient(std::shared_ptr<Router> router) : Client<Service_t>(LocalChannel::Create())
		{
			if (router == NULL)
			{
				//TODO
				throw std::exception();
			}
			router->addChannel(std::dynamic_pointer_cast<LocalChannel>(this->channel));
		}
		
		LocalClient(std::shared_ptr<Service> service) : LocalClient(service->getRouter())
		{ }
		
		
	};
}
}