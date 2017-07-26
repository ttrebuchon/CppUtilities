#pragma once
#include <map>


namespace QUtils
{
namespace Network
{
	template <class Index_t, class Service_t, class Return_t, class...Args>
	class ProcedureLookup
	{
		private:
		typedef Return_t(Service_t::*Procedure)(Args...);
		static std::map<Index_t, Procedure> procedures;
		public:
		static Procedure Find(const Index_t index)
		{
			return procedures.at(index);
		}
		
		static void Register(const Index_t index, Procedure proc)
		{
			procedures.add(index, proc);
		}
	};
}
}