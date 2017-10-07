#include <QUtils/Network/Service/LocalChannel.h>



namespace QUtils { namespace Network {
	
	LocalChannel::LocalChannel() : Channel()
	{ }
	
	std::shared_ptr<LocalChannel> LocalChannel::Create()
	{
		return std::shared_ptr<LocalChannel>(new LocalChannel());
	}
	
	void LocalChannel::send(std::shared_ptr<Message> msg)
	{
		this->addMessage(msg);
	}
}
}