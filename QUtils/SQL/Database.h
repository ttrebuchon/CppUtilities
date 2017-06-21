#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Util
{
namespace SQL
{
	class Connection;
	class Table;
	
	class Database
	{
		private:
		std::shared_ptr<std::vector<std::string>> lastTables;
		
		protected:
		Connection* con;
		
		public:
		Database(Connection*);
		
		Table operator[](std::string name) const;
		
		class iterator
		{
			private:
			typename std::vector<std::string>::iterator vIt;
			std::shared_ptr<std::vector<std::string>> names;
			Connection* con;
			iterator(Connection*, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			public:
			
			Table operator*() const;
			iterator operator++();
			bool operator==(const iterator) const;
			bool operator!=(const iterator) const;
			
			friend class Database;
		};
		
		iterator begin();
		iterator end() const;
	};
}
}