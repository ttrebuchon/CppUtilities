#pragma once

#include "../SQLQuery.h"
#include <string>

class sqlite3;
class sqlite3_stmt;

namespace QUtils
{
namespace SQL
{
	class SQLiteQuery : public SQLQuery
	{
		protected:
		sqlite3_stmt* stmt;
		int status;
		
		
		virtual double columnDouble(int) const override;
		virtual int columnInt(int) const override;
		virtual long columnLong(int) const override;
		virtual std::string columnString(int) const override;
		
		
		
		
		public:
		SQLiteQuery(sqlite3_stmt*);
		virtual ~SQLiteQuery();
		
		
		virtual int width() const override;
		virtual ValueType columnType(int index) const override;
		virtual bool columnNULL(int) const override;
		virtual bool next() override;
		virtual void reset() override;
		virtual bool operator()() override;
		
		virtual std::string columnName(int) const override;
		virtual std::string tableName(int) const override;
		virtual std::string dbName(int) const override;
		virtual std::string statement() const override;
		
		
		
		
		virtual void unbind() override;
		
		virtual void bind(std::string parameter, double value) override;
		virtual void bind(std::string parameter, int value) override;
		virtual void bind(std::string parameter, long value) override;
		virtual void bind(std::string parameter, std::string value) override;
		
		virtual void bind(unsigned int index, double value) override;
		virtual void bind(unsigned int index, int value) override;
		virtual void bind(unsigned int index, long value) override;
		virtual void bind(unsigned int index, std::string value) override;
	};
	
}
}