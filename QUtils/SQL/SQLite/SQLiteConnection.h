#pragma once

#include "../Connection.h"
#include "SQLiteQuery.h"
#include <string>

class sqlite3;

namespace QUtils
{
namespace SQL
{
	
	
	class SQLiteConnection : public Connection
	{
		protected:
		std::string filename;
		
		sqlite3* db;
		bool useWAL;
		
		public:
		SQLiteConnection(int WAL = true);
		SQLiteConnection(std::string file, int WAL = true);
		virtual ~SQLiteConnection();
		
		virtual bool isOpen() const override;
		virtual void open() override;
		virtual void close() override;
		virtual SQLiteQuery* query(std::string) const override;
		virtual bool vQuery(std::string query) override;
		virtual Query* tablesQuery() const override;
		virtual bool tableExists(std::string name) const override;
		virtual std::vector<ColumnInfo> tableColumns(const std::string tableName) const override;
		
		
		void openWithFlags(int flags);
		void openNoCreate();
		std::string& file();
		const std::string& file() const;
		std::vector<sqlite3_stmt*> pending() const;
		
	};
}
}