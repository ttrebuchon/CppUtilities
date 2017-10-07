#pragma once

#include "Service.h"


namespace QUtils
{
namespace Network
{
	class Service;
	
	class Message
	{
		private:
		const std::chrono::system_clock::time_point createTime = std::chrono::system_clock::now();
		
		protected:
		
		virtual void visit(Service& srv)
		{
			srv.process(*this);
		}
		
		public:
		
		virtual int priority() const = 0;
		virtual std::chrono::system_clock::time_point time() const
		{
			return createTime;
		}
		
		template <class Service_t>
		friend class ServiceRouter;
	};
	
}
}