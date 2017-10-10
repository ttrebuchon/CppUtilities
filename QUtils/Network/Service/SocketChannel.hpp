#pragma once

#include "SocketChannel.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Network/Sockets.h>
#include "SocketProtocol/Protocol.h"
#include "Message.h"

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
		using namespace SocketProtocol;
		nlohmann::json body = *msg;
		const std::string str = body.dump();
		const unsigned char* cstr = reinterpret_cast<const unsigned char*>(str.c_str());
		const auto len = (str.length()+1);
		auto head = new Header<Spec>();
		head->id = 10;
		head->checksum = Protocol<Spec>::CalculateChecksum(cstr, len);
		head->size = len;
		
		unsigned char* rawHead = Protocol<Spec>::WriteHeader(head);
		delete head;
		
		this->socket->write(rawHead, Protocol<Spec>::HeaderLength);
		this->socket->write(cstr, len);
		
		delete[] rawHead;
		
		//throw NotImp();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <class Spec>
	ConnectionChannel_Info<Spec>* ConnectionChannel_Info<Spec>::Start(SocketRecvChannel<Spec>* chan, Socket* sock)
	{
		ConnectionChannel_Info<Spec>* ptr = NULL;
		try
		{
		
		ptr = new ConnectionChannel_Info<Spec>();
		ptr->sock = sock;
		ptr->channel = chan;
		ptr->cancellation = new std::atomic<bool>(false);
		ptr->handler = std::async(std::launch::async, [](auto ptr)
		{
			
			
			
			
			constexpr auto headLen = SocketProtocol::Protocol<Spec>::HeaderLength;
			
			while (!*ptr->cancellation)
			{
				if (ptr->sock->poll(100))
				{
					unsigned char* rawHead = new unsigned char[headLen];
					ptr->sock->read(rawHead, headLen);
					auto head = SocketProtocol::Protocol<Spec>::ParseHeader(rawHead);
					delete[] rawHead;
					
					std::cout << std::this_thread::get_id() << " - " << "Length " << head->size << "!\n";
					
					auto body = ptr->sock->read((const int)head->size);
					
					std::cout << "Body: '" << body << "'\n";
					
					
					
					delete head;
				}
			}
			
			
			
			
			
		}, ptr);
		
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
		for (auto con : connections)
		{
			if (con->handler.valid())
			{
				con->handler.get();
			}
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
				if (ptr->socket->poll(500))
				{
					sock = ptr->socket->accept();
					std::unique_lock<std::shared_timed_mutex> lock(ptr->conns_m);
					ptr->connections.push_back(ConnectionChannel_Info<Spec>::Start(ptr, sock));
					sock = NULL;
				}
				else
				{
					std::this_thread::yield();
				}
				}
				catch (...)
				{
					if (sock != NULL)
					{
						delete sock;
						sock = NULL;
					}
				}
			}
		}, this);
	}
	
}
}