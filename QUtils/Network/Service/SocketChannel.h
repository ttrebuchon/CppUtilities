#pragma once

#include "Channel.h"
#include "SendChannel.h"
#include "SocketProtocol/Types.h"
#include "SocketProtocol/Messenger.h"
#include <list>
#include <QUtils/Network/Sockets.h>

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
		virtual ~SocketChannel();
		
		public:
		
		static std::shared_ptr<SocketRecvChannel<ProtocolSpec>> Listen(const unsigned short port, const unsigned int backlog = 10);
		
		static std::shared_ptr<SocketSendChannel<ProtocolSpec>> Connect(const std::string hostname, const unsigned short port);
		
		bool isOpen() const
		{
			return socket->isOpen();
		}
		
		const Socket* getSocket() const
		{
			return socket;
		}
		
	};
	
	
	
	
	
	template <class Spec>
	class SocketSendChannel : public SocketChannel<Spec>, public SendChannel
	{
		protected:
		
		
		SocketSendChannel(Socket*);
		
		
		public:
		
		virtual ~SocketSendChannel();
		
		void send(std::shared_ptr<Message>) final override;
		
		
		template <class>
		friend class SocketChannel;
	};
	
	template <class Spec>
	struct ConnectionChannel_Info
	{
		Socket* sock;
		std::future<void> handler;
		SocketRecvChannel<Spec>* channel;
		std::atomic<bool>* cancellation;
		
		static ConnectionChannel_Info<Spec>* Start(SocketRecvChannel<Spec>*, Socket*);
	};
	
	template <class Spec>
	class SocketRecvChannel : public SocketChannel<Spec>, public Channel
	{
		protected:
		std::thread acceptor;
		std::atomic<bool> acceptor_cancellation;
		std::list<ConnectionChannel_Info<Spec>*> connections;
		
		std::shared_timed_mutex conns_m;
		
		SocketRecvChannel(Socket*);
		
		bool gatherMessages();
		
		void initialize();
		
		public:
		
		virtual ~SocketRecvChannel();
		
		
		template <class>
		friend class SocketChannel;
	};
	
	
}
}