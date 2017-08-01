#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "SQLColumns.h"
#include "SQLRows.h"


namespace QUtils
{
namespace SQL
{
	class SQLConnection;
	class SQLColumn;
	class SQLQuery;
	
	class SQLTable
	{
		private:
		protected:
		SQLConnection* con;
		
		std::string _name;
		std::vector<std::shared_ptr<SQLColumn>> _columns;
		std::map<std::string, std::shared_ptr<SQLColumn>> _columnsByName;
		
		std::shared_ptr<SQLRows> _rows;
		
		std::shared_ptr<SQLColumn> _PK;
		
		SQLTable(SQLConnection*, std::string name);
		
		void refreshColumns();
		public:
		SQLColumns columns;
		const SQLRows& rows;
		
		SQLTable& operator=(const SQLTable);
		
		const std::string& name;
		/*const std::vector<std::shared_ptr<Column>>& columns;
		const std::map<std::string, std::shared_ptr<Column>>& columnsByName;*/
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
		
		std::string tableStatement() const;
		
		
		friend class SQLDatabase;
	};
}
}