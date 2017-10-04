#include <QUtils/Network/Service/SocketProtocol/Protocol.h>
#include <QUtils/Network/Service/SocketProtocol/Header.h>

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	Header* Protocol::ParseHeader(const char* data, unsigned int size)
	{
		Header* h = new Header();
		
		return h;
	}
	
	
}
}
}