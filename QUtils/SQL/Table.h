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
		
		std::shared_ptr<Column> _PK;
		
		Table(Connection*, std::string name);
		
		void refreshColumns();
		public:
		
		
		
		const std::string name;
		const std::vector<std::shared_ptr<Column>>& columns;
		long count() const;
		
		bool drop();
		
		Table join(const Table t, std::string col1, std::string col2) const;
		
		const std::shared_ptr<Column> primary() const;
		
		void refresh();
		
		friend class Database;
	};
}
}