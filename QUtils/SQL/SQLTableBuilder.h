#pragma once
#include <vector>
#include <string>
#include "ValueType.h"

namespace QUtils
{
namespace SQL
{
	struct SQLForeignKeyBuilder
	{
		std::string fTable;
		std::string fColumn;
	};
	
	struct SQLColumnBuilder
	{
		std::string name;
		bool notNull;
		bool unique;
		bool PK;
		ValueType type;
		
		
		SQLColumnBuilder() : name(), notNull(false), unique(false), PK(false), type(Null)
		{}
	};
	
	struct SQLTableBuilder
	{
		std::string name;
		std::vector<SQLColumnBuilder> columns;
		std::vector<SQLForeignKeyBuilder> foreignKeys;
	};
}
}