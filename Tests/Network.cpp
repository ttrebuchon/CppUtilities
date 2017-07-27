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
		try
		{
		dout << "Creating Service...\n";
		auto srv = StringService::Create();
		
		dout << "Getting Router...\n";
		auto router = std::dynamic_pointer_cast<StringService::Router>(srv->localRouter());
		
		dout << "Launching service thread...\n";
		auto startF = std::async(std::launch::async, [srv]() {
			srv->start();
			dout << "srv->start() ended...\n";
		});
		
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
		
		//QUtils::sleep(1000);
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
		printFut.get();
		dout << "Ending\n";
		srv->stop();
		QUtils::sleep(1000);/*
		srv.reset();
		router.reset();*/
		}
		catch(...)
		{
			dout << "Caught\n";
		}
	}
	
	
	return true;
}