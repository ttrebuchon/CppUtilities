#pragma once
#include "Types.h"

namespace QUtils { namespace Network {
class Socket;

namespace SocketProtocol {
	
	struct Header;
	
	//Static Class
	class Protocol
	{
		public:
		
		static const size_t HeaderLength = QUTILS_NETWORK_PROTO_MSG_ID_SIZE + QUTILS_NETWORK_PROTO_MSG_LEN_SIZE + QUTILS_NETWORK_PROTO_MSG_CHECKSUM_SIZE;
		
		/*static MsgLen_t ReadLength(const char length, MsgLen_t* readMore);
		static MsgLen_t ReadLength(const char* extendedLength);
		
		static Header* ParseHeader(const char* msg, const MsgLen_t size);*/
		
		static MsgLen_t GetMsgLength(const char* header);
		static Header* ParseHeader(const char* header, const MsgLen_t msgLen);
		
		static char* WriteHeader(const Header*);
	};
	
}
}
}