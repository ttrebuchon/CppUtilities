#include "../Tests_Helpers.h"
#include <QUtils/Network/Socket.h>
#include <future>
#include <unistd.h>

void StreamSocketTest();
void DGramSocketTest();

DEF_TEST(Network_Sockets)
{
	StreamSocketTest();
	DGramSocketTest();
	return true;
}


void StreamSocketTest()
{
	QUtils::Network::INetSocket sock(SOCK_STREAM);
	QUtils::Network::INetSocket srvsock(SOCK_STREAM);
	
	srvsock.open();
	assert_ex(srvsock.isOpen());
	dout << "Server socket opened." << std::endl;
	srvsock.bind();
	assert_ex(srvsock.isOpen());
	dout << "Server socket bound.\n";
	dout << "Server socket port: " << srvsock.port() << "\n";
	
	sock.open();
	assert_ex(sock.isOpen());
	sock.setPort(srvsock.port());
	assert_ex(sock.isOpen());
	sock.getHostByName("localhost");
	assert_ex(sock.isOpen());
	
	QUtils::Network::Socket* act_srvsock;
	
	srvsock.listen(10);
	auto accept = std::async(std::launch::async, [](auto ptr) { return ptr->accept(); }, &srvsock);
	sock.connect();
	act_srvsock = accept.get();
	
	assert_ex(srvsock.isOpen());
	assert_ex(sock.isOpen());
	assert_ex(act_srvsock->isOpen());
	
	dout << "Passive FD is " << srvsock.fd() << "\n";
	{
	
	std::string writeMsg = "Hello";
	
	dout << "Writing...\n";
	int written = ::write(sock.fd(), writeMsg.c_str(), sizeof(char)*(writeMsg.length() + 1));
	dout << "Wrote " << written << " bytes." << std::endl;
	
	
	char cbuf[256];
	
	dout << "In FD is " << act_srvsock->fd() << std::endl;
	
	dout << "Reading...\n" << std::flush;
	int count = ::read(act_srvsock->fd(), cbuf, 256);
	dout << "Read " << count << " bytes." << std::endl;
	
	std::string str(cbuf);
	
	dout << str << "\n";
	
	assert_ex(str == writeMsg);
	
	
	dout << "Closing active server socket...\n";
	act_srvsock->close();
	delete act_srvsock;
	dout << "Closed." << std::endl;
	act_srvsock = NULL;
	
	
	}
	
	sock.close();
	assert_ex(!sock.isOpen());
	
	srvsock.close();
	assert_ex(!srvsock.isOpen());
}




void DGramSocketTest()
{
	QUtils::Network::INetSocket sock(SOCK_DGRAM);
	QUtils::Network::INetSocket srvsock(SOCK_DGRAM);
	
	srvsock.open();
	assert_ex(srvsock.isOpen());
	dout << "Server socket opened." << std::endl;
	srvsock.bind();
	assert_ex(srvsock.isOpen());
	dout << "Server socket bound.\n";
	dout << "Server socket port: " << srvsock.port() << "\n";
	
	sock.open();
	assert_ex(sock.isOpen());
	sock.setPort(srvsock.port());
	assert_ex(sock.isOpen());
	sock.getHostByName("localhost");
	assert_ex(sock.isOpen());
	
	QUtils::Network::Socket* act_srvsock;
	
	sock.connect();
	act_srvsock = &srvsock;
	
	assert_ex(srvsock.isOpen());
	assert_ex(sock.isOpen());
	assert_ex(act_srvsock->isOpen());
	
	dout << "Passive FD is " << srvsock.fd() << "\n";
	{
	
	std::string writeMsg = "Hello";
	
	dout << "Writing...\n";
	int written = ::write(sock.fd(), writeMsg.c_str(), sizeof(char)*(writeMsg.length() + 1));
	dout << "Wrote " << written << " bytes." << std::endl;
	
	
	char cbuf[256];
	
	dout << "In FD is " << act_srvsock->fd() << std::endl;
	
	dout << "Reading...\n" << std::flush;
	int count = ::read(act_srvsock->fd(), cbuf, 256);
	dout << "Read " << count << " bytes." << std::endl;
	
	std::string str(cbuf);
	
	dout << str << "\n";
	
	assert_ex(str == writeMsg);
	
	act_srvsock = NULL;
	
	
	}
	
	sock.close();
	assert_ex(!sock.isOpen());
	
	srvsock.close();
	assert_ex(!srvsock.isOpen());
}