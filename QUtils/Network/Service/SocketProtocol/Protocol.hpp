#pragma once

#include "Protocol.h"
#include "Header.h"
#include <QUtils/Byte.h>

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
		if (hd->id == Spec::MsgID_Info::Max)
		{
			hd->integrityResponse = true;
		}
		auto ptr = header + Spec::ID_Size + Spec::Length_Size;
		hd->checksum = Spec::MsgChecksum_Info::Read(ptr);

		ptr += Spec::Checksum_Size;

		const Byte* options = reinterpret_cast<const Byte*>(ptr);
		if (Spec::Options_Size > 0)
		{
			hd->wideChars = options[0](0);
			hd->responseRequired = options[0](1);
		}

		ptr += Spec::Options_Size;
		
		return hd;
	}

	template <class Spec>
	Header<Spec>* Protocol<Spec>::ParseHeader(const unsigned char* header)
	{
		return ParseHeader(header, Spec::MsgLen_Info::Read(header + Spec::ID_Size));
	}
	
	template <class Spec>
	unsigned char* Protocol<Spec>::WriteHeader(const Header<Spec>* header)
	{
		unsigned char* rawHeader = new unsigned char[HeaderLength];
		WriteHeader(header, rawHeader);
		return rawHeader;
	}
	
	template <class Spec>
	unsigned int Protocol<Spec>::WriteHeader(const Header<Spec>* header, void* rawHeader)
	{
		static_assert(HeaderLength == sizeof(unsigned char)*(Spec::ID_Size + Spec::Length_Size + Spec::Checksum_Size + Spec::Options_Size), "");
		
		static_assert(Spec::Header_Size == sizeof(unsigned char)*(Spec::ID_Size + Spec::Length_Size + Spec::Checksum_Size + Spec::Options_Size), "");

		auto ptr = reinterpret_cast<unsigned char*>(rawHeader);
		
		if (header->integrityResponse)
		{
			Spec::MsgID_Info::Write(Spec::MsgID_Info::Max, ptr);
		}
		else
		{
			Spec::MsgID_Info::Write(header->id, ptr);
		}

		ptr += Spec::ID_Size;
		Spec::MsgLen_Info::Write(header->size, ptr);
		ptr += Spec::Length_Size;
		Spec::MsgChecksum_Info::Write(header->checksum, ptr);
		ptr += Spec::Checksum_Size;

		if (Spec::Options_Size > 0)
		{
			auto b = new(ptr) Byte(0);
			(*b)(0, header->wideChars);
			(*b)(1, header->responseRequired);
		}
		
		return Spec::ID_Size + Spec::Length_Size + Spec::Checksum_Size + Spec::Options_Size;
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
	
	
	
	template <class Spec>
	unsigned char* Protocol<Spec>::GoodMessageResponse(const typename Spec::MsgID_t id)
	{
		Header<Spec> hd;
		hd.setGoodMessageResponse();
		
		unsigned char* msg = new unsigned char[HeaderLength + Spec::ID_Size];
		
		WriteHeader(&hd, msg);
		Spec::MsgID_Info::Write(id, msg+HeaderLength);
		return msg;
	}
	
	template <class Spec>
	unsigned char* Protocol<Spec>::BadMessageResponse(const typename Spec::MsgID_t id)
	{
		Header<Spec> hd;
		hd.setBadMessageResponse();
		
		unsigned char* msg = new unsigned char[HeaderLength + Spec::ID_Size];
		
		WriteHeader(&hd, msg);
		Spec::MsgID_Info::Write(id, msg+HeaderLength);
		return msg;
	}
	
	
}
}
}