#pragma once
#include <string>
#include "Records.h"

namespace Util
{
namespace Rules
{
	class Engine
	{
		private:
		static long long nextID;
		Records* records;
		
		protected:
		
		
		public:
		Engine() : records(new Records(nextID++))
		{
			
		}
		
		~Engine()
		{
			delete records;
		}
		
		template <typename T, typename G>
		void assertf(const std::string name, const T val1, const G val2)
		{
			records->add(name, val1, val2);
			
		}
		
		template <typename T>
		void assertf(const std::string name, const T val1)
		{
			records->add(name, val1);
		}
		
		/*template <typename T>
		auto checkf(const std::string name) const
		{
			return records->template get<T>(name);
		}*/
		
		template <typename T, typename ...G>
		auto checkf(const std::string name) const
		{
			return records->template get<T, G...>(name);
		}
		
	};
}
}