#include "../Tests_Helpers.h"

#include <QUtils/Network/Sockets.h>
#include <QUtils/Network/Service/SocketProtocol/Protocol.h>
#include <QUtils/Network/Service/SocketProtocol/Header.h>

using QUtils::Network::Socket;

namespace Network_ServiceProtocol_Test
{

void InitStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void InitDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

void CleanupStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void CleanupDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

template <int>
char* getTestHeader(unsigned long* size);

template <int>
void verifyTestHeader(const QUtils::Network::SocketProtocol::Header*);

}



using namespace Network_ServiceProtocol_Test;

template <int>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock);

#define HEADER_SIZE QUTILS_NETWORK_PROTO_MSG_ID_SIZE + QUTILS_NETWORK_PROTO_MSG_LEN_SIZE + QUTILS_NETWORK_PROTO_MSG_CHECKSUM_SIZE

DEF_TEST(Network_ServiceProtocol)
{
	Socket *passive, *active, *client;
	
	#define RUN_TEST(x) \
	InitStreamSockets(&passive, &active, &client); \
	testHeader<x>(passive, active, client); \
	CleanupStreamSockets(&passive, &active, &client);
	
	
	RUN_TEST(0);
	RUN_TEST(1);
	RUN_TEST(2);
	
	
	return true;
}

using QUtils::Network::SocketProtocol::MsgLen_t;
using QUtils::Network::SocketProtocol::MsgID_t;

template <int N>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock)
{
	unsigned long size;
	char* data = getTestHeader<N>(&size);
	assert_ex(data != NULL);
	assert_ex(size > 0);
	
	sock->write(data, size);
	delete[] data;
	
	char* rawHeader = new char[QUtils::Network::SocketProtocol::Protocol::HeaderLength];
	
	act_srvsock->read(
	rawHeader,
	QUtils::Network::SocketProtocol::
	Protocol::HeaderLength
	);
	
	auto length = QUtils::Network::SocketProtocol::Protocol::GetMsgLength(rawHeader);
	
	
	char* body = new char[length];
	act_srvsock->read(body, length);
	auto hd = QUtils::Network::SocketProtocol::Protocol::ParseHeader(rawHeader, length);
	verifyTestHeader<N>(hd);
	delete hd;
	delete[] body;
	delete[] rawHeader;
	assert_ex(act_srvsock->waitingData() == 0);
}



namespace Network_ServiceProtocol_Test
{
	template <>
	char* getTestHeader<0>(unsigned long* size)
	{
		assert_ex(QUTILS_NETWORK_PROTO_MSG_ID_SIZE == 1);
		assert_ex(HEADER_SIZE == QUtils::Network::SocketProtocol::Protocol::HeaderLength);
		const unsigned int MsgLen = 5;
		*size = HEADER_SIZE + MsgLen;
		char* data = new char[*size];
		
		data[0] = 1;
		*(unsigned int*)&data[QUTILS_NETWORK_PROTO_MSG_ID_SIZE] = htonl(MsgLen);
		
		
		
		return data;
	}
	
	template <>
	void verifyTestHeader<0>(const QUtils::Network::SocketProtocol::Header* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->id == 1);
		assert_ex(hd->size == 5);
	}
	
	
	
	
	
	
	
	
	template <>
	char* getTestHeader<1>(unsigned long* size)
	{
		assert_ex(QUTILS_NETWORK_PROTO_MSG_ID_SIZE == 1);
		assert_ex(HEADER_SIZE == QUtils::Network::SocketProtocol::Protocol::HeaderLength);
		const unsigned int MsgLen = 400;
		*size = HEADER_SIZE + MsgLen;
		char* data = new char[*size];
		
		data[0] = 255;
		*(unsigned int*)&data[QUTILS_NETWORK_PROTO_MSG_ID_SIZE] = htonl(MsgLen);
	}
	
	template <>
	void verifyTestHeader<1>(const QUtils::Network::SocketProtocol::Header* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->size == 400);
		assert_ex(hd->id == 255);
	}
	
	
	
	
	
	
	
	
	template <>
	char* getTestHeader<2>(unsigned long* size)
	{
		assert_ex(QUTILS_NETWORK_PROTO_MSG_ID_SIZE == 1);
		assert_ex(HEADER_SIZE == QUtils::Network::SocketProtocol::Protocol::HeaderLength);
		const unsigned int MsgLen = 400;
		*size = HEADER_SIZE + MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header();
		hd->id = 128;
		hd->size = MsgLen;
		hd->checksum = 40;
		char* raw = QUtils::Network::SocketProtocol::Protocol::WriteHeader(hd);
		delete hd;
		return raw;
	}
	
	template <>
	void verifyTestHeader<2>(const QUtils::Network::SocketProtocol::Header* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->size == 400);
		assert_ex(hd->id == 128);
		std::cout << hd->checksum << "\n";
		assert_ex(hd->checksum == 40);
	}
}














































































#include <future>


using QUtils::Network::INetSocket;

namespace Network_ServiceProtocol_Test
{


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

}