#pragma once

#include <string>
#include <vector>

#include "Errors.h"

namespace QUtils
{
namespace SQL
{
	
	class Query;
	
	class Connection
	{
		protected:
		
		public:
		
		virtual bool isOpen() const = 0;
		virtual void open() = 0;
		virtual void close() = 0;
		
		virtual Query* query(std::string) const = 0;
		
		virtual bool vQuery(std::string) = 0;
		
		virtual Query* tablesQuery(std::string tableName = "") const = 0;
		virtual bool tableExists(std::string) const = 0;
		
		typedef std::tuple<int, std::string, std::string, bool, std::string, bool> ColumnInfo;
		
		virtual std::vector<ColumnInfo> tableColumns(const std::string tableName) const = 0;
		
	};
}
}