#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "SQLObjects/SQLDatabaseObject.h"
#include "SQLColumns.h"
#include "SQLRows.h"



namespace QUtils
{
namespace SQL
{
	class SQLConnection;
	class SQLColumn;
	class SQLQuery;
	class SQLClause;
	
	
namespace Internal
{
	class SQLTable_Obj : public SQLDatabaseObject
	{
		protected:
		std::string _name;
		std::vector<std::shared_ptr<SQLColumn>> _columns;
		std::map<std::string, std::shared_ptr<SQLColumn>> _columnsByName;
		
		std::shared_ptr<SQLColumn> _PK;
		
		SQLTable_Obj(const SQLDatabase, const std::string);
		SQLTable_Obj(const SQLDatabaseObject&, const std::string);
		
		void refreshColumns();
		public:
		const std::string& name;
		SQLColumns columns;
		SQLRows rows;
		
		
		
		long count() const;
		void drop();
		SQLTable join(const SQLTable table2, std::string col1, std::string col2) const;
		SQLTable join(const std::shared_ptr<SQLTable_Obj> table2, std::string col1, std::string col2) const;
		const std::shared_ptr<SQLColumn> primary() const;
		void refresh();
		SQLQuery* rowsQuery() const;
		
		
		
		
		template <typename... S>
		SQLQuery* select(std::string c1, std::string c2, S... s)
		{
			return select(c1 + ", " + c2, s...);
		}
		SQLQuery* select(std::string) const;
		SQLQuery* select(std::string, SQLClause) const;
		
		std::string tableStatement() const;
		
		
		friend QUtils::SQL::SQLTable;
	};
}
	/*
	class SQLTable : public SQLDatabaseObject
	{
		private:
		protected:
		std::string _name;
		std::shared_ptr<Internal::SQLTable_Obj> behind;
		
		
		
		SQLTable(const SQLDatabase&, std::string name);
		
		void refreshColumns();
		public:
		SQLColumns columns;
		SQLRows rows;
		
		//SQLTable(const SQLTable&);
		
		SQLTable& operator=(const SQLTable);
		
		const std::string& name;
		
		long count() const;
		void drop();
		SQLTable join(const SQLTable t, std::string col1, std::string col2) const;
		const std::shared_ptr<SQLColumn> primary() const;
		void refresh();
		SQLQuery* rowsQuery() const;
		
		
		
		
		template <typename... S>
		SQLQuery* select(std::string c1, std::string c2, S... s)
		{
			return select(c1 + ", " + c2, s...);
		}
		SQLQuery* select(std::string) const;
		SQLQuery* select(std::string, SQLClause) const;
		
		std::string tableStatement() const;
		
		
		friend class SQLDatabase;
	};*/
}
}