#pragma once

#include "../SQLConnection.h"
#include "SQLiteQuery.h"
#include <string>
#include <functional>

class sqlite3;

namespace QUtils
{
namespace SQL
{
	
	class SQLiteConnection : public SQLConnection
	{
		protected:
		std::string filename;
		
		sqlite3* db;
		bool useWAL;
		
		std::function<void(int, char const*, char const*, long long)> updateHook;
		std::function<int(int, const char*, const char*, const char*, const char*)> authorizerHook;
		
		
		void registerUpdateHook();
		void registerAuthorizerHook();
		
		public:
		SQLiteConnection(int WAL = true);
		SQLiteConnection(std::string file, int WAL = true);
		virtual ~SQLiteConnection();
		
		virtual bool isOpen() const override;
		virtual void open() override;
		virtual void close() override;
		virtual SQLiteQuery* query(std::string) const override;
		virtual bool vQuery(std::string query) override;
		virtual SQLQuery* tablesQuery(std::string tableName = "") const override;
		virtual bool tableExists(std::string name) const override;
		virtual std::vector<ColumnInfo> tableColumns(const std::string tableName) const override;
		virtual bool tableHasRid(const std::string tableName) override;
		virtual void attachDatabase(const std::string schema, const std::string URI) override;
		virtual std::string getDefaultDBName() const override;
		virtual std::vector<std::string> getDatabases() const override;
		virtual std::string RIDType() const override;
		//virtual void buildTable(const SQLTableBuilder) override;
		
		
		
		
		
		
		void openWithFlags(int flags);
		void openNoCreate();
		std::string& file();
		const std::string& file() const;
		std::vector<sqlite3_stmt*> pending() const;
		
		template <class F>
		void setUpdateCallback(F);
		template <class F>
		void setAuthorizerCallback(F);
		
	};
}
}

#include "SQLiteConnection.hpp"