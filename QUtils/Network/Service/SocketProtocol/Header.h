#pragma once
#include "Types.h"

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	struct Header
	{
		MsgID_t id;
		MsgLen_t size;
		MsgChecksum_t checksum;
	};
	
}
}
}