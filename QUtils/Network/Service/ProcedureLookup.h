#pragma once
#include <map>


namespace QUtils
{
namespace Network
{
	template <class Index_t, class Service_t, class Return_t, class...Args>
	class ProcedureLookup
	{
		public:
		typedef Return_t(Service_t::*Procedure)(Args...);
		private:
		static std::map<Index_t, Procedure> procedures;
		public:
		static Procedure Find(const Index_t index)
		{
			return procedures.at(index);
		}
		
		static void Register(const Index_t index, Procedure proc)
		{
			procedures[index] = proc;
		}
	};
	
	template <class Index_t, class Service_t, class Return_t, class...Args>
	std::map<Index_t, typename ProcedureLookup<Index_t, Service_t, Return_t, Args...>::Procedure> ProcedureLookup<Index_t, Service_t, Return_t, Args...>::procedures;
}
}