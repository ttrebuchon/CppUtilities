#pragma once

#include "Client.h"

namespace QUtils { namespace Network {
	
	template <class Service_t, class ProtocolSpec>
	class INetClient : public Client<Service_t>
	{
		private:
		
		protected:
		
		public:
		
		INetClient(const std::string hostname, const unsigned short port);
	};
}
}