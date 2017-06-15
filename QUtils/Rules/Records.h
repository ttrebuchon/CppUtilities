#pragma once
#include <string>
#include "Database.h"
#include <functional>

namespace Util
{
namespace Rules
{
	class Records
	{
		protected:
		const long long ID;
		
		template <typename... T>
		Database<T...>* getDB() const
		{
			return DatabaseHandler::Get<T...>(ID);
		}
		
		public:
		Records(long long ID) : ID(ID)
		{
			
		}
		
		virtual ~Records()
		{
			DatabaseHandler::Remove(ID);
		}
		
		
		template <typename ...T>
		void add(const std::string name, const T... vals)
		{
			getDB<T...>()->add(name, vals...);
		}
		
		template <typename ...T>
		auto get(const std::string name, const Engine* eng)
		{
			return getDB<T...>()->get(name, eng);
		}
		
		template <typename ...T>
		void newRule(const std::string name, typename Record<T...>::Rule r)
		{
			getDB<T...>()->newRule(name, r);
		}
		
	};
}
}
