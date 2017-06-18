#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Util
{
namespace SQL
{
	class Connection;
	class Column;
	
	class Table
	{
		private:
		protected:
		Connection* con;
		
		std::vector<std::shared_ptr<Column>> _columns;
		
		Table(Connection*, std::string name);
		public:
		
		
		
		const std::string name;
		const std::vector<std::shared_ptr<Column>>& columns() const { return _columns; }
		long count() const;
		
		friend class Database;
	};
}
}