#pragma once

#include <memory>
#include <queue>
#include <chrono>
#include <type_traits>

#include <QUtils/Multi/Mutexed.h>
#include "Message.h"
#include "Service.h"

#include <iostream>

namespace QUtils
{
namespace Network
{
	class Message;
	class Channel;
	
	namespace Helpers
	{
		template <class A, class B = A>
		struct MessageCompare
		{
			//True if x is lower priority than y
			bool operator()(const A x, const B y)
			{
				
				if (x->priority() == y->priority())
				{
					return x->time() > y->time();
				}
				else
				{
					return x->priority() < y->priority();
				}
			}
		};
		typedef std::shared_ptr<Message> MsgPtr;
		
		typedef std::priority_queue<MsgPtr, std::deque<MsgPtr>, MessageCompare<MsgPtr>> MessageQueue;
	}
	
	
	
	class Router
	{
		private:
		
		protected:
		Helpers::MessageQueue messages;
		//Multi::Mutexed<std::queue<std::shared_ptr<Message>>> messageTmpQueue;
		//std::shared_ptr<Service> service;
		QUtils::Multi::Mutexed<std::vector<std::shared_ptr<Channel>>> channels;
		
		virtual std::shared_ptr<Message> next();
		
		virtual std::shared_ptr<Message> fast_next();
		
		virtual std::shared_ptr<Message> slow_next();
		
		virtual void handleMsg(std::shared_ptr<Message> msg) = 0;
		
		
		
		
		Router() : messages(), channels() {}
		
		public:
		
		
		bool job();
		bool fast_job();
		
		void addChannel(const std::shared_ptr<Channel>);
		
		
		friend class Service;
	};
	
	
	
	template <class Service_t>
	class ServiceRouter : public Router
	{
		static_assert(std::is_base_of<Service, Service_t>::value, "ServiceRouter template parameter must derive from Service");
		private:
		
		protected:
		std::shared_ptr<Service_t> service;
		
		virtual void handleMsg(std::shared_ptr<Message> msg) override
		{
			msg->visit(*service);
		}
		
		public:
		ServiceRouter(std::shared_ptr<Service_t> service) : Router(), service(service)
		{
			if (!service)
			{
				//TODO
				throw std::exception();
			}
		}
		
		
		
	};
	
	
}
}