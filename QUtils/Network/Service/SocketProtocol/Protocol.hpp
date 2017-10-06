#pragma once

#include "Protocol.h"
#include "Header.h"

namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	template <class Spec>
	typename Spec::MsgLen_t Protocol<Spec>::GetMsgLength(const unsigned char* header)
	{
		return Spec::MsgLen_Info::Read(header+Spec::ID_Size);
	}
	
	template <class Spec>
	Header<Spec>* Protocol<Spec>::ParseHeader(const unsigned char* header, const typename Spec::MsgLen_t msgLen)
	{
		Header<Spec>* hd = new Header<Spec>();
		
		hd->size = msgLen;
		hd->id = Spec::MsgID_Info::Read(header);
		hd->checksum = Spec::MsgChecksum_Info::Read(header+Spec::ID_Size+Spec::Length_Size);
		
		return hd;
	}
	
	template <class Spec>
	unsigned char* Protocol<Spec>::WriteHeader(const Header<Spec>* header)
	{
		unsigned char* rawHeader = new unsigned char[HeaderLength];
		
		Spec::MsgID_Info::Write(header->id, rawHeader);
		Spec::MsgLen_Info::Write(header->size, &rawHeader[Spec::ID_Size]);
		
		Spec::MsgChecksum_Info::Write(header->checksum, rawHeader+Spec::ID_Size+Spec::Length_Size);
		
		return rawHeader;
	}
	
	template <class Spec>
	typename Spec::MsgChecksum_t Protocol<Spec>::CalculateChecksum(const unsigned char* msg, const typename Spec::MsgLen_t len)
	{
		typename Spec::MsgChecksum_t sum = 0;
		
		for (auto i = 0; i < len; ++i)
		{
			sum += (int)msg[i];
			sum %= Spec::MsgChecksum_Info::Max;
		}
		
		return sum;
	}
	
	template <class Spec>
	bool Protocol<Spec>::VerifyChecksum(Header<Spec>* header, const unsigned char* msg)
	{
		return (header->checksum == CalculateChecksum(msg, header->size));
	}
}
}
}