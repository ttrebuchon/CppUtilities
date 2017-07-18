#pragma once

#include <type_traits>


#include "Service.h"

namespace QUtils
{
namespace Network
{
	template <class Service_t>
	class ServiceFactory
	{
		static_assert(std::is_base_of<Service, Service_t>::value, "");
		private:
		bool initted = false;
		
		
		public:
		
		virtual void init()
		{
			
		}
	};
}
}