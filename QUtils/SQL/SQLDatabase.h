#pragma once

#include <string>
#include <vector>
#include <memory>

namespace QUtils
{
namespace SQL
{
	class SQLConnection;
	class SQLTable;
	
	class SQLDatabase
	{
		private:
		std::shared_ptr<std::vector<std::string>> lastTables;
		
		protected:
		SQLConnection* con;
		
		public:
		SQLDatabase(SQLConnection*);
		
		SQLTable operator[](std::string name) const;
		
		class iterator
		{
			private:
			typename std::vector<std::string>::iterator vIt;
			std::shared_ptr<std::vector<std::string>> names;
			SQLConnection* con;
			iterator(SQLConnection*, std::shared_ptr<std::vector<std::string>> names, bool end = false);
			public:
			
			SQLTable operator*() const;
			iterator operator++();
			bool operator==(const iterator) const;
			bool operator!=(const iterator) const;
			
			friend class SQLDatabase;
		};
		
		iterator begin();
		iterator end() const;
	};
}
}