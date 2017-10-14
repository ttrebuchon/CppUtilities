#pragma once

#include "Protocol.h"

namespace QUtils { namespace Network {
	
class Socket;


namespace SocketProtocol
{
	
	
	class Messenger
	{
		private:
		
		protected:
		Socket* socket;
		
		Messenger(Socket* s) : socket(s)
		{ }
		
		public:
		
		virtual ~Messenger() { }
		
		template <class Spec>
		static std::shared_ptr<Messenger> Create(Socket*);
		
		static std::shared_ptr<Messenger> CreateDefault(Socket*);
		
		
		virtual void send(const unsigned char* data, const unsigned int length, bool wideChars = false, bool responseRequired = false) = 0;
		
		virtual unsigned char* receive(unsigned long long& length, bool& wideChars, bool& responseRequired, unsigned long long& id) = 0;
		
		bool poll(const int timeout_ms) const;
		
		virtual bool openIDs() const = 0;
	};
	
	
	
	
	template <class Spec>
	class MessengerWithSpec final : public Messenger
	{
		private:
		
		unsigned char** cachedMsgs;
		typename Spec::MsgID_t idsLeft;
		
		protected:
		
		MessengerWithSpec(Socket*);
		
		public:
		
		virtual ~MessengerWithSpec();
		
		virtual void send(const unsigned char* data, const unsigned int length, bool wideChars = false, bool responseRequired = false);
		
		virtual unsigned char* receive(unsigned long long& length, bool& wideChars, bool& responseRequired, unsigned long long& id);
		
		void respondBadMessage(const typename Spec::MsgID_t id);
		
		void resendBadMessage(const unsigned char* body);
		void resendBadMessage(const typename Spec::MsgID_t id);
		
		inline bool openIDs() const override
		{
			return idsLeft > 0;
		}
		
		
		friend class Messenger;
	};
	
	
	template <class Spec>
	std::shared_ptr<Messenger> Messenger::Create(Socket* socket)
	{
		auto ptr = new MessengerWithSpec<Spec>(socket);
		return std::shared_ptr<Messenger>(ptr);
	}
}
}
}