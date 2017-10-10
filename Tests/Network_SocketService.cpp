#include "Tests_Helpers.h"

#include <QUtils/Network/Service/Service.h>
#include <QUtils/Network/Service/Channel.h>
#include <QUtils/Network/Service/SocketChannel.h>
#include <QUtils/Network/Service/SocketChannel.hpp>
#include <QUtils/Network/Service/Message.h>

#include <QUtils/String/String.h>
#include <QUtils/Sleep/Sleep.h>

void Test_Channel();
void Test_SocketChannel();
void Test_TimeSrv();

DEF_TEST(Network_SocketService)
{
	Test_Channel();
	Test_SocketChannel();
	Test_TimeSrv();
	
	return true;
}

namespace TestChannel_NS
{

	using namespace QUtils::Network;
	class TestChannel : public Channel
	{
		protected:
		
		
		bool gatherMessages() final
		{ return false; }
		
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
		
		std::string str;
		
		TestMessage(const std::string str) : Message(false), str(str)
		{
			
		}

		virtual int priority() const override
		{
			return 0;
		}
		
		virtual void serialize(nlohmann::json& j) const
		{
			j["str"] = str;
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



	

	auto msg1 = std::make_shared<TestMessage>("");

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
		msgs_arr[i] = std::make_shared<TestMessage>("");
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

	auto msg2 = std::make_shared<TestMessage>("");
	chan1->Test_addMessage(msg2);
	assert_ex(chan1->hasMessages);
	assert_ex(chan1->stillValid);
	assert_ex(msgs_deq->size() == prevSize);

	delete msgs_deq;
	
}


void Test_SocketChannel()
{
	using namespace QUtils::Network;
	
	const auto portno = 65528;
	
	
	auto srvsock_future = std::async(std::launch::async, []() {
		return SocketChannel<>::Listen(portno);
	});
	
	
	std::this_thread::yield();
	decltype(SocketChannel<>::Connect("", 0)) sock = NULL;
	while (sock == NULL && srvsock_future.valid())
	{
		try
		{
			sock = SocketChannel<>::Connect("localhost", portno);
			std::this_thread::yield();
		}
		catch (std::exception& ex)
		{
			QUtils::String what(ex.what());
			if (!what.contains( "refused"))
			{
				throw;
			}
			dout << ex.what() << "\n\n\n";
			assert_ex(srvsock_future.valid());
			auto wait = srvsock_future.wait_for(std::chrono::milliseconds(5000));
			assert_ex(wait != std::future_status::deferred);
			if (wait == std::future_status::ready)
			{
				srvsock_future.get();
			}
		}
	}
	
	auto srvsock = srvsock_future.get();
	
	//QUtils::sleep(2000);
	
	/*auto sock2 = SocketChannel<>::Connect("localhost", portno);
	assert_ex(sock2->isOpen());*/
	
	using namespace TestChannel_NS;
	
	sock->send(std::make_shared<TestMessage>("Hello, world"));
	std::this_thread::yield();
	QUtils::sleep(1000);
	
}







void Test_TimeSrv()
{
	class TimeService : public QUtils::Network::Service
	{
		
	};
}