#pragma once

#include <QUtils/Types/Functions.h>

#include "Message.h"
#include "ProcedureLookup.h"

namespace QUtils
{
namespace Network
{
	template <class Service_t, class Ret, class ...Args>
	class RPCMessage : public Message
	{
		private:
		typedef Ret(Service_t::*Procedure)(Args...);
		typedef std::string Index;
		
		Index procIndex;
		std::tuple<Args...> args;
		protected:
		virtual void visit(Service& baseSrv) override
		{
			Procedure proc = ProcedureLookup<Index, Service_t, Ret, Args...>::Find(procIndex);
			Service_t& srv = static_cast<Service_t&>(baseSrv);
			auto call = [=, &srv](auto... x) {
				return (srv.*proc)(x...);
			};
			
			Types::CallWithTupleArgs(call, args);
			
		}
	};

}
}