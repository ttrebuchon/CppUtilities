#include "Tests_Helpers.h"

#include <QUtils/Network/Service/Service.h>
#include <QUtils/Network/Service/Channel.h>

void Test_Channel();
void Test_TimeSrv();

DEF_TEST(Network_SocketService)
{
	Test_TimeSrv();
	
	return true;
}

void Test_Channel()
{
	using namespace QUtils::Network;
	class TestChannel : public Channel
	{
		public:
		TestChannel() : Channel()
		{
			
		}
		
		auto Test_getNext()
		{
			return this->getNext();
		}
		
		auto Test_getAll()
		{
			return this->getAll();
		}
		
		
		
		void Test_addMessage(std::shared_ptr<Message> msg)
		{
			this->addMessage(msg);
		}
	};
	
	
	auto chan1 = std::make_shared<TestChannel>();
	assert_ex(!chan1->hasMessages);
	chan1->Test_addMessage(NULL);
	assert_ex(!chan1->hasMessages);
}

void Test_TimeSrv()
{
	class TimeService : public QUtils::Network::Service
	{
		
	};
}