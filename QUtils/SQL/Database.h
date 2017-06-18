#pragma once

#include <string>

namespace Util
{
namespace SQL
{
	class Connection;
	class Table;
	
	class Database
	{
		private:
		protected:
		Connection* con;
		
		public:
		Database(Connection*);
		
		Table operator[](std::string name) const;
	};
}
}