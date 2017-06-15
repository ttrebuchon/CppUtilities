#pragma once
#include <string>
#include <map>
#include <castor.h>
#include "Record.h"
#include <iostream>

namespace Util
{
namespace Rules
{
	
	
	template <typename ...T>
	class Database
	{
		protected:
		
		static_assert(sizeof...(T) > 0, "Cannot have a database of no type");
		
		std::map<std::string, castor::Disjunctions*> relations;
		
		std::map<std::string, Record<T...>*> records;
		
		static std::map<long long, Database<T...>*> Databases;
		
		Database()
		{
		}
		
		public:
		
		virtual ~Database()
		{
			
		}
		
		
		void addDisjunction(const std::string name)
		{
			if (relations.count(name) <= 0)
			{
				relations[name] = new castor::Disjunctions();
			}
		}
		
		bool disjunctionExists(const std::string name) const
		{
			return relations.count(name) > 0;
		}
		
		void add(const std::string name, const T... t)
		{
			if (records.count(name) <= 0)
			{
			records[name] = new Record<T...>();
			}
			records[name]->add(t...);
		}
		
		typename Record<T...>::Result get(const std::string name, auto... args) const
		{
			return records.at(name)->get(args...);
		}
		
		void newRule(const std::string name, typename Record<T...>::Rule r)
		{
			if (records.count(name) > 0)
			{
				//TODO
				throw std::exception();
			}
			records[name] = new Record<T...>();
			records[name]->setRule(r);
		}
		
		template <typename ...G>
		friend class DBWrapperT;
		friend class DatabaseHandler;
	};
	
	
	
	
	
	
	
	
	
	
	
	template <typename ...T>
	std::map<long long, Database<T...>*> Database<T...>::Databases;
	
	class DBWrapper
	{
		public:
		DBWrapper() {}
		virtual ~DBWrapper() {}
	};
	
	template <typename ...T>
	class DBWrapperT : public DBWrapper
	{
		long long ID;
		typedef Database<T...> Type;
		public:
		
		DBWrapperT(long long ID) : DBWrapper(), ID(ID)
		{
			
		}
		virtual ~DBWrapperT()
		{
			delete Type::Databases[ID];
			Type::Databases.erase(ID);
		}
		
	};
	
	class DatabaseHandler
	{
		private:
		
		
		static std::map<long long, std::vector<DBWrapper*>> handles;
		
		public:
		DatabaseHandler() = delete;
		
		
		template <typename ...T>
		static Database<T...>* Get(long long ID)
		{
			if (Database<T...>::Databases.count(ID) <= 0)
			{
				Database<T...>::Databases[ID] = new Database<T...>();
				handles[ID].push_back(new DBWrapperT<T...>(ID));
			}
			return Database<T...>::Databases[ID];
		}
		
		static void Remove(long long ID)
		{
			for (auto wrap : handles[ID])
			{
				delete wrap;
			}
			handles.erase(ID);
		}
	};
}
}