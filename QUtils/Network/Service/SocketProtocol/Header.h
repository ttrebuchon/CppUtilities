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
		
		Header() : id(0), size(0), checksum(0), wideChars(false), responseRequired(false), integrityResponse(false), badMessage(false)
		{
			
		}
		
		static Header* GoodMessageResponse()
		{
			auto hd = new Header();
			hd->integrityResponse = true;
			hd->id = Spec::MsgID_Info::Max;
			return hd;
		}
		
		static Header* BadMessageResponse()
		{
			auto hd = new Header();
			hd->integrityResponse = true;
			hd->id = Spec::MsgID_Info::Max;
			hd->badMessage = true;
			return hd;
		}
	};
	
}
}
}