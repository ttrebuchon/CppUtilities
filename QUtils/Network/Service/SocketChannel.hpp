#pragma once

#include "SocketChannel.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Network/Sockets.h>
#include "SocketProtocol/Messenger.h"
#include "SocketProtocol/Messenger.hpp"
#include "SocketProtocol/Protocol.h"
#include "Message.h"

#include <iostream>


namespace QUtils { namespace Network {
	
	
	
	SocketChannel::SocketChannel(Socket* sock) : socket(sock)
	{
		
	}
	
	SocketChannel::~SocketChannel()
	{
		/*if (socket != NULL)
		{
			if (socket->isOpen())
			{
				socket->close();
			}
			delete socket;
			socket = NULL;
		}*/
	}
	
	
	template <class Spec>
	std::shared_ptr<SocketRecvChannel<Spec>> SocketChannel::Listen(const unsigned short port, const unsigned int backlog)
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
	std::shared_ptr<SocketSendChannel<Spec>> SocketChannel::Connect(const std::string hostname, const unsigned short port)
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
	SocketSendChannel<Spec>::SocketSendChannel(Socket* sock) : SocketChannel(sock), SendChannel(), msgr_m(), msgr(SocketProtocol::Messenger::Create<Spec>(sock))
	{
		
	}
	
	template <class Spec>
	SocketSendChannel<Spec>::~SocketSendChannel()
	{
		std::lock_guard<std::shared_timed_mutex> msgr_lock(msgr_m);
		msgr.reset();
		if (this->socket != NULL)
		{
			if (this->socket->isOpen())
			{
				this->socket->close();
			}
			delete this->socket;
			this->socket = NULL;
		}
	}
	
	template <class Spec>
	void SocketSendChannel<Spec>::send(std::shared_ptr<Message> msg)
	{
		using namespace SocketProtocol;
		nlohmann::json body = *msg;
		const std::string str = body.dump();
		const unsigned char* cstr = reinterpret_cast<const unsigned char*>(str.c_str());
		const auto len = (str.length()+1);
		
		
		{
			std::lock_guard<std::shared_timed_mutex> msgr_lock(msgr_m);
			if (!msgr->openIDs())
			{
				throw NotImp();
			}
			msgr->send(cstr, len, false, msg->responseRequired);
		}
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
			
			
			
			
			auto messenger = SocketProtocol::Messenger::Create<Spec>(ptr->sock);
			
			
			unsigned long long id;
			unsigned long long len;
			bool wideChars;
			bool responseRequired;
			unsigned char* body = NULL;
			
			while (!*ptr->cancellation)
			{
				if (ptr->sock->poll(100))
				{
					body = messenger->receive(len, wideChars, responseRequired, id);
					if (body == NULL)
					{
						continue;
					}
					if (len <= 0)
					{
						delete[] body;
						body = NULL;
						continue;
					}
					
					#ifdef DEBUG
					//DEBUG
					{
					std::string bodyStr(len, 'a');
					::memcpy(&bodyStr[0], body, len);
					std::cout << "Body: '" << bodyStr << "'\n" << std::flush;
					}
					#endif


					nlohmann::json jMsg;
					if (!wideChars)
					{
						jMsg = nlohmann::json::parse(body);
					}
					else
					{
						//TODO
						throw std::exception();
						//jMsg = nlohmann::json::parse(std::wstring(reinterpret_cast<const wchar_t*>(body)));
					}
					delete[] body;
					
					

					const std::chrono::system_clock::time_point timestamp(std::chrono::system_clock::duration(jMsg["timestamp"].get<unsigned long long>()));
					const int priority = jMsg["priority"];
					
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
					*ptr->cancellation = true;
					try
					{
						ptr->handler.get();
					}
					catch (...)
					{}
					delete ptr->cancellation;
				}
				delete ptr;
			}
			throw;
		}
	}
	
	
	
	template <class Spec>
	SocketRecvChannel<Spec>::SocketRecvChannel(Socket* sock) : SocketChannel(sock), Channel(), acceptor(), acceptor_cancellation(false), connections(), conns_m()
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
				else
				{
					std::cerr << "Couldn't join Acceptor thread!" << std::endl;
				}
			}
			catch (std::exception& ex)
			{
				//DEBUG
				std::cout << "Acceptor exception: \n" << ex.what() << std::endl;
			}
			catch (...)
			{
				
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
				try
				{
					con->handler.get();
				}
				catch (...)
				{ }
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
					
					ConnectionChannel_Info<Spec>* newCon = ConnectionChannel_Info<Spec>::Start(ptr, sock);
					
					if (newCon != NULL)
					{
						ptr->connections.push_back(newCon);
					}
					
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