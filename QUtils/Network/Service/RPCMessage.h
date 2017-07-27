#pragma once

#include <type_traits>

#include <QUtils/Types/Functions.h>

#include "ReturnMessage.h"
#include "ProcedureLookup.h"

namespace QUtils
{
namespace Network
{
	namespace Helpers
	{
		template <class Ret, class... Args>
		struct CallerHelper
		{
			template <class F>
			static Ret callWithArgs(F& f, std::tuple<Args...>& args)
			{
				return Types::CallWithTupleArgs(f, args);
			}
		};
		
		template <class Ret>
		struct CallerHelper<Ret>
		{
			template <class F>
			static Ret callWithArgs(F& f, std::tuple<>& args)
			{
				return f();
				std::cout << "Invalid state!\n";
				throw std::exception();
			}
		};
	}
	
	template <class Service_t, class Ret, class ...Args>
	class RPCMessage : public ReturnMessage<Ret>
	{
		private:
		typedef Ret(Service_t::*Procedure)(Args...);
		typedef std::string Index;
		int _priority;
		
		Index procIndex;
		std::tuple<Args...> args;
		
		
		
		
		
		protected:
		virtual void visit(Service& baseSrv) override
		{
			try
			{
			std::cout << "Visiting\n";
			Procedure proc = ProcedureLookup<Index, Service_t, Ret, Args...>::Find(procIndex);
			Service_t& srv = static_cast<Service_t&>(baseSrv);
			
			
			auto call = [&](auto... x)
			{
				std::cout << "Calling...\n";
				return (srv.*proc)(x...);
			};
			
			auto value = [&]() -> Ret
			{
				std::cout << "Calling via helper...\n";
				return Helpers::CallerHelper<Ret, Args...>::callWithArgs(call, args);
				/*if (sizeof...(Args) > 0)
				{
					
				}
				else
				{
					return call();
				}*/
			};
			
			this->setValue(value);
			}
			catch (...)
			{
				this->setException(std::current_exception());
			}
			std::cout << "Visited.\n";
		}
		
		
		
		public:
		RPCMessage(Index index, Args... args) : procIndex(index), args(std::tuple<Args...>(args...))
		{}
		
		virtual int priority() const override
		{
			return _priority;
		}
	};

}
}