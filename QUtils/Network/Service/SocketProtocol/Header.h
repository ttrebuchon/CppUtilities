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
		bool wideChars;
		bool responseRequired;
		bool integrityResponse;
		bool badMessage;
		
		constexpr static auto Length = Spec::Header_Size;
		
		void setGoodMessageResponse()
		{
			integrityResponse = true;
			id = Spec::MsgID_Info::Max;
			badMessage = false;
		}
		
		void setBadMessageResponse()
		{
			integrityResponse = true;
			id = Spec::MsgID_Info::Max;
			badMessage = true;
		}
		
		Header() : id(0), size(0), checksum(0), wideChars(false), responseRequired(false), integrityResponse(false), badMessage(false)
		{
			
		}
	};
	
}
}
}