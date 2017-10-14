#pragma once
#include <unordered_map>
#include <map>
#include <typeindex>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <string>

namespace QUtils::Network
{
	class TypeLookup
	{
		private:
		typedef unsigned long long ID_t;
		static std::atomic<ID_t> nextID;
		
		static std::shared_timed_mutex types_m;
		static std::map<std::type_index, ID_t> types;
		static std::map<ID_t, std::type_index> to_types;
		
		static std::shared_timed_mutex aliases_m;
		static std::map<std::string, ID_t> aliases;
		
		public:
		
		template <class Type>
		static ID_t Register(const std::string alias)
		{
			auto id = Register<Type>();
			
			{
				std::unique_lock<std::shared_timed_mutex> lock(aliases_m);
				aliases[alias] = id;
			}
			return id;
		}
		
		template <class Type>
		static ID_t Register()
		{
			auto id = nextID++;
			
			std::type_index index(typeid(Type));
			
			{
				std::unique_lock<std::shared_timed_mutex> lock(types_m);
				types[index] = id;
				to_types[id] = index;
			}
			
			return id;
		}
		
		static std::type_index Lookup(const ID_t id)
		{
			std::shared_lock<std::shared_timed_mutex> lock(types_m);
			return to_types.at(id);
		}
		
		static std::type_index Lookup(const std::string alias)
		{
			ID_t id;
			
			{
				std::shared_lock<std::shared_timed_mutex> lock(aliases_m);
				id = aliases.at(alias);
			}
			return Lookup(id);
		}
		
		 
	};
}