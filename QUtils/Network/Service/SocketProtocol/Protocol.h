#pragma once
#include "Types.h"
#include "Header.h"

namespace QUtils { namespace Network {
class Socket;

namespace SocketProtocol {
	
	
	//Static Class
	template <class Spec = DefaultSpec>
	class Protocol
	{
		public:
		
		constexpr static size_t HeaderLength = Spec::Header_Size;
		
		static typename Spec::MsgLen_t GetMsgLength(const unsigned char* header);
		static Header<Spec>* ParseHeader(const unsigned char* header, const typename Spec::MsgLen_t msgLen);
		static Header<Spec>* ParseHeader(const unsigned char* header);
		
		static unsigned char* WriteHeader(const Header<Spec>*);
		
		static typename Spec::MsgChecksum_t CalculateChecksum(const unsigned char* msg, const typename Spec::MsgLen_t len);
		static bool VerifyChecksum(Header<Spec>* header, const unsigned char* msg);
	};
	
}
}
}

#include "Protocol.hpp"