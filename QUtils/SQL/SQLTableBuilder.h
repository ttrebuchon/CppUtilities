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
		
		std::string to_string() const
		{
			return "[" + name + "] " + SQL::to_string(type) + (notNull ? " NOT NULL" : "") + (PK ? " PRIMARY KEY" : "");
		}
	};
	
	struct SQLTableBuilder
	{
		std::string name;
		std::vector<SQLColumnBuilder> columns;
		std::vector<SQLForeignKeyBuilder> foreignKeys;
		
		std::string to_string() const
		{
			std::string str = "";
			for (auto col : columns)
			{
				str += ", " + col.to_string();
			}
			return "[" + name + "] (" + str.substr(2) + ")";
		}
	};
}
}