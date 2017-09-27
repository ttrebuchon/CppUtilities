#include "../Tests_Helpers.h"
#include <QUtils/Network/Network.h>
#include <QUtils/Network/Service.h>
#include "../Deps/json/json.hpp"
#include <QUtils/GUID/GUID.h>

#ifdef QUTILS_HAS_CURL
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#endif

#include <QUtils/Sleep/Sleep.h>
#include <QUtils/Types/CompilerPrint.h>

using json = nlohmann::json;
#ifdef QUTILS_HAS_CURL
using namespace curlpp::options;
using namespace curlpp;

#endif

namespace Network_Test
{
	void Test()
	{
		#ifdef QUTILS_HAS_CURL
		auto br = [&] () -> std::ostream& {
			return (dout << "---------------------" << "\n\n\n\n\n" << "---------------------" << "\n");
		};
		
		curlpp::Easy request;
		request.setOpt<Url>("http://www.reddit.com/.json");
		request.setOpt<Timeout>(2); //Set timeout to 2 seconds
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
		request2.setOpt<Timeout>(2); //Set timeout to 2 seconds
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
			request.setOpt<Timeout>(2); //Set timeout to 2 seconds
			
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
		request2.setOpt<Timeout>(2); //Set timeout to 2 seconds
		
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
		#endif
	}
}

void MathServiceTest();

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
				//QUtils::Network::ProcedureLookup<std::string, StringService, int>::Register("create", &StringService::create);
				
				this->registerProc("create", &StringService::create);
				//QUtils::Network::ProcedureLookup<std::string, StringService, void, const int, std::string>::Register("set", &StringService::set);
				this->registerProc("set", &StringService::set);
				
				//QUtils::Network::ProcedureLookup<std::string, StringService, void, const int>::Register("print", &StringService::print);
				
				this->registerProc<StringService, void, int>("print", &StringService::print);
				
				//QUtils::Network::ProcedureLookup<std::string, StringService, std::string, const int>::Register("str", &StringService::str);
				this->registerProc("str", &StringService::str);
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
			
			std::string str(const int id) const
			{
				return strings.at(id);
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
		
		auto setMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, int, std::string>>("set", strID, "TestString");
		
		router->send(setMsg);
		
		
		
		dout << "Creating 'print(id)' Message...\n";
		auto printMsg = std::make_shared<QUtils::Network::RPCMessage<StringService, void, int>>("print", strID);
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
				objID = this->sendRPCRequest<int>("create", 4);
			}
			
			StringClient& operator=(std::string str)
			{
				this->sendRPCRequestAsync<void, int, std::string>("set", objID, str, 1);
				return *this;
			}
			
			void print()
			{
				return this->sendRPCRequest<void, int>("print", objID, 1);
			}
			
			
			std::shared_future<void> printAsync()
			{
				return this->sendRPCRequestAsync<void, int>("print", objID, 1);
			}
			
			std::string str() const
			{
				return this->sendRPCRequest<std::string, int>("str", objID, 1);
			}
			
		};
		
		
		
		
		
		//Sleep to make sure all the print statements are executed before the line break
		QUtils::sleep(200); 
		dout << "\n\n\n\n";
		StringClient str1(router);
		str1 = "Testing";
		str1.print();
		const int stringCallCount = 10;
		for (int i = 0; i < stringCallCount; ++i)
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
		
		assert_ex(str1.str() == "Testing_" + std::to_string(stringCallCount));
		
		srv->wait();
		
		
		dout << "\n\n\n\n";
		srv->stop();
		
	}
	
	dout << "\n\n\n\n";
	
	MathServiceTest();
	
	return true;
}


void MathServiceTest()
{
	class MathService : public QUtils::Network::Service
	{
		private:
		
		public:
		typedef QUtils::Network::ServiceRouter<MathService> Router;
		
		typedef QUtils::GUID ID_t;
		
		protected:
		
		std::map<ID_t, long double> objects;
		
		virtual void process(QUtils::Network::Message&) override
			{
				
			}
		
		virtual void registerProcs() override
		{
			this->registerProc("create", &MathService::create);
			
			this->registerProc/*<MathService, void, ID_t>*/("print", &MathService::print);
			this->registerProc("get", &MathService::get);
			this->registerProc("set", &MathService::set);
			this->registerProc("add", &MathService::add);
		}
		
		public:
		
		static std::shared_ptr<MathService> Create()
		{
			auto ptr = std::make_shared<MathService>();
			ptr->setRouter(std::make_shared<Router>(ptr));
			return ptr;
		}
		
		ID_t create()
		{
			ID_t id = ID_t::Create();
			objects[id] = 0;
			return id;
		}
		
		void print(const ID_t id) const
		{
			dout << "Object with ID " << id << " -> " << objects.at(id) << "\n";
		}
		
		void set(const ID_t id, const long double val)
		{
			objects.at(id) = val;
		}
		
		long double get(const ID_t id) const
		{
			return objects.at(id);
		}
		
		ID_t add(const ID_t id1, const ID_t id2)
		{
			ID_t id3 = ID_t::Create();
			objects[id3] = objects.at(id1) + objects.at(id2);
			return id3;
		}
		
		
	};
	
	auto srv1 = MathService::Create();
	
	srv1->startThreaded();
	dout << "Service 1 started...\n";
	
	auto router1 = std::dynamic_pointer_cast<MathService::Router>(srv1->localRouter());
	
	auto createMsg1 = std::make_shared<QUtils::Network::RPCMessage<MathService, MathService::ID_t>>("create");
	
	router1->send(createMsg1);
	
	auto createResp1 = createMsg1->future();
	assert_ex(createResp1.valid());
	MathService::ID_t obj_id1 = createResp1.get();
	
	auto printMsg1 = std::make_shared<QUtils::Network::RPCMessage<const MathService, void, MathService::ID_t>>("print", obj_id1);
	
	router1->send(printMsg1);
	
	printMsg1->future().get();
	
	
	class MathObj : public QUtils::Network::LocalClient<MathService>
	{
		private:
		typedef QUtils::Network::LocalClient<MathService> Base;
		typedef typename MathService::ID_t ID_t;
		
		protected:
		ID_t id;
		
		public:
		
		MathObj(std::shared_ptr<typename MathService::Router> router, const ID_t id) : Base(router), id(id)
		{
			
		}
		MathObj(std::shared_ptr<typename MathService::Router> router) : Base(router), id()
		{
			id = sendRPCRequest<ID_t>("create");
		}
		
		void print() const
		{
			sendRPCRequest<void, ID_t>("print", id);
		}
		
		std::shared_future<void> printAsync() const
		{
			return sendRPCRequestAsync<void, ID_t>("print", id);
		}
		
		void set(const long double val)
		{
			sendRPCRequest<void, ID_t, long double>("set", id, val);
		}
		
		long double get() const
		{
			return sendRPCRequest<long double, ID_t>("get", id);
		}
		
		MathObj operator+(const MathObj obj2) const
		{
			return MathObj(this->router, const_cast<MathObj*>(this)->sendRPCRequest<ID_t, ID_t, ID_t>("add", id, obj2.id));
		}
	};
	
	
	
	MathObj obj1(router1, obj_id1);
	dout << "MathObj1 created.\n";
	MathObj obj2(router1);
	dout << "MathObj2 created.\n";
	
	{
	
	auto printMessage2 = std::make_shared<QUtils::Network::RPCMessage<const MathService, void, MathService::ID_t>>("print", obj_id1);
	router1->send(printMessage2);
	printMessage2->future().get();
	
	}
	
	dout << "Printing...\n";
	obj2.print();
	dout << "Printed.\n";
	
	long double obj2_v = 45;
	dout << "Setting obj2 (45)...\n";
	obj2.set(45);
	
	long double obj1_v = 15;
	dout << "Setting obj1 (15)...\n";
	obj1.set(15);
	
	obj1.print();
	obj2.print();
	
	long double obj3_v = obj1_v + obj2_v;
	MathObj obj3 = obj1 + obj2;
	
	obj3.print();
	
	assert_ex(obj1.get() == obj1_v);
	assert_ex(obj2.get() == obj2_v);
	assert_ex(obj3.get() == obj3_v);
	
	srv1->stop();
	dout << "Service 1 stopped.\n";
}