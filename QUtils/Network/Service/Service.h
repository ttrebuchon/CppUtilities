#pragma once

#include <memory>
#include <queue>
#include <chrono>

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
		
		protected:
		std::shared_ptr<Router> router;
		
		virtual void process(Message& msg) = 0;
		
		public:
		template <class this_type>
		Service(std::shared_ptr<ServiceRouter<this_type>> router) : router(router)
		{
			
		}
		
		friend class Message;
		
	};
	
	
}
}