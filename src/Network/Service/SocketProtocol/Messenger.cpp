#include <QUtils/Network/Service/SocketProtocol/Messenger.h>
#include <QUtils/Network/Sockets.h>

namespace QUtils { namespace Network {
namespace SocketProtocol
{
	bool Messenger::poll(const int timeout_ms) const
	{
		return socket->poll(timeout_ms);
	}
	
	
}
}
}