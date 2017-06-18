#pragma once

#include <string>
#include <vector>

namespace Util
{
namespace SQL
{
	class Connection;
	
	class Table
	{
		private:
		protected:
		Connection* con;
		
		Table(Connection*, std::string name);
		public:
		
		
		
		const std::string name;
		std::vector<std::string> columns() const;
		long count() const;
		
		friend class Database;
	};
}
}