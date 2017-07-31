#include <QUtils/SQL/SQLColumn.h>
#include <QUtils/SQL/SQLClause.h>

namespace QUtils
{
namespace SQL
{
	SQLColumn::SQLColumn(const int index, const std::string name, const std::string type, const bool notNull, const std::string defaultValue, const bool PK, const std::string table) : _index(index), _name(name), _type(type), _notNull(notNull), _defaultValue(defaultValue), _PK(PK), _table(table), index(_index), name(_name), type(_type), notNull(_notNull), defaultValue(_defaultValue), PK(_PK)
	{
		
	}
	
	SQLClause SQLColumn::operator==(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "=", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator!=(const SQLColumn& col) const
	{
		return !(SQLClause("[" + this->_table + "].[" + name + "]", "=", "[" + col._table + "].[" + col.name + "]"));
	}
	
	SQLClause SQLColumn::operator*(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "*", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator/(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "/", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator+(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "+", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator-(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "-", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator>(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", ">", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator>=(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", ">=", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator<(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "<", "[" + col._table + "].[" + col.name + "]");
	}
	
	SQLClause SQLColumn::operator<=(const SQLColumn& col) const
	{
		return SQLClause("[" + this->_table + "].[" + name + "]", "<=", "[" + col._table + "].[" + col.name + "]");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	SQLClause SQLColumn::operator==(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "=", s);
	}
	
	SQLClause SQLColumn::operator!=(const double n) const
	{
		auto s = std::to_string(n);
		return !(SQLClause("[" + this->_table + "].[" + name + "]", "=", s));
	}
	
	SQLClause SQLColumn::operator*(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "*", s);
	}
	
	SQLClause SQLColumn::operator/(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "/", s);
	}
	
	SQLClause SQLColumn::operator+(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "+", s);
	}
	
	SQLClause SQLColumn::operator-(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "-", s);
	}
	
	SQLClause SQLColumn::operator>(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", ">", s);
	}
	
	SQLClause SQLColumn::operator>=(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", ">=", s);
	}
	
	SQLClause SQLColumn::operator<(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "<", s);
	}
	
	SQLClause SQLColumn::operator<=(const double n) const
	{
		auto s = std::to_string(n);
		return SQLClause("[" + this->_table + "].[" + name + "]", "<=", s);
	}
	
	
	
	
}
}