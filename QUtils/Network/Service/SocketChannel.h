#pragma once

#include "Channel.h"
#include "SocketProtocol/Types.h"

namespace QUtils { namespace Network {
	
	template <class>
	class SocketRecvChannel;
	
	template <class>
	class SocketSendChannel;
	
	class Socket;
	
	template <class ProtocolSpec = SocketProtocol::DefaultSpec>
	class SocketChannel
	{
		private:
		
		protected:
		Socket* socket;
		
		SocketChannel(Socket*);
		
		public:
		
		static std::shared_ptr<SocketRecvChannel<ProtocolSpec>> Listen(const unsigned short port, const unsigned int backlog = 10);
		
		static std::shared_ptr<SocketSendChannel<ProtocolSpec>> Connect(const std::string hostname, const unsigned short port);
		
	};
	
}
}