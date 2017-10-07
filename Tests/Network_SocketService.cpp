#include "Tests_Helpers.h"

#include <QUtils/Network/Service/Service.h>
#include <QUtils/Network/Service/Channel.h>
#include <QUtils/Network/Service/Message.h>

void Test_Channel();
void Test_TimeSrv();

DEF_TEST(Network_SocketService)
{
	Test_TimeSrv();
	
	return true;
}

namespace TestChannel_NS
{

	using namespace QUtils::Network;
	class TestChannel : public Channel
	{
		public:
		TestChannel() : Channel()
		{
			
		}
		
		
		
		void Test_addMessage(std::shared_ptr<Message> msg)
		{
			this->addMessage(msg);
		}

		void Test_addMessages(auto x, auto y)
		{
			this->addMessages(x, y);
		}

		
	};

	class TestMessage : public Message
	{
		public:

			virtual int priority() const override
			{
				return 0;
			}

	};

}

void Test_Channel()
{
	
	using namespace TestChannel_NS;
	
	auto chan1 = std::make_shared<TestChannel>();
	assert_ex(chan1->stillValid);
	assert_ex(!chan1->hasMessages);
	chan1->Test_addMessage(NULL);
	assert_ex(!chan1->hasMessages);
	assert_ex(chan1->stillValid);



	

	auto msg1 = std::make_shared<TestMessage>();

	chan1->Test_addMessage(msg1);
	assert_ex(chan1->hasMessages);
	assert_ex(chan1->stillValid);
	auto msg1_1 = chan1->getNext();
	assert_ex(msg1 == msg1_1);
	assert_ex(!chan1->hasMessages);
	assert_ex(chan1->stillValid);

	const int msgs_arr_size = 10;
	std::shared_ptr<Message>* msgs_arr = new std::shared_ptr<Message>[msgs_arr_size];
	for (int i = 0; i < msgs_arr_size; ++i)
	{
		msgs_arr[i] = std::make_shared<TestMessage>();
	}

	chan1->Test_addMessages(msgs_arr, msgs_arr+msgs_arr_size);
	assert_ex(chan1->hasMessages);
	assert_ex(chan1->stillValid);

	delete[] msgs_arr;

	std::deque<std::shared_ptr<Message>>* msgs_deq = chan1->getAll();
	assert_ex(!chan1->hasMessages);
	assert_ex(chan1->stillValid);

	const auto prevSize = msgs_deq->size();
	assert_ex(prevSize == msgs_arr_size);

	auto msg2 = std::make_shared<TestMessage>();
	chan1->Test_addMessage(msg2);
	assert_ex(chan1->hasMessages);
	assert_ex(chan1->stillValid);
	assert_ex(msgs_deq->size() == prevSize);

	delete msgs_deq;
	
}

void Test_TimeSrv()
{
	class TimeService : public QUtils::Network::Service
	{
		
	};
}