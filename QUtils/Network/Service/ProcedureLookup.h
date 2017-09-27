#pragma once
#include <map>
#include <vector>

#include <QUtils/Exception/Exception.h>


namespace QUtils
{
namespace Network
{
	QUTILS_CUSTOM_EXCEPTION(ProcedureNotFound, the remote procedure could not be found);
	
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
			if (procedures.count(index) <= 0)
			{
				throw ProcedureNotFound().Function(__func__).Line(__LINE__).File(__FILE__).Msg("with index \"" + index + "\"");
			}
			return procedures.at(index);
		}
		
		static Procedure_c Find_c(const Index_t index)
		{
			if (procedures_c.count(index) <= 0)
			{
				throw ProcedureNotFound().Function(__func__).Line(__LINE__).File(__FILE__).Msg("with index \"" + index + "\"");
			}
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
		
		static auto Count(const Index_t index)
		{
			return procedures.count(index);
		}
		
		static auto Count_c(const Index_t index)
		{
			return procedures_c.count(index);
		}
		
		static std::vector<Index_t> Keys()
		{
			std::vector<Index_t> vec(procedures.size());
			int ind = 0;
			for (auto pair : procedures)
			{
				vec[ind++] = pair.first;
			}
			return vec;
		}
		
		static std::vector<Index_t> Keys_c()
		{
			std::vector<Index_t> vec(procedures_c.size());
			int ind = 0;
			for (auto pair : procedures_c)
			{
				vec[ind++] = pair.first;
			}
			return vec;
		}
	};
	
	template <class Index_t, class Service_t, class Return_t, class...Args>
	std::map<Index_t, typename ProcedureLookup<Index_t, Service_t, Return_t, Args...>::Procedure> ProcedureLookup<Index_t, Service_t, Return_t, Args...>::procedures;
	
	template <class Index_t, class Service_t, class Return_t, class...Args>
	std::map<Index_t, typename ProcedureLookup<Index_t, Service_t, Return_t, Args...>::Procedure_c> ProcedureLookup<Index_t, Service_t, Return_t, Args...>::procedures_c;
}
}