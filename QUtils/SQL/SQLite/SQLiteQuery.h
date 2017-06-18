#pragma once

#include "../Query.h"
#include <string>

class sqlite3;
class sqlite3_stmt;

namespace Util
{
namespace SQL
{
	class SQLiteQuery : public Query
	{
		protected:
		sqlite3_stmt* stmt;
		int status;
		
		
		virtual double columnDouble(int) override;
		virtual int columnInt(int) override;
		virtual long columnLong(int) override;
		virtual std::string columnString(int) override;
		
		
		
		
		public:
		SQLiteQuery(sqlite3_stmt*);
		virtual ~SQLiteQuery();
		
		
		virtual int width() const override;
		virtual ValueType columnType(int index) const override;
		virtual bool columnNULL(int) override;
		virtual bool next() override;
		virtual void reset() override;
		virtual bool operator()() override;
		
		virtual std::string columnName(int) const override;
		virtual std::string tableName(int) const override;
		virtual std::string dbName(int) const override;
		virtual std::string statement() const override;
	};
	
}
}