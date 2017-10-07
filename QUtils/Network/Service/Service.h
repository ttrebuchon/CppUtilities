#pragma once

#include <memory>
#include <queue>
#include <chrono>
#include <future>
#include <string>
#include <atomic>

#include <QUtils/Multi/Mutexed.h>

#include "ProcedureLookup.h"
#include "TypeLookup.h"

namespace QUtils
{
namespace Network
{
	class Router;
	
	template <class>
	class ServiceRouter;
	
	class Message;
	
	class Service
	{
		private:
		std::atomic<bool> _started;
		bool registered;
		std::future<void> serviceFuture;
		
		Service(std::shared_ptr<Router> router);
		
		void goRegister();
		
		protected:
		std::shared_ptr<Router> router;
		
		virtual void process(Message& msg) = 0;
		
		virtual void registerProcs() = 0;
		
		template <class Service_t, class Ret, class ...Args>
		void registerProc(std::string name, Ret(Service_t::*proc)(Args...)) const
		{
			ProcedureLookup<std::string, Service_t, Ret, Args...>::Register(name, proc);
		}
		
		template <class Service_t, class Ret, class ...Args>
		void registerProc(std::string name, Ret(Service_t::*proc)(Args...) const) const
		{
			ProcedureLookup<std::string, Service_t, Ret, Args...>::Register(name, proc);
		}
		
		public:
		const std::atomic<bool>& started;
		template <class this_type>
		Service(std::shared_ptr<ServiceRouter<this_type>> router) : Service((std::shared_ptr<Router>)router)
		{}
		
		Service() : Service(NULL)
		{}
		
		virtual ~Service();
		
		template <class this_type>
		void setRouter(std::shared_ptr<ServiceRouter<this_type>> router)
		{
			if (this->router)
			{
				//TODO
				throw std::exception();
			}
			this->router = router;
		}
		
		std::shared_ptr<Router> getRouter();
		
		virtual void start();
		virtual void startAsync();
		
		virtual void stop();
		
		
		virtual void wait();
		
		friend class Message;
		
	};
	
	
}
}