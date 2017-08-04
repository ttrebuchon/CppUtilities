#pragma once

#include <memory>
#include <map>
#include <vector>

#include "SQLTypeDefs.h"


namespace QUtils
{
namespace SQL
{
	class SQLColumn;
	
	class SQLColumns
	{
		private:
		
		
		
		SQLColumns(std::vector<std::shared_ptr<SQLColumn>>* cols, std::map<std::string, std::shared_ptr<SQLColumn>>* colsByName, std::shared_ptr<SQLColumn>& PK) : columns(cols), columnsByName(colsByName), PK(PK)
		{}
		
		public:
		typedef typename std::vector<std::shared_ptr<SQLColumn>>::const_iterator iterator;
		
		const std::vector<std::shared_ptr<SQLColumn>>* columns;
		const std::map<std::string, std::shared_ptr<SQLColumn>>* columnsByName;
		
		const std::shared_ptr<SQLColumn> PK;
		const SQLColumn& operator[](const std::string columnName) const;
		
		SQLColumns& operator=(const SQLColumns&);
		
		
		iterator begin() const;
		iterator end() const;
		
		friend SQLTable;
		friend class Internal::SQLTable_Obj;
	};
}
}