#pragma once

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	struct Header;
	
	class Protocol
	{
		public:
		
		static Header* ParseHeader(const char*, unsigned int size);
	};
	
}
}
}