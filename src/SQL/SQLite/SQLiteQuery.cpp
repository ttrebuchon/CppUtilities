#include <QUtils/SQL/SQLite/SQLiteQuery.h>
#include <QUtils/SQL/Errors.h>
#include <sqlite3.h>
#include <iostream>

namespace QUtils
{
namespace SQL
{
	SQLiteQuery::SQLiteQuery(sqlite3_stmt* ptr) : stmt(ptr), status(SQLITE_OK)
	{
		
	}
	
	SQLiteQuery::~SQLiteQuery()
	{
		//TODO
		sqlite3_finalize(stmt);
	}
	
	int SQLiteQuery::width() const
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
	
	bool SQLiteQuery::columnNULL(int index) const
	{
		return sqlite3_column_type(stmt, index) == SQLITE_NULL;
	}
	
	bool SQLiteQuery::next()
	{
		status = sqlite3_step(stmt);
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
		status = sqlite3_reset(stmt);
	}
	
	bool SQLiteQuery::operator()()
	{
		if (status == SQLITE_OK)
		{
			status = sqlite3_step(stmt);
		}
		return (status == SQLITE_ROW);
		//return (sqlite3_data_count(stmt) > 0);
	}
	
	std::string SQLiteQuery::columnName(int index) const
	{
		auto cstr = sqlite3_column_name(stmt, index);
		if (cstr == NULL)
		{
			//TODO
			throw std::exception();
		}
		return std::string(cstr);
	}
	
	std::string SQLiteQuery::tableName(int index) const
	{
		auto cstr = sqlite3_column_table_name(stmt, index);
		if (cstr == NULL)
		{
			//TODO
			throw std::exception();
		}
		return std::string(cstr);
	}
	
	std::string SQLiteQuery::dbName(int index) const
	{
		auto cstr = sqlite3_column_database_name(stmt, index);
		if (cstr == NULL)
		{
			//TODO
			throw std::exception();
		}
		return std::string(cstr);
	}
	
	std::string SQLiteQuery::statement() const
	{
		auto cstr = sqlite3_expanded_sql(stmt);
		if (cstr == NULL)
		{
			//TODO
			throw std::exception();
		}
		return std::string(cstr);
	}
	
	
	
	
	
	
	double SQLiteQuery::columnDouble(int index) const
	{
		return sqlite3_column_double(stmt, index);
	}
	
	int SQLiteQuery::columnInt(int index) const
	{
		return sqlite3_column_int(stmt, index);
	}
	
	long SQLiteQuery::columnLong(int index) const
	{
		return sqlite3_column_int64(stmt, index);
	}
	
	std::string SQLiteQuery::columnString(int index) const
	{
		auto cstr = sqlite3_column_text(stmt, index);
		if (cstr == NULL)
		{
			return "NULL";
		}
		return std::string(reinterpret_cast<const char*>(cstr));
	}
	
	
	
	
	
	void SQLiteQuery::unbind()
	{
		int result;
		if ((result = sqlite3_clear_bindings(stmt)) != 0)
		{
			//TODO
			throw SQLErrorException().Msg(sqlite3_errstr(result));
		}
	}
	
	
	
	
	
	void SQLiteQuery::bind(std::string parameter, double value)
	{
		auto index = sqlite3_bind_parameter_index(stmt, parameter.c_str());
		if (index == 0)
		{
			throw SQLErrorException().Msg("No parameter with name '" + parameter + "' in statement");
		}
		
		this->bind(index, value);
	}
	
	void SQLiteQuery::bind(std::string parameter, int value)
	{
		auto index = sqlite3_bind_parameter_index(stmt, parameter.c_str());
		if (index == 0)
		{
			throw SQLErrorException().Msg("No parameter with name '" + parameter + "' in statement");
		}
		
		this->bind(index, value);
	}
	
	void SQLiteQuery::bind(std::string parameter, long value)
	{
		auto index = sqlite3_bind_parameter_index(stmt, parameter.c_str());
		if (index == 0)
		{
			throw SQLErrorException().Msg("No parameter with name '" + parameter + "' in statement");
		}
		
		this->bind(index, value);
	}
	
	void SQLiteQuery::bind(std::string parameter, std::string value)
	{
		auto index = sqlite3_bind_parameter_index(stmt, parameter.c_str());
		if (index == 0)
		{
			throw SQLErrorException().Msg("No parameter with name '" + parameter + "' in statement");
		}
		
		this->bind(index, value);
	}
	
	
	
	void SQLiteQuery::bind(unsigned int index, double value)
	{
		auto result = sqlite3_bind_double(stmt, index, value);
		if (result != SQLITE_OK)
		{
			this->status = result;
			throw SQLErrorException().Msg(sqlite3_errstr(result));
		}
	}
	
	void SQLiteQuery::bind(unsigned int index, int value)
	{
		auto result = sqlite3_bind_int(stmt, index, value);
		if (result != SQLITE_OK)
		{
			this->status = result;
			throw SQLErrorException().Msg(sqlite3_errstr(result));
		}
	}
	
	void SQLiteQuery::bind(unsigned int index, long value)
	{
		auto result = sqlite3_bind_int64(stmt, index, value);
		if (result != SQLITE_OK)
		{
			this->status = result;
			throw SQLErrorException().Msg(sqlite3_errstr(result));
		}
	}
	
	void SQLiteQuery::bind(unsigned int index, std::string value)
	{
		auto result = sqlite3_bind_text(stmt, index, value.c_str(), value.length(), SQLITE_TRANSIENT);
		if (result != SQLITE_OK)
		{
			this->status = result;
			throw SQLErrorException().Msg(sqlite3_errstr(result));
		}
	}
	
	
}
}