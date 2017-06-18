#pragma once

#include <string>

namespace Util
{
namespace SQL
{
	
	
	class Column
	{
		private:
		int _index;
		std::string _name;
		std::string _type;
		bool _notNull;
		std::string _defaultValue;
		bool _PK;
		
		public:
		Column(const int, const std::string, const std::string, const bool, const std::string, const bool);
		
		const int& index;
		const std::string& name;
		const std::string& type;
		const bool& notNull;
		const std::string& defaultValue;
		const bool& PK;
		
		friend class Table;
		
	};
}
}