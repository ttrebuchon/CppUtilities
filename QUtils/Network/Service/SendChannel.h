#pragma once
#include <memory>

namespace QUtils { namespace Network {
	
	class Message;
	
	class SendChannel
	{
		public:
		
		virtual void send(std::shared_ptr<Message>) = 0;
	};
}
}