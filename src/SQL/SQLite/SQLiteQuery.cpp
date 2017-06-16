#include <QUtils/SQL/SQLite/SQLiteQuery.h>
#include <sqlite3.h>
#include <iostream>

namespace Util
{
namespace SQL
{
	SQLiteQuery::SQLiteQuery(sqlite3_stmt* ptr) : stmt(ptr)
	{
		
	}
	
	SQLiteQuery::~SQLiteQuery()
	{
		//TODO
	}
	
	int SQLiteQuery::count() const
	{
		return sqlite3_column_count(stmt);
	}
	
	ValueType SQLiteQuery::columnType(int index) const
	{
		switch (sqlite3_column_type(stmt, index))
		{
			case SQLITE_INTEGER:
			return Integer;
			
			case SQLITE_TEXT:
			return Text;
			
			
			
			case SQLITE_NULL:
			return ValueType::Null;
			
			default:
			//TODO
			throw std::exception();
			
		}
	}
	
	bool SQLiteQuery::columnNULL(int index)
	{
		return sqlite3_column_type(stmt, index) == SQLITE_NULL;
	}
	
	bool SQLiteQuery::next()
	{
		int status = sqlite3_step(stmt);
		switch (status)
		{
			case SQLITE_ROW:
			return true;
			
			case SQLITE_DONE:
			return false;
			
			default:
			throw std::exception();
		}
	}
	
	void SQLiteQuery::reset()
	{
		sqlite3_reset(stmt);
		next();
	}
	
	bool SQLiteQuery::operator()()
	{
		return (sqlite3_data_count(stmt) > 0);
	}
	
	
	
	
	
	
	double SQLiteQuery::columnDouble(int index)
	{
		return sqlite3_column_double(stmt, index);
	}
	
	int SQLiteQuery::columnInt(int index)
	{
		return sqlite3_column_int(stmt, index);
	}
	
	long SQLiteQuery::columnLong(int index)
	{
		return sqlite3_column_int64(stmt, index);
	}
	
	std::string SQLiteQuery::columnString(int index)
	{
		return std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, index)));
	}
	
	
}
}