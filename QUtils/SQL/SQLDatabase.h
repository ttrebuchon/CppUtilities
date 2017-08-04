#pragma once

#include <string>
#include <vector>
#include <memory>

#include "SQLTypeDefs.h"
#include "SQLObjects/SQLObject.h"

namespace QUtils
{
namespace SQL
{
	class SQLConnection;
	
namespace Internal
{
	class SQLDatabase_Obj : public SQLObject, public std::enable_shared_from_this<SQLDatabase_Obj>
	{
		protected:
		SQLDatabase_Obj(SQLConnection*, const std::string name);
		SQLDatabase_Obj(SQLConnection*);
		
		std::string name;
		std::shared_ptr<std::vector<std::string>> lastTables;
		
		
		static std::shared_ptr<SQLDatabase_Obj> Create(SQLConnection*, const std::string);
		
		public:
		SQLTable operator[](std::string name);
		
		class iterator : public SQLObject
		{
			private:
			typename std::vector<std::string>::iterator vIt;
			std::shared_ptr<std::vector<std::string>> names;
			std::shared_ptr<SQLDatabase_Obj> behind;
			iterator(SQLDatabase_Obj&, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			iterator(std::shared_ptr<Internal::SQLDatabase_Obj>, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			public:
			
			SQLTable operator*() const;
			iterator operator++();
			bool operator==(const iterator) const;
			bool operator!=(const iterator) const;
			
			friend SQLDatabase_Obj;
		};
		
		/*iterator begin();
		iterator end();*/
		friend SQLDatabase;
	};
}
//typedef SQLObjectPointer<Internal::SQLDatabase_Obj> SQLDatabase;
	
	/*class SQLDatabase : public SQLObject, public std::enable_shared_from_this<SQLDatabase>
	{
		private:
		
		
		protected:
		std::shared_ptr<Internal::SQLDatabase_Obj> behind;
		std::string _name;
		
		SQLDatabase(std::shared_ptr<Internal::SQLDatabase_Obj>);
		
		public:
		const std::string& name;
		SQLDatabase(SQLConnection*, const std::string name);
		SQLDatabase(SQLConnection*);
		
		SQLTable operator[](std::string name) const;
		
		SQLDatabase& operator=(const SQLDatabase&);
		
		class iterator : public SQLObject
		{
			private:
			typename std::vector<std::string>::iterator vIt;
			std::shared_ptr<std::vector<std::string>> names;
			std::shared_ptr<Internal::SQLDatabase_Obj> behind;
			iterator(SQLDatabase&, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			iterator(std::shared_ptr<Internal::SQLDatabase_Obj>, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			public:
			
			SQLTable operator*() const;
			iterator operator++();
			bool operator==(const iterator) const;
			bool operator!=(const iterator) const;
			
			friend class SQLDatabase;
		};
		
		iterator begin();
		iterator end();
	};*/
	
}
}