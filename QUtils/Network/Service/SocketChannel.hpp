#pragma once

#include "SocketChannel.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Network/Sockets.h>


namespace QUtils { namespace Network {
	
	template <class Spec>
	std::shared_ptr<SocketRecvChannel<Spec>> SocketChannel<Spec>::Listen(const unsigned short port, const unsigned int backlog)
	{
		auto sock = new 
		throw NotImp();
	}
	
	template <class Spec>
	std::shared_ptr<SocketSendChannel<Spec>> SocketChannel<Spec>::Connect(const std::string hostname, const unsigned short port)
	{
		auto sock = new INetSocket(SOCK_STREAM);
		sock->setPort(port);
		sock->getHostByName(hostname);
		sock->connect();
		auto ptr = std::shared_ptr<SocketSendChannel<Spec>>(new SocketSendChannel<Spec>(sock));
		return ptr;
		throw NotImp();
	}
	
}
}