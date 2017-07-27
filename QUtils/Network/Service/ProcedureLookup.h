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
		typedef Return_t(Service_t::*Procedure_c)(Args...) const;
		
		
		private:
		
		static std::map<Index_t, Procedure> procedures;
		static std::map<Index_t, Procedure_c> procedures_c;
		
		
		public:
		static Procedure Find(const Index_t index)
		{
			return procedures.at(index);
		}
		
		static Procedure_c Find_c(const Index_t index)
		{
			return procedures_c.at(index);
		}
		
		static void Register(const Index_t index, Procedure proc)
		{
			procedures[index] = proc;
		}
		
		static void Register(const Index_t index, Procedure_c proc)
		{
			procedures_c[index] = proc;
		}
	};
	
	template <class Index_t, class Service_t, class Return_t, class...Args>
	std::map<Index_t, typename ProcedureLookup<Index_t, Service_t, Return_t, Args...>::Procedure> ProcedureLookup<Index_t, Service_t, Return_t, Args...>::procedures;
	
	template <class Index_t, class Service_t, class Return_t, class...Args>
	std::map<Index_t, typename ProcedureLookup<Index_t, Service_t, Return_t, Args...>::Procedure_c> ProcedureLookup<Index_t, Service_t, Return_t, Args...>::procedures_c;
}
}