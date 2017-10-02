#include "../Tests_Helpers.h"
#include <QUtils/Network/Socket.h>
#include <future>
#include <unistd.h>
#include <atomic>

using namespace QUtils::Network;

#define SOCKET_TEST(x) void x##_SocketTest(Socket* srvsock, Socket* act_srvsock, Socket* sock)

SOCKET_TEST(C_IO);
SOCKET_TEST(Wrapped_IO);
SOCKET_TEST(Async);

void InitStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void InitDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

void CleanupStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void CleanupDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);







DEF_TEST(Network_Sockets)
{
	Socket *active, *passive, *client;
	
	#define RUN_TEST(x, y) \
	dout << "\n\nInitializing " << #x << " sockets...\n"; \
	Init##x##Sockets(&passive, &active, &client); \
	dout << "Running Test '" << #y << "_SocketTest'...\n"; \
	y##_SocketTest(passive, active, client); \
	dout << "Cleaning up sockets...\n\n\n"; \
	Cleanup##x##Sockets(&passive, &active, &client)
	
	
	
	
	
	RUN_TEST(Stream, C_IO);
	RUN_TEST(DGram, C_IO);
	RUN_TEST(Stream, Wrapped_IO);
	RUN_TEST(DGram, Wrapped_IO);
	RUN_TEST(Stream, Async);
	RUN_TEST(DGram, Async);
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
	dout << "'" << out_str << "'\n";
	
	assert_ex(in_str.length() == out_str.length());
	assert_ex(in_str == out_str);
	
	std::string in_str2 = "ABC";
	std::string in_str3 = "123";
	
	sock->write(in_str2);
	sock->write(in_str3);
	
	std::string out_str2 = act_srvsock->read();
	dout << "'" << out_str2 << "'\n" << std::flush;
	dout << "Length: " << out_str2.length() << std::endl;
	
	std::string out_str3 = act_srvsock->read();
	dout << "'" << out_str3 << "'\n" << std::flush;
	dout << "Length: " << out_str3.length() << std::endl;
	
	if (act_srvsock != srvsock)
	{
		//dout << "'" << in_str
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
	out_str += act_srvsock->readAll();
	
	writeGet.get();
	//dout << "'" << out_str2 << "'\n";
	assert_ex(out_str2 == in_str2);
	
}