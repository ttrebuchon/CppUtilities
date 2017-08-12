#pragma once

#include <string>

#include "SQLTypeDefs.h"
#include "ValueType.h"

namespace QUtils
{
namespace SQL
{
	class SQLClause;
	
	class SQLColumn
	{
		private:
		int _index;
		std::string _name;
		ValueType _type;
		bool _notNull;
		std::string _defaultValue;
		bool _PK;
		std::string _table;
		
		public:
		SQLColumn(const int, const std::string, const std::string, const bool, const std::string, const bool, const std::string);
		
		SQLColumn& operator=(SQLColumn&&);
		
		const int& index;
		const std::string& name;
		const ValueType& type;
		const bool& notNull;
		const std::string& defaultValue;
		const bool& PK;
		
		
		
		
		
		
		
		SQLClause operator==(const SQLColumn&) const;
		SQLClause operator!=(const SQLColumn&) const;
		SQLClause operator*(const SQLColumn&) const;
		SQLClause operator/(const SQLColumn&) const;
		SQLClause operator+(const SQLColumn&) const;
		SQLClause operator-(const SQLColumn&) const;
		SQLClause operator>(const SQLColumn&) const;
		SQLClause operator>=(const SQLColumn&) const;
		SQLClause operator<(const SQLColumn&) const;
		SQLClause operator<=(const SQLColumn&) const;
		
		
		SQLClause operator==(const double n) const;
		SQLClause operator!=(const double n) const;
		SQLClause operator*(const double n) const;
		SQLClause operator/(const double n) const;
		SQLClause operator+(const double n) const;
		SQLClause operator-(const double n) const;
		SQLClause operator>(const double n) const;
		SQLClause operator>=(const double n) const;
		SQLClause operator<(const double n) const;
		SQLClause operator<=(const double n) const;
		
		
		
		
		friend SQLTable;
		
	};
}
}