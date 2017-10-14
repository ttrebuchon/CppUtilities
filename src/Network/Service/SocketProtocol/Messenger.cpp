#include <QUtils/Network/Service/SocketProtocol/Messenger.h>
#include <QUtils/Network/Service/SocketProtocol/Types.h>
#include <QUtils/Network/Sockets.h>

namespace QUtils { namespace Network {
namespace SocketProtocol
{
	bool Messenger::poll(const int timeout_ms) const
	{
		return socket->poll(timeout_ms);
	}
	
	std::shared_ptr<Messenger> Messenger::CreateDefault(Socket* socket)
	{
		auto ptr = new MessengerWithSpec<DefaultSpec>(socket);
		return std::shared_ptr<Messenger>(ptr);
	}
	
	
}
}
}