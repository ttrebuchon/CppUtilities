#pragma once

#include <string>
#include <vector>

#include "Errors.h"

#include "SQLTableBuilder.h"

namespace QUtils
{
namespace SQL
{
	
	class SQLQuery;
	
	class SQLConnection
	{
		protected:
		
		public:
		
		virtual bool isOpen() const = 0;
		virtual void open() = 0;
		virtual void close() = 0;
		
		virtual SQLQuery* query(std::string) const = 0;
		
		virtual bool vQuery(std::string) = 0;
		
		virtual SQLQuery* tablesQuery(const std::string tableName = "") const = 0;
		virtual bool tableExists(const std::string) const = 0;
		
		typedef std::tuple<int, std::string, std::string, bool, std::string, bool> ColumnInfo;
		
		virtual std::vector<ColumnInfo> tableColumns(const std::string tableName) const = 0;
		
		virtual bool tableHasRid(const std::string tableName) = 0;
		
		virtual void attachDatabase(const std::string schema, const std::string URI) = 0;
		inline void attachDB(const std::string schema, const std::string URI)
		{ return attachDatabase(schema, URI); }
		
		virtual std::string getDefaultDBName() const = 0;
		virtual std::vector<std::string> getDatabases() const = 0;
		
		virtual std::string RIDType() const = 0;
		
		virtual void createTables(const std::vector<SQLTableBuilder>& builders) = 0;
		
	};
}
}