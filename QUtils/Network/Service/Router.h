#pragma once

#include <memory>
#include <queue>
#include <chrono>

#include <QUtils/Multi/Mutexed.h>
#include "Message.h"

#include <iostream>

namespace QUtils
{
namespace Network
{
	class Message;
	
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
		Multi::Mutexed<std::queue<std::shared_ptr<Message>>> messageTmpQueue;
		//std::shared_ptr<Service> service;
		
		
		virtual std::shared_ptr<Message> next()
		{
			if (messageTmpQueue.try_lock())
			{
				while (!messageTmpQueue->empty())
				{
					messages.push(messageTmpQueue->front());
					messageTmpQueue->pop();
				}
				messageTmpQueue.unlock();
			}
			
			if (!messages.empty())
			{
				auto t = messages.top();
				messages.pop();
				return t;
			}
			else
			{
				return NULL;
			}
		}
		
		virtual std::shared_ptr<Message> fast_next()
		{
			if (messages.empty())
			{
				return next();
			}
			
			auto t = messages.top();
			messages.pop();
			return t;
		}
		
		virtual void handleMsg(std::shared_ptr<Message> msg) = 0;
		
		
		
		
		Router() : messages(), messageTmpQueue() {}
		
		public:
		
		
		void send(std::shared_ptr<Message> msg)
		{
			std::cout << "Sending msg\n";
			messageTmpQueue.lock();
			messageTmpQueue->push(msg);
			messageTmpQueue.unlock();
			std::cout << "Message in Tmp Queue\n";
		}
		
		
		virtual void job()
		{
			auto msg = next();
			if (msg != NULL)
			{
				std::cout << "Handling message " << msg << "\n";
				handleMsg(msg);
				std::cout << "Handled.\n";
			}
		}
		
		virtual void fast_job()
		{
			auto msg = fast_next();
			if (msg != NULL)
			{
				handleMsg(msg);
			}
		}
		
		
		friend class Service;
	};
	
	
	
	template <class Service_t>
	class ServiceRouter : public Router
	{
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