#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

struct sockaddr;

struct sockaddr_in;

namespace QUtils::Network
{
	enum struct SocketType
	{
		Inet,
		Unix,
	};
	
	
	class Socket
	{
		private:
		
		protected:
		int domain;
		int type;
		int protocol;
		
		int descriptor;
		
		::sockaddr* addr;
		const size_t addr_len;
		
		public:
		
		Socket(::sockaddr*, const size_t len, int domain, int type, int protocol = 0);
		Socket(const Socket&) = delete;
		virtual ~Socket();
		
		virtual void open();
		virtual void close();
		
		inline bool isOpen() const
		{ return descriptor != -1; }
		
		virtual void bind();
		virtual void connect();
		virtual void listen(int backlog);
		virtual Socket* accept() = 0;
		virtual void getAddrInfoAndOpen(const std::string node, const std::string service) = 0;
		virtual void getHostByName(const std::string) = 0;
		
		virtual int fd() const;
	};
	
	class INetSocket : public Socket
	{
		protected:
		
		public:
		INetSocket(int type, int protocol = 0);
		INetSocket(const INetSocket&) = delete;
		virtual ~INetSocket();
		
		
		virtual void bind() override;
		virtual INetSocket* accept() override;
		virtual void getAddrInfoAndOpen(const std::string node, const std::string service) override;
		
		virtual uint16_t port() const;
		virtual void setPort(uint16_t);
		
		virtual void getHostByName(const std::string) override;
	};
	
	
	
	
	
	/*class INetServerSocket : public INetSocket, public ServerSocket
	{
		private:
		
		protected:
		
		public:
		INetServerSocket(int type, int protocol = 0);
		virtual ~INetServerSocket();
		
		virtual void bind() override;
	};
	
	class INetClientSocket : public INetSocket, public ClientSocket
	{
		private:
		
		protected:
		
		public:
		INetClientSocket(int type, int protocol = 0);
		virtual ~INetClientSocket();
		
		virtual void connect(const std::string node, const std::string service) override;
	};*/
	
	
}