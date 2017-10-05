#pragma once
#include "Types.h"

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	template <class Spec = DefaultSpec>
	struct Header
	{
		typename Spec::MsgID_t id;
		typename Spec::MsgLen_t size;
		typename Spec::MsgChecksum_t checksum;
	};
	
}
}
}