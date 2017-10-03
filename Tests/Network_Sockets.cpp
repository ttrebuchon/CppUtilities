#include "../Tests_Helpers.h"
#include <QUtils/Network/Socket.h>
#include <future>
#include <unistd.h>
#include <atomic>
#include <Deps/json/json.hpp>

#include <QUtils/String/String.h>
#include <QUtils/Sleep/Sleep.h>
#include <QUtils/Exception/Aggregate.h>
#include <QUtils/Exception/Exception.h>

using namespace QUtils::Network;

#define SOCKET_TEST(x) void x##_SocketTest(Socket* srvsock, Socket* act_srvsock, Socket* sock)

SOCKET_TEST(C_IO);
SOCKET_TEST(Wrapped_IO);
SOCKET_TEST(Async);
SOCKET_TEST(Peek);
SOCKET_TEST(WaitAll);
SOCKET_TEST(JSON);
SOCKET_TEST(Raw_IO);

void InitStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void InitDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

void CleanupStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void CleanupDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);



QUTILS_CUSTOM_EXCEPTION(SocketTestException, );



DEF_TEST(Network_Sockets)
{
	Socket *active, *passive, *client;
	std::vector<std::exception_ptr> exceptions;
	
	
	
	
	
	#define RUN_TEST(x, y) \
	dout << "\n\nInitializing " << #x << " sockets...\n"; \
	try { \
	Init##x##Sockets(&passive, &active, &client); \
	dout << "Running Test '" << #y << "_SocketTest'...\n"; \
	y##_SocketTest(passive, active, client); } \
	catch (...) { \
	dout << "Exception in " << #y << "_SocketTest for " << #x << "!\n"; \
	SocketTestException ex(std::current_exception());  \
	ex.Msg(std::string(#y \
	) + "_SocketTest for " + #x \
	); \
	try { throw ex; } catch (...) \
	{ \
	exceptions.push_back(std::current_exception()); \
	} \
	} \
	try { \
	dout << "Cleaning up sockets...\n\n\n"; \
	Cleanup##x##Sockets(&passive, &active, &client); \
	} catch (...) { \
	dout << "Could not clean up sockets!\n"; } \
	
	
	#define RUN_TESTS(x) \
	RUN_TEST(Stream, x); \
	RUN_TEST(DGram, x); \
	
	
	
	RUN_TESTS(C_IO);
	RUN_TESTS(Wrapped_IO);
	RUN_TESTS(Async);
	RUN_TESTS(Peek);
	
	RUN_TEST(Stream, WaitAll); //Only valid for streams
	
	RUN_TESTS(JSON);
	RUN_TESTS(Raw_IO);
	
	if (exceptions.size() > 0)
	{
		throw QUtils::AggregateException(exceptions);
	}
	return true;
}



void InitStreamSockets(Socket** passive_server, Socket** active_server, Socket** client)
{
	INetSocket* pass;
	INetSocket* cli;
	INetSocket* act;
	
	*passive_server = pass = new INetSocket(SOCK_STREAM);
	*client = cli = new INetSocket(SOCK_STREAM);
	
	pass->open();
	assert_ex(pass->isOpen());
	
	pass->bind();
	assert_ex(pass->isOpen());
	
	cli->open();
	assert_ex(cli->isOpen());
	
	cli->setPort(pass->port());
	cli->getHostByName("localhost");
	assert_ex(cli->isOpen());
	assert_ex(cli->port() == pass->port());
	
	pass->listen(10);
	assert_ex(pass->isOpen());
	
	auto accept = std::async(std::launch::async, [](auto ptr) { return ptr->accept(); }, pass);
	
	cli->connect();
	*active_server = act = accept.get();
	assert_ex(pass->isOpen());
	assert_ex(act->isOpen());
	assert_ex(cli->isOpen());
}

void InitDGramSockets(Socket** passive_server, Socket** active_server, Socket** client)
{
	INetSocket* pass;
	INetSocket* cli;
	INetSocket* act;
	
	*active_server = *passive_server = act = pass = new INetSocket(SOCK_DGRAM);
	*client = cli = new INetSocket(SOCK_DGRAM);
	
	pass->open();
	assert_ex(pass->isOpen());
	
	pass->bind();
	assert_ex(pass->isOpen());
	
	cli->open();
	assert_ex(cli->isOpen());
	
	cli->setPort(pass->port());
	cli->getHostByName("localhost");
	assert_ex(cli->isOpen());
	assert_ex(cli->port() == pass->port());
	
	cli->connect();
	assert_ex(act != NULL);
	assert_ex(client != NULL);
	assert_ex(act == pass);
	assert_ex(pass->isOpen());
	assert_ex(act->isOpen());
	assert_ex(cli->isOpen());
}

void CleanupStreamSockets(Socket** passive_server, Socket** active_server, Socket** client)
{
	(*passive_server)->close();
	delete *passive_server;
	*passive_server = NULL;
	
	(*active_server)->close();
	delete *active_server;
	*active_server = NULL;
	
	(*client)->close();
	delete *client;
	*client = NULL;
}

void CleanupDGramSockets(Socket** passive_server, Socket** active_server, Socket** client)
{
	(*passive_server)->close();
	delete *passive_server;
	*passive_server = NULL;
	*active_server = NULL;
	
	(*client)->close();
	delete *client;
	*client = NULL;
}














SOCKET_TEST(C_IO)
{
	
	
	dout << "Passive FD is " << srvsock->fd() << "\n";
	
	std::string writeMsg = "Hello";
	
	dout << "Writing...\n";
	int written = ::write(sock->fd(), writeMsg.c_str(), sizeof(char)*(writeMsg.length() + 1));
	dout << "Wrote " << written << " bytes." << std::endl;
	
	
	char cbuf[256];
	
	dout << "In FD is " << act_srvsock->fd() << std::endl;
	
	dout << "Reading...\n" << std::flush;
	int count = ::read(act_srvsock->fd(), cbuf, 256);
	dout << "Read " << count << " bytes." << std::endl;
	
	std::string str(cbuf);
	
	dout << str << "\n";
	
	assert_ex(str == writeMsg);
}


SOCKET_TEST(Wrapped_IO)
{
	std::string in_str = "Hello, world!";
	sock->write(in_str);
	
	assert_ex(act_srvsock->waitingData() == in_str.length() + 1);
	
	std::string out_str = act_srvsock->read();
	
	assert_ex(in_str.length() == out_str.length());
	assert_ex(in_str == out_str);
	
	std::string in_str2 = "ABC";
	std::string in_str3 = "123";
	
	sock->write(in_str2);
	sock->write(in_str3);
	
	std::string out_str2 = act_srvsock->read();
	
	std::string out_str3 = act_srvsock->read();
	
	if (act_srvsock != srvsock)
	{
		assert_ex(out_str2 == in_str2 + in_str3);
	}
	else
	{
		assert_ex(in_str2 == out_str2);
		assert_ex(in_str3 == out_str3);
	}
	
	
	
	std::string in_str4(255, 'a');
	
	sock->write(in_str4);
	
	std::string out_str4 = act_srvsock->read();
	
	assert_ex(out_str4 == in_str4);
	
	act_srvsock->readAll();
	
	std::string in_str5;
	std::string out_str5;
	{
		const int count = 256;
		const char placeHolder = 'a';
		in_str5 = std::string(count, placeHolder);
		sock->write(in_str5);
		assert_ex(act_srvsock->waitingData() == count+1);
		out_str5 = act_srvsock->read(count-1);
		
		assert_ex(in_str5 == out_str5 + placeHolder);
		
		std::string out_str5_2 = act_srvsock->read();
		if (act_srvsock != srvsock)
		{
			assert_ex(out_str5_2 == (std::string() + placeHolder));
		}
	}
	
	
	const int count_6 = 250;
	const char character_6 = 'U';
	std::string in_str6;
	in_str6 += character_6;
	for (int i = 0; i < count_6; ++i)
	{
		sock->write(in_str6);
	}
	
	std::string out_str6;
	if (act_srvsock != srvsock)
	{
		out_str6 = act_srvsock->readAll();
	}
	else
	{
		int msgCount = 0;
		while (act_srvsock->waitingData() > 0)
		{
			++msgCount;
			out_str6 += act_srvsock->read();
		}
		dout << "Read as " << msgCount << " messages.\n";
	}
	assert_ex(out_str6 == std::string(count_6, character_6));
	assert_ex(out_str6.length() == count_6);
	
	
	char* in_cstr7 = new char[8] { 'A', 'B', 'C', '\0', '1', '2', '3', '\0' };
	
	assert_ex(sock->write(in_cstr7, 8) == 8);
	
	std::string out_str7 = act_srvsock->read();
	
	assert_ex(out_str7 == "ABC123");
	
	delete[] in_cstr7;
	
	assert_ex(act_srvsock->waitingData() == 0);
	assert_ex(act_srvsock->readAll() == "");
	
	
	std::string in_str8_1 = "DEF";
	std::string in_str8_2 = "456";
	
	sock->write(in_str8_1);
	sock->write(in_str8_2);
	
	QUtils::sleep(100);
	
	std::string out_str8_1 = act_srvsock->read();
	std::string out_str8_2 = act_srvsock->read();
	
	if (act_srvsock != srvsock)
	{
		assert_ex(out_str8_1 == in_str8_1 + in_str8_2);
	}
	else
	{
		assert_ex(in_str8_1 == out_str8_1);
		assert_ex(in_str8_2 == out_str8_2);
	}
	
	
	
	if (act_srvsock != srvsock)
	{
	
	std::string in_str9_1 = "GHI";
	std::string in_str9_2 = "789";
	
	sock->write(in_str9_1);
	sock->write(in_str9_2);
	
	QUtils::sleep(500);
	
	
	std::string out_str9_1 = act_srvsock->read('\0');
	
	assert_ex(out_str9_1 == in_str9_1);
	
	std::string out_str9_2 = act_srvsock->read('\0');
	
	assert_ex(out_str9_2 == in_str9_2);
	
	assert_ex(act_srvsock->readAll() == "");
	
	}
}


SOCKET_TEST(Async)
{
	std::string in_str;
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		in_str += c;
	}
	std::string out_str;
	volatile std::atomic<bool> finished(false);
	finished = false;
	
	auto writeGet = std::async(std::launch::async, [&]()
	{
		finished = false;
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			sock->write(std::string() + c);
		}
		finished = true;
	});
	
	while (!finished)
	{
		out_str += act_srvsock->readAll();
	}
	out_str += act_srvsock->readAll();
	
	writeGet.get();
	//dout << "'" << out_str << "'\n";
	assert_ex(out_str == in_str);
	
	
	std::string in_str2 = "";
	std::string out_str2;
	volatile const int count2 = 1000;
	for (int i = 0; i < count2; ++i)
	{
		in_str2 += std::to_string(i);
	}
	finished = false;
	
	writeGet = std::async(std::launch::async, [&, count2]()
	{
		finished = false;
		for (int i = 0; i < count2; ++i)
		{
			sock->write(std::to_string(i));
		}
		finished = true;
	});
	
	while (!finished)
	{
		out_str2 += act_srvsock->readAll();
	}
	QUtils::sleep(100);
	out_str += act_srvsock->readAll();
	
	writeGet.get();
	//dout << "'" << out_str2 << "'\n";
	if (out_str2 != in_str2)
	{
		dout << "'" << in_str2 << "'\n'" << out_str2 << "'\n";
	}
	assert_ex(out_str2 == in_str2);
	
}


SOCKET_TEST(Peek)
{
	std::string in_str = "";
	const int interval = 3;
	int expectedLength;
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		in_str += c;
		sock->write(std::string() + c);
		expectedLength = (c - 'A' + 1) % interval;
		if (expectedLength == 0)
		{
			expectedLength = interval;
		}
		expectedLength *= 2;
		
		int prevWaiting = act_srvsock->waitingData();
		std::string tmp = act_srvsock->peek();
		if (prevWaiting == expectedLength)
		{
			assert_ex(act_srvsock->waitingData() == prevWaiting);
		}
		
		if ((c - 'A' + 1) % interval == 1)
		{
			assert_ex(act_srvsock->waitingData() > 0);
		}
		
		if (c - 'A' > 0 && (c - 'A' + 1) % interval == 0)
		{
			assert_ex(tmp.length() > 0);
			assert_ex(tmp[0] == in_str[0]);
			assert_ex(act_srvsock->readAll() == in_str);
			in_str = "";
		}
	}
}



SOCKET_TEST(WaitAll)
{
	std::string in_str = "ABC123";
	auto fut = std::async(std::launch::async, [in_str] (auto sock)
	{
		sock->write(in_str.substr(0, 3));
		QUtils::sleep(500);
		sock->write(in_str.substr(3));
	}, sock);
	
	
	auto out_str = act_srvsock->waitAll(8);
	assert_ex(out_str == in_str);
	assert_ex(act_srvsock->waitingData() == 0);
	
	std::string in_str2 = "";
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		in_str2 += c;
		sock->write(c);
	}
	
	auto out_str2 = act_srvsock->waitAll('Z' - 'A' + 1);
	assert_ex(out_str2 == in_str2);
	
	assert_ex(act_srvsock->waitingData() == 0);
	assert_ex(act_srvsock->readAll() == "");
	
	
	std::string in_str3 = "";
	const int rangeS = 20;
	const int rangeE = 30;
	for (char c = rangeS; c <= rangeE; ++c)
	{
		in_str3 += c;
		sock->write(c);
	}
	assert_ex(in_str3.length() == (rangeE - rangeS + 1));
	auto out_str3 = act_srvsock->waitAll(rangeE - rangeS + 1);
	assert_ex(out_str3.length() == in_str3.length());
	assert_ex(out_str3 == in_str3);
}


using nlohmann::json;

namespace ns {
struct Person
{
	std::string fname;
	std::string lname;
	unsigned long birth;
};

bool operator==(const Person p1, const Person p2)
{
	return (p1.fname == p2.fname && p1.lname == p2.lname && p1.birth == p2.birth);
}

bool operator!=(const Person p1, const Person p2)
{
	return !(p1 == p2);
}

void to_json(json& j, const Person& p)
{
	j["fname"] = p.fname;
	j["lname"] = p.lname;
	j["birth"] = p.birth;
}

void from_json(const json& j, Person& p)
{
	p.fname = j.at("fname").get<std::string>();
	p.lname = j.at("lname").get<std::string>();
	p.birth = j.at("birth").get<unsigned long>();
}
}

SOCKET_TEST(JSON)
{
	
	ns::Person in_p1{"Tyler", "Trebuchon", 10000};
	
	json in_j1;// = in_p1;
	ns::to_json(in_j1, in_p1);
	
	dout << "Writing...\n";
	sock->write(in_j1.dump());
	
	dout << "Reading...\n";
	std::string out_str1 = act_srvsock->read();
	
	dout << "Parsing...\n";
	json out_j1 = json::parse(out_str1);
	
	ns::Person out_p1;
	ns::from_json(out_j1, out_p1);
	
	assert_ex(in_p1 == out_p1);
	assert_ex(in_j1 == out_j1);
	assert_ex(in_j1.dump() == out_j1.dump());
	
	
	
	std::vector<std::string> fnames = {"Tyler", "Jerry", "Bob", "Bill"};
	
	std::vector<std::string> lnames = {"Trebuchon", "Matthews", "Terry", "Bridges"};
	
	std::vector<ns::Person> people;
	
	for (int i = 0; i < fnames.size(); ++i)
	{
		people.push_back({fnames[i], lnames[i], 0-i});
	}
	
	
	
	json in_j2;
	for (int i = 0; i < people.size(); ++i)
	{
		to_json(in_j2["p" + std::to_string(i)], people[i]);
	}
	
	sock->write(in_j2.dump());
	
	std::string out_str2 = act_srvsock->read();
	
	json out_j2 = json::parse(out_str2);
	
	assert_ex(out_j2 == in_j2);
	
	
	json in_j3 = json::array();
	for (int i = 0; i < people.size(); ++i)
	{
		to_json(in_j3[i], people[i]);
	}
	
	sock->write(in_j3.dump(4));
	
	std::string out_str3 = act_srvsock->read();
	
	json out_j3 = json::parse(out_str3);
	
	assert_ex(out_j3 == in_j3);
	
	sock->write("[");
	sock->write(in_j1.dump(4));
	sock->write(",");
	sock->write(in_j2.dump(4));
	sock->write(",");
	sock->write(in_j3.dump(4));
	sock->write("]");
	
	std::string out_str4 = act_srvsock->readAll();
	
	json out_j4 = json::parse(out_str4);
	
	
}

SOCKET_TEST(Raw_IO)
{
	const int count1 = 500;
	int in_nums1[count1];
	for (int i = 0; i < count1; ++i)
	{
		in_nums1[i] = rand();
	}
	
	assert_ex(sock->write((void*)in_nums1, sizeof(int)*count1) == sizeof(int)*count1);
	
	int* out_nums1 = new int[count1];
	
	assert_ex(act_srvsock->read(out_nums1, sizeof(int)*count1) == sizeof(int)*count1);
	
	for (int i = 0; i < count1; ++i)
	{
		assert_ex(out_nums1[i] == in_nums1[i]);
	}
	
	delete[] out_nums1;
}