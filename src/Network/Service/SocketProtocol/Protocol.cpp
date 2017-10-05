
#include <QUtils/Network/Service/SocketProtocol/Protocol.h>
/*
#include <QUtils/Network/Service/SocketProtocol/Header.h>
#include <QUtils/Byte.h>
#include <QUtils/Network/Sockets.h>

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	MsgLen_t Protocol::GetMsgLength(const char* header)
	{
		return MsgLen_Info::Read(header+QUTILS_NETWORK_PROTO_MSG_ID_SIZE);
	}
	
	Header* Protocol::ParseHeader(const char* header, const MsgLen_t msgLen)
	{
		Header* hd = new Header();
		
		hd->size = msgLen;
		hd->id = MsgID_Info::Read(header);
		hd->checksum = MsgChecksum_Info::Read(header+QUTILS_NETWORK_PROTO_MSG_ID_SIZE+QUTILS_NETWORK_PROTO_MSG_LEN_SIZE);
		
		return hd;
	}
	
	char* Protocol::WriteHeader(const Header* header)
	{
		char* rawHeader = new char[HeaderLength];
		
		MsgID_Info::Write(header->id, rawHeader);
		MsgLen_Info::Write(header->size, &rawHeader[QUTILS_NETWORK_PROTO_MSG_ID_SIZE]);
		
		MsgChecksum_Info::Write(header->checksum, rawHeader+QUTILS_NETWORK_PROTO_MSG_ID_SIZE+QUTILS_NETWORK_PROTO_MSG_LEN_SIZE);
		
		return rawHeader;
	}
	
	MsgChecksum_t Protocol::CalculateChecksum(const char* msg, const MsgLen_t len)
	{
		MsgChecksum_t sum = 0;
		
		for (auto i = 0; i < len; ++i)
		{
			sum += (int)msg[i];
			sum %= MsgChecksum_Info::Max;
		}
		
		return sum;
	}
	
	bool Protocol::VerifyChecksum(Header* header, const char* msg)
	{
		return (header->checksum == CalculateChecksum(msg, header->size));
	}
	
	
}
}
}*/