#include <QUtils/Network/Socket.h>
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Exception/Exception.h>
#include <unistd.h>
#include <sys/un.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

namespace QUtils::Network
{
	QUTILS_CUSTOM_EXCEPTION(SocketException,);
	
	#define ERROR_EX(x) { auto errMsg = getError(x); throw (errMsg != "" ? SocketException().Msg(errMsg) : SocketException().Msg("ErrCode: " + std::to_string(x))).Function(__func__).Line(__LINE__).File(__FILE__); }
	
	
	std::string getError(const int);
	
	
	Socket::Socket(::sockaddr* addr, const size_t len, int domain, int type, int protocol) : domain(domain), type(type), protocol(protocol), descriptor(-1), addr(addr), addr_len(len)
	{
		
	}
	
	Socket::~Socket()
	{
		if (isOpen())
		{
			close();
		}
	}
	
	void Socket::close()
	{
		::close(descriptor);
		descriptor = -1;
	}
	
	
	void Socket::open()
	{
		if (isOpen())
		{
			return;
		}
		
		descriptor = ::socket(domain, type, protocol);
		int err = errno;
		if (descriptor == -1)
		{
			ERROR_EX(err);
		}
	}
	
	void Socket::bind()
	{
		if (!isOpen())
		{
			throw SocketException().Msg("Cannot bind a closed socket").Function(__func__).Line(__LINE__);
		}
		
		if (::bind(descriptor, addr, addr_len) == -1)
		{
			int err = errno;
			close();
			ERROR_EX(err);
		}
	}
	
	void Socket::listen(int backlog)
	{
		int l = ::listen(descriptor, backlog);
		int err = errno;
		if (l < 0)
		{
			ERROR_EX(err);
		}
	}
	
	void Socket::connect()
	{
		if (::connect(descriptor, addr, addr_len) != 0)
		{
			int err = errno;
			close();
			ERROR_EX(err);
		}
	}
	
	int Socket::fd() const
	{
		return descriptor;
	}
	
	
	
	
	
	
	
	INetSocket::INetSocket(int type, int protocol) : Socket((::sockaddr*)malloc(sizeof(::sockaddr_in)), sizeof(::sockaddr_in), AF_INET, type, protocol)
	{
		memset(addr, 0, sizeof(::sockaddr_in));
		
		auto addr = (::sockaddr_in*)this->addr;
		
		addr->sin_family = this->domain;
		addr->sin_addr.s_addr = INADDR_ANY;
		setPort(0);
	}
	
	INetSocket::~INetSocket()
	{
		if (addr != NULL)
		{
			free((::sockaddr_in*)addr);
			addr = NULL;
		}
	}
	
	uint16_t INetSocket::port() const
	{
		return ntohs(((::sockaddr_in*)addr)->sin_port);
	}
	
	void INetSocket::setPort(uint16_t port)
	{
		((::sockaddr_in*)addr)->sin_port = htons(port);
	}
	
	void INetSocket::bind()
	{
		if (port() == 0)
		{
			Socket::bind();
			::socklen_t len = addr_len;
			if (::getsockname(descriptor, addr, &len) < 0)
			{
				int err = errno;
				close();
				ERROR_EX(err);
			}
			
			
		}
		else
		{
			Socket::bind();
		}
	}
	
	INetSocket* INetSocket::accept()
	{
		int s = ::accept(descriptor, NULL, NULL);
		int err = errno;
		if (s < 0)
		{
			ERROR_EX(err);
		}
		INetSocket* sock = new INetSocket(this->type, this->protocol);
		
		sock->descriptor = s;
		::socklen_t len = sock->addr_len;
		::getsockname(s, sock->addr, &len);
		
		return sock;
	}
	
	void INetSocket::getAddrInfoAndOpen(const std::string node, const std::string service)
	{
		if (isOpen())
		{
			close();
		}
		
		::addrinfo hints;
		::addrinfo *result, *rp;
		
		memset(&hints, 0, sizeof(::addrinfo));
		hints.ai_family = domain;
		hints.ai_socktype = type;
		hints.ai_protocol = protocol;
		hints.ai_flags = 0;
		
		int s = ::getaddrinfo(node.c_str(), service.c_str(), &hints, &result);
		if (s != 0)
		{
			ERROR_EX(s);
		}
		
		throw NotImp();
	}
	
	void INetSocket::getHostByName(const std::string name)
	{
		auto ent = ::gethostbyname(name.c_str());
		::memcpy(&((::sockaddr_in*)addr)->sin_addr, ent->h_addr_list[0], ent->h_length);
	}
	
	
	
	
	
	
	
	
	
	
	std::string getError(const int err)
	{
		#define ERR(x) case x: return #x
		switch (err)
		{
			//ERR(EAI_FAMILY);
			//ERR(EAI_NONAME);
			//ERR(EAI_SERVICE);
			
			ERR(EACCES);
			ERR(EPERM);
			ERR(EADDRINUSE);
			ERR(EALREADY);
			ERR(ECONNREFUSED);
			ERR(EPROTOTYPE);
			ERR(EAFNOSUPPORT);
			ERR(ENETUNREACH);
			//ERR(EFAULT);
			ERR(EBADF);
			//ERR(EAGAIN);
			ERR(EWOULDBLOCK);
			ERR(EINVAL);
			ERR(ECONNABORTED);
			ERR(EPROTONOSUPPORT);
			ERR(ENOBUFS);
			ERR(ENOMEM);
			ERR(EMFILE);
			ERR(ENFILE);
			ERR(ENOTSOCK);
			ERR(EOPNOTSUPP);
			
			
			
			default:
			return "";
		}
	}
}