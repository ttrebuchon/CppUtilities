#pragma once

#include "Messenger.h"
#include <iostream>
#include <QUtils/Exception/NotImplemented.h>


namespace QUtils { namespace Network {
namespace SocketProtocol
{
	template <class Spec>
	MessengerWithSpec<Spec>::MessengerWithSpec(Socket* socket) : Messenger(socket), cachedMsgs(new unsigned char*[Spec::MsgID_Info::Max]), idsLeft(Spec::MsgID_Info::Max)
	{
		::memset(cachedMsgs, 0, Spec::MsgID_Info::Max*sizeof(unsigned char*));
	}
	
	template <class Spec>
	MessengerWithSpec<Spec>::~MessengerWithSpec()
	{
		for (unsigned char** ptr = cachedMsgs; ptr < (cachedMsgs + Spec::MsgID_Info::Max); ++ptr)
		{
			if (*ptr != NULL)
			{
				delete[] *ptr;
			}
		}
		delete[] cachedMsgs;
	}
	
	
	template <class Spec>
	void MessengerWithSpec<Spec>::send(const unsigned char* data, const unsigned int length, bool wideChars, bool responseRequired)
	{
		if (socket == NULL)
		{
			throw NotImp();
		}
		Header<Spec> head;
		
		typename Spec::MsgID_t id;
		
		for (id = 0; id < Spec::MsgID_Info::Max; ++id)
		{
			if (cachedMsgs[id] == NULL)
			{
				break;
			}
		}
		if (id == Spec::MsgID_Info::Max)
		{
			throw NotImp();
		}
		//TODO!
		head.id = id;
		
		head.size = length;
		head.wideChars = wideChars;
		head.responseRequired = responseRequired;
		head.badMessage = false;
		head.checksum = Protocol<Spec>::CalculateChecksum(data, length);
		
		auto rawHead = Protocol<Spec>::WriteHeader(&head);
		
		unsigned char* msg = new unsigned char[length + Spec::Header_Size];
		
		::memcpy(msg, rawHead, Spec::Header_Size);
		::memcpy(msg + Spec::Header_Size, data, length);
		
		delete[] rawHead;
		
		socket->write(msg, length + Spec::Header_Size);
		cachedMsgs[id] = msg;
		--idsLeft;
		
	}
	
	
	template <class Spec>
	unsigned char* MessengerWithSpec<Spec>::receive(unsigned long long& length, bool& wideChars, bool& responseRequired, unsigned long long& id)
	{
		unsigned char* rawHeader = new unsigned char[Spec::Header_Size];
		
		if (socket->waitAll(rawHeader, Spec::Header_Size) != Spec::Header_Size)
		{
			throw NotImp();
		}
		
		auto head = Protocol<Spec>::ParseHeader(rawHeader);
		
		
		delete[] rawHeader;
		
		if (head->integrityResponse)
		{
		unsigned char* body = new unsigned char[Spec::ID_Size];
			socket->read(body, Spec::ID_Size);
			auto id = Spec::MsgID_Info::Read(body);
		if (head->badMessage)
		{
			std::cerr << "BadMessage!\n" << std::flush;
			
			resendBadMessage(id);
		}
		else
		{
			if (cachedMsgs[id] != NULL)
			{
				delete[] cachedMsgs[id];
				cachedMsgs[id] = NULL;
				++idsLeft;
			}
		}
		delete[] body;
		delete head;
		return NULL;
		}
		
		unsigned char* body = new unsigned char[head->size];
		
		socket->waitAll(body, sizeof(unsigned char)*head->size);
		
		const typename Spec::MsgID_t msgID = head->id;
		
		id = head->id;
		
		if (Protocol<Spec>::CalculateChecksum(body, head->size) != head->checksum)
		{
			delete[] body;
			delete head;
			respondBadMessage(msgID);
			return NULL;
		}
		else
		{
			auto resp = Protocol<Spec>::GoodMessageResponse(msgID);
			socket->write(resp, Spec::Header_Size + Spec::ID_Size);
			delete[] resp;
		}
		
		length = head->size;
		wideChars = head->wideChars;
		responseRequired = head->responseRequired;
		id = head->id;
		
		delete head;
		return body;
	}
	
	
	
	template <class Spec>
	void MessengerWithSpec<Spec>::respondBadMessage(const typename Spec::MsgID_t id)
	{
		//TODO
		throw NotImp();
	}
	
	
	
	
	
	template <class Spec>
	void MessengerWithSpec<Spec>::resendBadMessage(const unsigned char* body)
	{
		const typename Spec::MsgID_t id = Spec::MsgID_Info::Read(body);
		resendBadMessage(id);
	}
	
	template <class Spec>
	void MessengerWithSpec<Spec>::resendBadMessage(const typename Spec::MsgID_t id)
	{
		//TODO
		throw NotImp();
	}
	
	/*template <class Spec>
	bool MessengerWithSpec<Spec>::openIDs() const
	{
		for (typename Spec::MsgID_t id = 0; id < Spec::MsgID_Info::Max; ++id)
		{
			if (cachedMsgs[id] == NULL)
			{
				return true;
			}
		}
		return false;
	}*/
}
}
}