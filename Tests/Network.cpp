#include "../Tests_Helpers.h"
#include <QUtils/Network/Network.h>
#include <QUtils/Network/Service.h>
#include <json/json.hpp>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>


#include <QUtils/Sleep/Sleep.h>

using json = nlohmann::json;
using namespace curlpp::options;
using namespace curlpp;

namespace Network_Test
{
	void Test()
	{
		auto br = [&] () -> std::ostream& {
			return (dout << "---------------------" << "\n\n\n\n\n" << "---------------------" << "\n");
		};
		
		curlpp::Easy request;
		request.setOpt<Url>("http://www.reddit.com/.json");
		request.perform();
		
		br() << std::flush;
		
		dout << "\n\n\n\n" << "\"" << curlpp::options::Url("www.reddit.com/.json") << "\"" << std::endl;
		
		br();
		//dout << request << std::endl;
		
		Url rUrl;
		request.getOpt(rUrl);
		
		dout << rUrl.getValue() << std::endl;
		
		dout << curlpp::infos::ResponseCode::get(request) << std::endl;
		dout << curlpp::infos::EffectiveUrl::get(request) << std::endl;
		
		Easy request2;
		request2.setOpt<Url>("https://www.reddit.com/.json");
		request2.setOpt(Header(true));
		std::stringstream ss;
		request2.setOpt(WriteStream(&ss));
		try
		{
		request2.perform();
		}
		catch (std::exception& ex)
		{
			dout << ex.what() << std::endl;
		}
		
		br() << ss.str() << std::endl;
		
		
		auto tryRequest = [](std::string url, bool printInfo = true, bool followRedirect = true) -> std::string
		{
			Easy request;
			std::stringstream ss;
			request.setOpt<FollowLocation>(followRedirect);
			
			request.setOpt<Url>(url);
			request.setOpt<WriteStream>(&ss);
			
			try
			{
				request.perform();
			}
			catch (std::exception& ex)
			{
				ss << ex.what();
			}
			
			if (printInfo)
			{
				dout << "Effective URL: " <<  curlpp::infos::EffectiveUrl::get(request) << std::endl;
				
				dout << "Response Code: " << curlpp::infos::ResponseCode::get(request) << std::endl;
			}
			
			return ss.str();
		};
		
		
		
		const std::string annaURL = "http://testing.project-anna.com/";
		dout << "Trying " << annaURL << "\n";
		request2.setOpt<Url>(annaURL);
		request2.setOpt<FollowLocation>(true);
		request2.setOpt<Header>(false);
		
		try
		{
			request2.perform();
			dout << request2 << std::endl;
		}
		catch (std::exception& ex)
		{
			dout << ex.what() << "\n";
		}
		
		dout << "sstream: \n";
		br() << ss.str() << std::endl;
		
		dout << "Effective URL: " <<  curlpp::infos::EffectiveUrl::get(request2) << std::endl;
		
		dout << "Response Code: " << curlpp::infos::ResponseCode::get(request2) << std::endl;
		
		br() << "Trying lambda request for \"" << annaURL << "\"\n";
		br() << tryRequest(annaURL) << std::endl;
		
		
		br() << tryRequest("http://testing.project-anna.com/Services/api/Web/SessionsCount") << std::endl;
		
	}
}


bool Test_Network()
{
	QUtils::Network::Curl::Init();
	Network_Test::Test();
	
	
	{
		
		
		
		
		
		
		class StringService : public QUtils::Network::Service, public std::enable_shared_from_this<StringService>
		{
			public:
			typedef QUtils::Network::ServiceRouter<StringService> Router;
			protected:
			std::map<int, std::string> strings;
			int next = 0;
			
			virtual void process(QUtils::Network::Message&) override
			{
				
			}
			
			
			virtual void registerProcs() override
			{
				QUtils::Network::ProcedureLookup<std::string, StringService, int>::Register("create", &StringService::create);
				QUtils::Network::ProcedureLookup<std::string, StringService, void, const int, std::string>::Register("set", &StringService::set);
				
				QUtils::Network::ProcedureLookup<std::string, StringService, void, const int>::Register("print", &StringService::print);
			}
			
			
			
			public:
			StringService() : QUtils::Network::Service()
			{
				
			}
			
			virtual ~StringService()
			{
				dout << "~StringService()\n";
			}
			
			static std::shared_ptr<StringService> Create()
			{
				auto ptr = std::make_shared<StringService>();
				ptr->setRouter(std::make_shared<QUtils::Network::ServiceRouter<StringService>>(ptr));
				return ptr;
			}
			
			
			void print(const int id)
			{
				dout << "{id: " << id << ", string: \"" << strings.at(id) << "\"}\n";
			}
			
			void set(const int id, std::string value)
			{
				strings.at(id) = value;
			}
			
			int create()
			{
				strings[next] = std::string();
				return next++;
			}
			
		};
		
		std::shared_ptr<StringService> srv = NULL;
		
		
		
		dout << "Creating Service...\n";
		srv = StringService::Create();
		
		dout << "Getting Router...\n";
		auto router = std::dynamic_pointer_cast<StringService::Router>(srv->localRouter());
		
		dout << "Launching service thread...\n";
		srv->startThreaded();
		
		
		
		dout << "Creating 'create()' Message...\n";
		auto newMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, int>>("create");
		
		dout << "Sending Message...\n";
		router->send(newMsg);
		
		
		dout << "Checking RPC Message Future...\n";
		auto idFuture = newMsg->future();
		assert_ex(idFuture.valid());
		dout << "Getting Result...\n";
		int strID = idFuture.get();
		
		
		
		dout << "Creating 'set(id, str)' Message...\n";
		
		auto setMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, const int, std::string>>("set", strID, "TestString");
		
		router->send(setMsg);
		
		
		
		dout << "Creating 'print(id)' Message...\n";
		auto printMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, const int>>("print", strID);
		dout << "Sending Message...\n";
		router->send(printMsg);
		
		dout << "Checking print-future validity...\n";
		assert_ex(printMsg->future().valid());
		dout << "Waiting for end...\n";
		auto printFut = printMsg->future();
		if (!printFut.valid())
		{
			std::cout << "printFut not valid!!\n";
		}
		assert_ex(printFut.valid());
		printFut.get();
		dout << "Ending\n";
		srv->stop();
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
		srv->startThreaded();
		
		
		
		
		
		
		class StringClient : public QUtils::Network::LocalClient<StringService>
		{
			private:
			//std::shared_ptr<StringService::Router> router;
			int objID;
			
			public:
			StringClient(std::shared_ptr<StringService::Router> router) : QUtils::Network::LocalClient<StringService>(router), objID(-1)
			{
				/*auto newMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, int>>("create", 4);
				router->send(newMsg);
				objID = newMsg->future().get();*/
				objID = this->sendRPCRequest<int>("create", 4);
			}
			
			StringClient& operator=(std::string str)
			{
				/*auto setMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, const int, std::string>>("set", objID, str, 1);
				router->send(setMsg);
				//setMsg->future().get();
				*/
				this->sendRPCRequestAsync<void, const int, std::string>("set", objID, str, 1);
				return *this;
			}
			
			void print()
			{
				/*auto printMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, const int>>("print", objID, 1);
				router->send(printMsg);
				if (!printMsg->future().valid())
				{
					throw std::future_error(std::future_errc::no_state);
				}
				printMsg->future().get();*/
				return this->sendRPCRequest<void, const int>("print", objID, 1);
			}
			
			
			std::shared_future<void> printAsync()
			{
				/*auto printMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, const int>>("print", objID, 1);
				router->send(printMsg);
				if (!printMsg->future().valid())
				{
					throw std::future_error(std::future_errc::no_state);
				}
				printMsg->future().get();*/
				return this->sendRPCRequestAsync<void, const int>("print", objID, 1);
			}
			
		};
		
		
		
		
		
		
		QUtils::sleep(200);
		dout << "\n\n\n\n";
		StringClient str1(router);
		str1 = "Testing";
		str1.print();
		for (int i = 0; i < 10; ++i)
		{
			str1 = "Testing_" + std::to_string(i+1);
			
			StringClient str2(router);
			str2 = "String_" + std::to_string(i+1);
			str1.printAsync();
			str2.printAsync();
			str2 = "Hello";
			str2 = ", world" + std::to_string(i+1);
			str2 = "X" + std::to_string(i+1);
			str2.printAsync();
		}
		
		srv->wait();
		
		
		dout << "\n\n\n\n";
		srv->stop();
		
	}
	
	
	return true;
}