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
		
		Service(std::shared_ptr<Router> router) : _started(false), registered(false), router(router), started(_started)
		{
			
		}
		
		void goRegister()
		{
			if (!registered)
			{
				registerProcs();
			}
		}
		
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
		
		virtual ~Service()
		{
			router = NULL;
			this->stop();
			
		}
		
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
		
		virtual std::shared_ptr<Router> localRouter()
		{
			return router;
		}
		
		virtual void start();
		virtual void startThreaded()
		{
			if (this->serviceFuture.valid())
			{
				if (serviceFuture.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
				{
					//TODO
					throw std::exception();
				}
			}
			this->serviceFuture = std::async(std::launch::async, [&] () {
				this->start();
			});
		}
		
		virtual void stop()
		{
			_started = false;
		}
		
		
		virtual void wait();
		
		friend class Message;
		
	};
	
	
}
}