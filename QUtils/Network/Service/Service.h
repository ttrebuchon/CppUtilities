#pragma once

#include <memory>
#include <queue>
#include <chrono>
#include <iostream>

#include <QUtils/Multi/Mutexed.h>

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
		Multi::Mutexed<bool> _started;
		bool registered;
		
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
		
		public:
		const Multi::Mutexed<bool>& started;
		template <class this_type>
		Service(std::shared_ptr<ServiceRouter<this_type>> router) : Service((std::shared_ptr<Router>)router)
		{}
		
		Service() : Service(NULL)
		{}
		
		virtual ~Service()
		{
			router = NULL;
			std::cout << "~Service()\n";
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
		
		virtual void stop()
		{
			std::cout << "Stop()\n";
			_started.lock();
			_started = false;
			_started.unlock();
		}
		
		friend class Message;
		
	};
	
	
}
}