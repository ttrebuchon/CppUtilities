#include <QUtils/SQL/SQLite/SQLiteConnection.h>
#include <QUtils/SQL/SQLite/SQLiteQuery.h>
#include <sqlite3.h>
#include <iostream>


namespace Util
{
namespace SQL
{
	SQLiteConnection::SQLiteConnection(int WAL) : SQLiteConnection("", WAL)
	{
		
	}
	
	SQLiteConnection::SQLiteConnection(std::string file, int WAL) : filename(file), db(NULL), useWAL(WAL > 0)
	{
		
	}
	
	SQLiteConnection::~SQLiteConnection()
	{
		if (isOpen())
		{
			close();
		}
		
	}
	
	
	bool SQLiteConnection::isOpen() const
	{
		return (db != NULL);
	}
	
	void SQLiteConnection::open()
	{
		openWithFlags(-1);
	}
	
	void SQLiteConnection::close()
	{
		if (db == NULL)
		{
			//TODO
			throw std::exception();
		}
		
		sqlite3_close(db);
		db = NULL;
	}
	
	
	
	SQLiteQuery* SQLiteConnection::query(std::string str) const
	{
		sqlite3_stmt* stmt = NULL;
		int status;
		
		status = sqlite3_prepare_v2(db, str.c_str(), -1, &stmt, NULL);
		if (status == SQLITE_ERROR)
		{
			sqlite3_finalize(stmt);
			throw SQLErrorException().Msg(sqlite3_errmsg(db));
		}
		sqlite3_step(stmt);
		return new SQLiteQuery(stmt);
	}
	
	bool SQLiteConnection::vQuery(std::string query)
	{
		sqlite3_stmt* ptr = NULL;
		if (sqlite3_prepare(db, query.c_str(), -1, &ptr, NULL) != SQLITE_OK)
		{
			std::string err = sqlite3_errmsg(db);
			sqlite3_finalize(ptr);
			throw SQLErrorException().Msg(err);
			return false;
		}
		int status = SQLITE_OK;
		while (status != SQLITE_DONE && status != SQLITE_ERROR)
		{
			status = sqlite3_step(ptr);
		}
		if (status == SQLITE_ERROR)
		{
			std::string err = sqlite3_errmsg(db);
			throw SQLErrorException().Msg(err);
		}
		sqlite3_finalize(ptr);
		return true;
	}
	
	
	Query* SQLiteConnection::tablesQuery() const
	{
		return query("SELECT name FROM sqlite_master WHERE type='table'");
	}
	
	
	
	
	
	
	
	
	void SQLiteConnection::openWithFlags(int flags)
	{
		if (db != NULL)
		{
			//TODO
			throw std::exception();
		}
		
		if (filename == "")
		{
			//TODO
			std::cerr << "Inv Filename\n";
			throw std::exception();
		}
		
		if (flags == -1)
		{
			flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_SHAREDCACHE;
		}
		
		if (sqlite3_open_v2(filename.c_str(), &db, flags, NULL) != SQLITE_OK)
		{
			std::string err = sqlite3_errmsg(db);
			throw SQLErrorException().Msg(err);
		}
		
		if (useWAL)
		{
			vQuery("PRAGMA journal_mode=WAL");
		}
	}
	
	void SQLiteConnection::openNoCreate()
	{
		openWithFlags(SQLITE_OPEN_READWRITE | SQLITE_OPEN_SHAREDCACHE);
	}
	
	std::string& SQLiteConnection::file()
	{
		return filename;
	}
	
	const std::string& SQLiteConnection::file() const
	{
		return filename;
	}
}
}