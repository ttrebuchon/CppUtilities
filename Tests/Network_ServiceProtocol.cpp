#include "../Tests_Helpers.h"

#include <QUtils/Network/Sockets.h>
#include <QUtils/Network/Service/SocketProtocol/Protocol.h>
#include <QUtils/Network/Service/SocketProtocol/Header.h>

#include <QUtils/Network/Service/SocketProtocol/Messenger.h>

using QUtils::Network::Socket;

namespace Network_ServiceProtocol_Test
{

void InitStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void InitDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

void CleanupStreamSockets(Socket** passive_server, Socket** active_server, Socket** client);
void CleanupDGramSockets(Socket** passive_server, Socket** active_server, Socket** client);

template <int>
unsigned char* getTestHeader(unsigned long* size);

template <int>
unsigned char* getTestBody()
{
	return NULL;
}

using QUtils::Network::SocketProtocol::DefaultSpec;

template <int>
void verifyTestHeader(const QUtils::Network::SocketProtocol::Header<>*);


template <class S, int>
void verifyTestHeader(const QUtils::Network::SocketProtocol::Header<S>*);

}


using namespace Network_ServiceProtocol_Test;

template <int>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock);

template <class, int>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock);







typedef QUtils::Network::SocketProtocol::HeaderSpec<2, 4, 3, 1> Spec6;







void MessengerTest();



#define HEADER_SIZE DefaultSpec::Header_Size

DEF_TEST(Network_ServiceProtocol)
{
	Socket *passive, *active, *client;
	
	#define RUN_TEST(x) \
	dout << "Running Test " << x << "...\n"; \
	InitStreamSockets(&passive, &active, &client); \
	testHeader<x>(passive, active, client); \
	CleanupStreamSockets(&passive, &active, &client);
	
	
	#define RUN_TEST_S(x, S) \
	dout << "Running Test " << x << "...\n"; \
	InitStreamSockets(&passive, &active, &client); \
	testHeader<S, x>(passive, active, client); \
	CleanupStreamSockets(&passive, &active, &client);
	
	
	RUN_TEST(0);
	RUN_TEST(1);
	RUN_TEST(2);
	RUN_TEST(3);
	RUN_TEST(4);
	RUN_TEST(5);
	RUN_TEST_S(6, Spec6);
	MessengerTest();
	
	
	return true;
}

typedef QUtils::Network::SocketProtocol::DefaultSpec::MsgID_t MsgID_t;
typedef QUtils::Network::SocketProtocol::DefaultSpec::MsgLen_t MsgLen_t;
typedef QUtils::Network::SocketProtocol::DefaultSpec::MsgChecksum_t MsgChecksum_t;

using QUtils::Network::SocketProtocol::Protocol;

template <int N>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock)
{
	unsigned long bodySize;
	unsigned char* header_in = getTestHeader<N>(&bodySize);
	assert_ex(header_in != NULL);
	
	assert_ex(sock->write(header_in, HEADER_SIZE) == HEADER_SIZE);
	delete[] header_in;
	header_in = NULL;
	
	unsigned char* body_in = getTestBody<N>();
	if (body_in != NULL)
	{
		assert_ex(sock->write(body_in, bodySize) == bodySize);
		delete[] body_in;
	}
	
	
	unsigned char* rawHeader = new unsigned char[Protocol<>::HeaderLength];
	
	assert_ex(
	act_srvsock->read(
		rawHeader,
		Protocol<>::HeaderLength
	) == Protocol<>::HeaderLength);
	
	auto length = QUtils::Network::SocketProtocol::Protocol<>::GetMsgLength(rawHeader);
	assert_ex(length == bodySize);
	
	
	unsigned char* body = NULL;
	if (body_in != NULL)
	{
		body = new unsigned char[length];
		assert_ex(act_srvsock->read(body, length) == length);
	}
	auto hd = Protocol<>::ParseHeader(rawHeader, length);
	verifyTestHeader<N>(hd);
	
	if (body != NULL)
	{
		assert_ex(Protocol<>::VerifyChecksum(hd, body));
		delete[] body;
	}
	
	
	delete hd;
	delete[] rawHeader;
	assert_ex(act_srvsock->waitingData() == 0);
}


template <class S, int N>
void testHeader(Socket* srvsock, Socket* act_srvsock, Socket* sock)
{
	unsigned long bodySize;
	unsigned char* header_in = getTestHeader<N>(&bodySize);
	assert_ex(header_in != NULL);
	
	assert_ex(sock->write(header_in, S::Header_Size) == S::Header_Size);
	delete[] header_in;
	header_in = NULL;
	
	unsigned char* body_in = getTestBody<N>();
	if (body_in != NULL)
	{
		assert_ex(sock->write(body_in, bodySize) == bodySize);
		delete[] body_in;
	}
	
	
	unsigned char* rawHeader = new unsigned char[Protocol<S>::HeaderLength];
	
	assert_ex(
	act_srvsock->read(
		rawHeader,
		Protocol<S>::HeaderLength
	) == Protocol<S>::HeaderLength);
	
	auto length = QUtils::Network::SocketProtocol::Protocol<S>::GetMsgLength(rawHeader);
	assert_ex(length == bodySize);
	
	
	unsigned char* body = NULL;
	if (body_in != NULL)
	{
		body = new unsigned char[length];
		assert_ex(act_srvsock->read(body, length) == length);
	}
	auto hd = Protocol<S>::ParseHeader(rawHeader, length);
	verifyTestHeader<S, N>(hd);
	
	if (body != NULL)
	{
		assert_ex(Protocol<S>::VerifyChecksum(hd, body));
		delete[] body;
	}
	
	
	delete hd;
	delete[] rawHeader;
	assert_ex(act_srvsock->waitingData() == 0);
}



namespace Network_ServiceProtocol_Test
{
	template <>
	unsigned char* getTestHeader<0>(unsigned long* size)
	{
		assert_ex(DefaultSpec::ID_Size == 1);
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		const unsigned int MsgLen = 5;
		*size = MsgLen;
		unsigned char* data = new unsigned char[HEADER_SIZE];
		
		static_assert(DefaultSpec::ID_Size == 1, "Update values in test");
		data[0] = 1;
		static_assert(DefaultSpec::Length_Size >= 1, "Update values in test");
		::memset(&data[1], 0, DefaultSpec::Length_Size-1);
		
		
		//0x05 == 5, so set chars manually
		data[DefaultSpec::Length_Size] = 0x05;
		
		
		return data;
	}
	
	template <>
	void verifyTestHeader<0>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->id == 1);
		assert_ex(hd->size == 5);
	}
	
	
	
	
	
	
	
	
	template <>
	unsigned char* getTestHeader<1>(unsigned long* size)
	{
		assert_ex(DefaultSpec::ID_Size == 1);
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		const unsigned int MsgLen = 400;
		*size = MsgLen;
		char* data = new char[HEADER_SIZE];
		
		static_assert(DefaultSpec::ID_Size == 1, "Update values in test");
		data[0] = 255;
		
		static_assert(DefaultSpec::Length_Size >= 2, "Update values in test");
		::memset(&data[1], 0, DefaultSpec::Length_Size-2);
		
		
		//0x0190 == 400, so set chars manually
		data[DefaultSpec::Length_Size-1] = 0x01;
		data[DefaultSpec::Length_Size] = 0x90;
		
	}
	
	template <>
	void verifyTestHeader<1>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		assert_ex(hd != NULL);
		if (hd->size != 400)
		{
			dout << "hd->size: " << (unsigned long long)hd->size << "\n";
		}
		assert_ex(hd->size == 400);
		assert_ex(hd->id == 255);
	}
	
	
	
	
	
	
	
	
	template <>
	unsigned char* getTestHeader<2>(unsigned long* size)
	{
		assert_ex(DefaultSpec::ID_Size == 1);
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		const unsigned int MsgLen = 400;
		*size = MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header<>();
		hd->id = 128;
		hd->size = MsgLen;
		hd->checksum = 40;
		unsigned char* raw = QUtils::Network::SocketProtocol::Protocol<>::WriteHeader(hd);
		delete hd;
		return raw;
	}
	
	template <>
	void verifyTestHeader<2>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->size == 400);
		assert_ex(hd->id == 128);
		assert_ex(hd->checksum == 40);
	}
	
	
	
	
	
	
	template <>
	unsigned char* getTestHeader<3>(unsigned long* size)
	{
		assert_ex(DefaultSpec::ID_Size == 1);
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		const unsigned long MsgLen = 0x200;
		*size = MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header<>();
		hd->id = 42;
		hd->size = MsgLen;
		hd->checksum = 0x010000;
		unsigned char* raw = QUtils::Network::SocketProtocol::Protocol<>::WriteHeader(hd);
		delete hd;
		return raw;
	}
	
	template <>
	unsigned char* getTestBody<3>()
	{
		const auto len = 0x200;
		unsigned char* body = new unsigned char[len];
		::memset(body, 0, len);
		const unsigned char val = (0x010000/len);
		static_assert(0x010000/len == 0x80, "");
		static_assert(val == 0x80, "");
		
		static_assert(val*len == 0x010000, "");
		unsigned long long tally = 0;
		for (auto ptr = body; ptr < len+body; ++ptr)
		{
			*ptr = val;
			tally += val;
			tally %= DefaultSpec::MsgChecksum_Info::Max;
		}
		assert_ex(tally == 0x010000);
		return body;
	}
	
	template <>
	void verifyTestHeader<3>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		assert_ex(hd != NULL);
		assert_ex(hd->size == 0x200);
		assert_ex(hd->id == 42);
		assert_ex(hd->wideChars == false);
		assert_ex(hd->checksum == 0x010000);
	}
	
	
	
	
	
	template <>
	unsigned char* getTestHeader<4>(unsigned long* size)
	{
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		
		const std::string body = "Hello, world!";
		
		const unsigned long MsgLen = body.length();
		*size = MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header<>();
		hd->id = 56;
		hd->size = MsgLen;
		hd->checksum = Protocol<>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		hd->wideChars = false;
		unsigned char* raw = QUtils::Network::SocketProtocol::Protocol<>::WriteHeader(hd);
		delete hd;
		return raw;
	}
	
	template <>
	unsigned char* getTestBody<4>()
	{
		const std::string bodyStr = "Hello, world!";
		//We don't want the null terminator
		unsigned char* body = new unsigned char[bodyStr.length()];
		::memcpy(body, bodyStr.c_str(), bodyStr.length());
		return body;
	}
	
	template <>
	void verifyTestHeader<4>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		const std::string body = "Hello, world!";
		
		const unsigned long MsgLen = body.length();
		const auto chksum = Protocol<>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		assert_ex(hd != NULL);
		assert_ex(hd->size == MsgLen);
		assert_ex(hd->id == 56);
		assert_ex(hd->checksum == chksum);
		unsigned long long tally = 0;
		for (int i = 0; i < body.length(); ++i)
		{
			tally += body[i];
			tally %= DefaultSpec::MsgChecksum_Info::Max;
		}
		assert_ex(tally == chksum);
		assert_ex(!hd->wideChars);
	}










	template <>
	unsigned char* getTestHeader<5>(unsigned long* size)
	{
		assert_ex(HEADER_SIZE == Protocol<>::HeaderLength);
		const std::wstring body = L"Hello, world!";

		const unsigned long MsgLen = body.length()*sizeof(wchar_t);
		*size = MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header<>();
		hd->id = 56;
		hd->size = MsgLen;
		hd->checksum = Protocol<>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		hd->wideChars = true;
		unsigned char* raw = QUtils::Network::SocketProtocol::Protocol<>::WriteHeader(hd);
		delete hd;
		return raw;
	}

	template <>
	unsigned char* getTestBody<5>()
	{
		const std::wstring bodyStr = L"Hello, world!";
		//We don't want the null terminator
		unsigned char* body = new unsigned char[bodyStr.length()*sizeof(wchar_t)];
		::memcpy(body, bodyStr.c_str(), bodyStr.length()*sizeof(wchar_t));
		return body;
	}

	template <>
	void verifyTestHeader<5>(const QUtils::Network::SocketProtocol::Header<>* hd)
	{
		const std::wstring body = L"Hello, world!";

		const unsigned long MsgLen = body.length()*sizeof(wchar_t);
		const auto chksum = Protocol<>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		assert_ex(hd != NULL);
		assert_ex(hd->size == MsgLen);
		assert_ex(hd->id == 56);
		assert_ex(hd->checksum == chksum);
		unsigned long long tally = 0;
		for (int i = 0; i < body.length(); ++i)
		{
			tally += body[i];
			tally %= DefaultSpec::MsgChecksum_Info::Max;
		}
		assert_ex(tally == chksum);
		assert_ex(hd->wideChars);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <>
	unsigned char* getTestHeader<6>(unsigned long* size)
	{
		const std::wstring body = L"Hello, world!";

		const unsigned long MsgLen = body.length()*sizeof(wchar_t);
		*size = MsgLen;
		auto hd = new QUtils::Network::SocketProtocol::Header<Spec6>();
		assert_ex(sizeof(Spec6::MsgID_t) == 4);
		assert_ex(Spec6::Header_Size == 10);
		hd->id = 65592; //2^16 + 56
		hd->size = MsgLen;
		hd->checksum = Protocol<Spec6>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		hd->wideChars = true;
		unsigned char* raw = QUtils::Network::SocketProtocol::Protocol<Spec6>::WriteHeader(hd);
		delete hd;
		return raw;
	}

	template <>
	unsigned char* getTestBody<6>()
	{
		const std::wstring bodyStr = L"Hello, world!";
		//We don't want the null terminator
		unsigned char* body = new unsigned char[bodyStr.length()*sizeof(wchar_t)];
		::memcpy(body, bodyStr.c_str(), bodyStr.length()*sizeof(wchar_t));
		return body;
	}

	template <>
	void verifyTestHeader<Spec6, 6>(const QUtils::Network::SocketProtocol::Header<Spec6>* hd)
	{
		const std::wstring body = L"Hello, world!";

		const unsigned long MsgLen = body.length()*sizeof(wchar_t);
		const auto chksum = Protocol<Spec6>::CalculateChecksum((const unsigned char*)body.c_str(), MsgLen);
		assert_ex(hd != NULL);
		assert_ex(hd->size == MsgLen);
		assert_ex(hd->id == 56);
		assert_ex(hd->checksum == chksum);
		unsigned long long tally = 0;
		for (int i = 0; i < body.length(); ++i)
		{
			tally += body[i];
			tally %= Spec6::MsgChecksum_Info::Max;
		}
		assert_ex(tally == chksum);
		assert_ex(hd->wideChars);
	}
}


void MessengerTest()
{
	dout << "Testing Messenger...\n";
	using namespace QUtils::Network::SocketProtocol;
	
	typedef DefaultSpec Spec;
	
	Socket *passive, *active, *client;
	
	passive = active = client = NULL;
	
	try
	{
		InitStreamSockets(&passive, &active, &client);
		
		
		auto msgr = Messenger::Create<Spec>(client);
		
		auto srv = Messenger::Create<Spec>(active);
		
		assert_ex(msgr != NULL);
		assert_ex(srv != NULL);
		
		
		{
			std::string body_in = "Hello";
			msgr->send(reinterpret_cast<const unsigned char*>(body_in.c_str()), body_in.length()+1, false, false);
			
			
			unsigned long long len_out, id_out;
			bool wideChars_out, responseRequired_out;
			
			unsigned char* body_out = srv->receive(len_out, wideChars_out, responseRequired_out, id_out);
			
			assert_ex(len_out == body_in.length()+1);
			assert_ex(!wideChars_out);
			assert_ex(!responseRequired_out);
			
			
			unsigned long long len_r, id_r;
			bool wideChars_r, responseRequired_r;
			
			assert_ex(msgr->receive(len_r, wideChars_r, responseRequired_r, id_r) == NULL);
			
		}
		
		
	}
	catch (...)
	{
		if (passive != NULL)
		{
			CleanupStreamSockets(&passive, &active, &client);
		}
		throw;
	}
	
	CleanupStreamSockets(&passive, &active, &client);
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