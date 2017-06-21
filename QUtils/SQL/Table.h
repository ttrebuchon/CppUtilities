#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>


namespace QUtils
{
namespace SQL
{
	class Connection;
	class Column;
	class Query;
	
	class Table
	{
		private:
		protected:
		Connection* con;
		
		std::string _name;
		std::vector<std::shared_ptr<Column>> _columns;
		std::map<std::string, std::shared_ptr<Column>> _columnsByName;
		
		std::shared_ptr<Column> _PK;
		
		Table(Connection*, std::string name);
		
		void refreshColumns();
		public:
		
		Table& operator=(const Table);
		
		const std::string& name;
		const std::vector<std::shared_ptr<Column>>& columns;
		const std::map<std::string, std::shared_ptr<Column>>& columnsByName;
		long count() const;
		void drop();
		Table join(const Table t, std::string col1, std::string col2) const;
		const std::shared_ptr<Column> primary() const;
		void refresh();
		Query* rows() const;
		
		
		const Column& operator[](const std::string columnName) const;
		
		template <typename... S>
		Query* select(std::string c1, std::string c2, S... s)
		{
			return select(c1 + ", " + c2, s...);
		}
		Query* select(std::string) const;
		
		
		friend class Database;
	};
}
}