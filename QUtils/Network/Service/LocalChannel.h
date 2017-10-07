#pragma once

#include "Channel.h"
#include "SendChannel.h"


namespace QUtils { namespace Network {
	
	class LocalChannel : public Channel, public SendChannel
	{
		protected:
		LocalChannel();
		
		public:
		
		
		static std::shared_ptr<LocalChannel> Create();
		
		virtual void send(std::shared_ptr<Message>) override;
		
	};
	
	
}
}