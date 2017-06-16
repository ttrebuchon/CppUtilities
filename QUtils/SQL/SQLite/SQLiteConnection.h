#pragma once

#include "../Connection.h"
#include "SQLiteQuery.h"
#include <string>

class sqlite3;

namespace Util
{
namespace SQL
{
	
	
	class SQLiteConnection : public Connection
	{
		protected:
		std::string filename;
		
		sqlite3* db;
		
		
		public:
		SQLiteConnection();
		SQLiteConnection(std::string file);
		virtual ~SQLiteConnection();
		
		virtual bool isOpen() const override;
		virtual void open() override;
		virtual void close() override;
		virtual SQLiteQuery* query(std::string) override;
		virtual bool vQuery(std::string query) override;
		
		
		void openOrCreate();
		std::string& file();
		const std::string& file() const;
		
	};
}
}