#include <QUtils/SQL/Column.h>
#include <QUtils/SQL/Clause.h>

namespace Util
{
namespace SQL
{
	Column::Column(const int index, const std::string name, const std::string type, const bool notNull, const std::string defaultValue, const bool PK, const std::string table) : _index(index), _name(name), _type(type), _notNull(notNull), _defaultValue(defaultValue), _PK(PK), _table(table), index(_index), name(_name), type(_type), notNull(_notNull), defaultValue(_defaultValue), PK(_PK)
	{
		
	}
	
	Clause Column::operator==(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "=", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator!=(const Column& col) const
	{
		return !(Clause("[" + this->_table + "].[" + name + "]", "=", "[" + col._table + "].[" + col.name + "]"));
	}
	
	Clause Column::operator*(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "*", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator/(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "/", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator+(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "+", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator-(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "-", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator>(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", ">", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator>=(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", ">=", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator<(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "<", "[" + col._table + "].[" + col.name + "]");
	}
	
	Clause Column::operator<=(const Column& col) const
	{
		return Clause("[" + this->_table + "].[" + name + "]", "<=", "[" + col._table + "].[" + col.name + "]");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	Clause Column::operator==(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "=", s);
	}
	
	Clause Column::operator!=(const double n) const
	{
		auto s = std::to_string(n);
		return !(Clause("[" + this->_table + "].[" + name + "]", "=", s));
	}
	
	Clause Column::operator*(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "*", s);
	}
	
	Clause Column::operator/(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "/", s);
	}
	
	Clause Column::operator+(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "+", s);
	}
	
	Clause Column::operator-(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "-", s);
	}
	
	Clause Column::operator>(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", ">", s);
	}
	
	Clause Column::operator>=(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", ">=", s);
	}
	
	Clause Column::operator<(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "<", s);
	}
	
	Clause Column::operator<=(const double n) const
	{
		auto s = std::to_string(n);
		return Clause("[" + this->_table + "].[" + name + "]", "<=", s);
	}
	
	
	
	
}
}