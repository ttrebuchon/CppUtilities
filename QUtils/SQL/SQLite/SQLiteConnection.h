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
		
		
		void registerUpdateHook();
		
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
		
		
		void openWithFlags(int flags);
		void openNoCreate();
		std::string& file();
		const std::string& file() const;
		std::vector<sqlite3_stmt*> pending() const;
		
		template <class F>
		void setUpdateCallback(F f)
		{
			updateHook = [f](int code, const char* db, const char* table, long long row)
			{
				f(code, db, table, row);
			};
			registerUpdateHook();
		}
		
	};
}
}