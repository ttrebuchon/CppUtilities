#pragma once

#include <string>

namespace QUtils
{
namespace SQL
{
	class Clause;
	
	class Column
	{
		private:
		int _index;
		std::string _name;
		std::string _type;
		bool _notNull;
		std::string _defaultValue;
		bool _PK;
		std::string _table;
		
		public:
		Column(const int, const std::string, const std::string, const bool, const std::string, const bool, const std::string);
		
		Column& operator=(Column&&);
		
		const int& index;
		const std::string& name;
		const std::string& type;
		const bool& notNull;
		const std::string& defaultValue;
		const bool& PK;
		
		
		
		
		
		
		
		Clause operator==(const Column&) const;
		Clause operator!=(const Column&) const;
		Clause operator*(const Column&) const;
		Clause operator/(const Column&) const;
		Clause operator+(const Column&) const;
		Clause operator-(const Column&) const;
		Clause operator>(const Column&) const;
		Clause operator>=(const Column&) const;
		Clause operator<(const Column&) const;
		Clause operator<=(const Column&) const;
		
		
		Clause operator==(const double n) const;
		Clause operator!=(const double n) const;
		Clause operator*(const double n) const;
		Clause operator/(const double n) const;
		Clause operator+(const double n) const;
		Clause operator-(const double n) const;
		Clause operator>(const double n) const;
		Clause operator>=(const double n) const;
		Clause operator<(const double n) const;
		Clause operator<=(const double n) const;
		
		
		
		
		friend class Table;
		
	};
}
}