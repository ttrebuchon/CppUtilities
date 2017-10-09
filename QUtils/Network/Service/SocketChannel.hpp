#pragma once

#include "SocketChannel.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Network/Sockets.h>
#include <iostream>


namespace QUtils { namespace Network {
	
	
	
	template <class Spec>
	SocketChannel<Spec>::SocketChannel(Socket* sock) : socket(sock)
	{
		
	}
	
	template <class Spec>
	SocketChannel<Spec>::~SocketChannel()
	{
		if (socket != NULL)
		{
			if (socket->isOpen())
			{
				socket->close();
			}
			delete socket;
			socket = NULL;
		}
	}
	
	
	template <class Spec>
	std::shared_ptr<SocketRecvChannel<Spec>> SocketChannel<Spec>::Listen(const unsigned short port, const unsigned int backlog)
	{
		INetSocket* sock = NULL;
		try
		{
			sock = new INetSocket(SOCK_STREAM);
			sock->open();
			sock->setPort(port);
			sock->bind();
			sock->listen(backlog);
			
			auto ptr = std::shared_ptr<SocketRecvChannel<Spec>>(new SocketRecvChannel<Spec>(sock));
			ptr->initialize();
			
			return ptr;
		}
		catch (...)
		{
			if (sock != NULL)
			{
				if (sock->isOpen())
				{
					sock->close();
				}
				delete sock;
			}
			throw;
		}
	}
	
	template <class Spec>
	std::shared_ptr<SocketSendChannel<Spec>> SocketChannel<Spec>::Connect(const std::string hostname, const unsigned short port)
	{
		INetSocket* sock = NULL;
		try
		{
		sock = new INetSocket(SOCK_STREAM);
		sock->setPort(port);
		sock->getHostByName(hostname);
		sock->open();
		sock->connect();
		auto ptr = std::shared_ptr<SocketSendChannel<Spec>>(new SocketSendChannel<Spec>(sock));
		return ptr;
		}
		catch (...)
		{
			if (sock != NULL)
			{
				if (sock->isOpen())
				{
					sock->close();
				}
				delete sock;
			}
			throw;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	template <class Spec>
	SocketSendChannel<Spec>::SocketSendChannel(Socket* sock) : SocketChannel<Spec>(sock), SendChannel()
	{
		
	}
	
	template <class Spec>
	void SocketSendChannel<Spec>::send(std::shared_ptr<Message> msg)
	{
		throw NotImp();
	}
	
	
	
	
	
	
	
	
	
	
	#define TPRIN std::cout << std::this_thread::get_id() << "::"
	
	
	
	template <class Spec>
	ConnectionChannel_Info<Spec>* ConnectionChannel_Info<Spec>::Start(SocketRecvChannel<Spec>* chan, Socket* sock)
	{
		//return NULL;
		ConnectionChannel_Info<Spec>* ptr = NULL;
		try
		{
		
		ptr = new ConnectionChannel_Info<Spec>();
		ptr->sock = sock;
		ptr->channel = chan;
		ptr->cancellation = new bool(false);
		
		return ptr;
		
		}
		catch (...)
		{
			if (ptr != NULL)
			{
				if (ptr->cancellation != NULL)
				{
					delete ptr->cancellation;
				}
				delete ptr;
			}
			throw;
		}
	}
	
	
	
	template <class Spec>
	SocketRecvChannel<Spec>::SocketRecvChannel(Socket* sock) : SocketChannel<Spec>(sock), Channel()
	{
		
	}
	
	template <class Spec>
	SocketRecvChannel<Spec>::~SocketRecvChannel()
	{
		{
			acceptor_cancellation = true;
			try
			{
				if (acceptor.joinable())
				{
					acceptor.join();
				}
			}
			catch (...)
			{
				throw;
			}
		}
		{
		std::unique_lock<std::shared_timed_mutex> lock(conns_m);
		for (auto con : connections)
		{
			*(con->cancellation) = true;
		}
		TPRIN << "Joining connections...\n";
		for (auto con : connections)
		{
			if (!con->handler.valid())
			{
				TPRIN << "Not valid!\n" << std::flush;
			}
			else
			{
				con->handler.get();
			}
			TPRIN << "Joined...\n";
			delete con->cancellation;
			con->cancellation = NULL;
			con->sock->close();
			delete con->sock;
			con->sock = NULL;
			
			delete con;
		}
		
		connections.clear();
		
		}
	}
	
	template <class Spec>
	bool SocketRecvChannel<Spec>::gatherMessages()
	{
		{
			std::shared_lock<std::shared_timed_mutex> lock(conns_m);
			
		}
		throw NotImp();
	}
	
	template <class Spec>
	void SocketRecvChannel<Spec>::initialize()
	{
		if (acceptor.joinable())
		{
			//TODO
			//Already initted
			throw std::exception();
		}
		
		
		acceptor = std::thread(
		[] (auto ptr)
		{
			while (!ptr->acceptor_cancellation)
			{
				Socket* sock = NULL;
				try
				{
				TPRIN << "Waiting for connection...\n";
				if (ptr->socket->poll(500))
				{
					TPRIN << "Connection waiting!" << std::endl;
					sock = ptr->socket->accept();
					bool* cancel = new bool();
					*cancel = false;
					TPRIN << "Creating connection...\n";
					std::unique_lock<std::shared_timed_mutex> lock(ptr->conns_m);
					ptr->connections.push_back(ConnectionChannel_Info<Spec>::Start(ptr, sock));
					sock = NULL;
					TPRIN << "Connection created.\n";
				}
				else
				{
					std::this_thread::yield();
				}
				}
				catch (...)
				{
					TPRIN << "Error!\n";
					if (sock != NULL)
					{
						delete sock;
						sock = NULL;
					}
				}
			}
			
			TPRIN << "Acceptor exiting...\n";
		}, this);
	}
	
}
}