#include <QUtils/SQL/SQLite/SQLiteConnection.h>
#include <QUtils/SQL/SQLite/SQLiteQuery.h>
#include <sqlite3.h>
#include <iostream>


namespace QUtils
{
namespace SQL
{
	namespace Helpers
	{
		template <class Ret, class ...Args>
		Ret sqlite_callback(void* callback, Args... args)
		{
			auto func = (std::function<Ret(Args...)>*)callback;
			return (*func)(args...);
		}
	}
	void SQLiteConnection::registerUpdateHook()
	{
		sqlite3_update_hook(db, &Helpers::sqlite_callback<void, int, char const*, char const*, long long>, (void*)&updateHook);
	}
	
	
	
	
	
	
	
	
	
	
	
	SQLiteConnection::SQLiteConnection(int WAL) : SQLiteConnection("", WAL)
	{
		
	}
	
	SQLiteConnection::SQLiteConnection(std::string file, int WAL) : filename(file), db(NULL), useWAL(WAL > 0), updateHook()
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
		#ifdef PRINT_SQL_QUERIES
		std::cout << str << "\n";
		#endif
		sqlite3_stmt* stmt = NULL;
		int status;
		
		status = sqlite3_prepare_v2(db, str.c_str(), -1, &stmt, NULL);
		if (status != SQLITE_OK)
		{
			sqlite3_finalize(stmt);
			throw SQLErrorException().Msg(sqlite3_errmsg(db) + std::string("\t\tQuery: '") + str + "'");
		}
		
		return new SQLiteQuery(stmt);
	}
	
	bool SQLiteConnection::vQuery(std::string query)
	{
		#ifdef PRINT_SQL_QUERIES
		std::cout << query << "\n";
		#endif
		sqlite3_stmt* ptr = NULL;
		int status;
		if ((status = sqlite3_prepare_v2(db, query.c_str(), -1, &ptr, NULL)) != SQLITE_OK)
		{
			std::string err = sqlite3_errmsg(db);
			sqlite3_finalize(ptr);
			throw SQLErrorException().Msg(err + " (" + std::to_string(status) + ")");
			return false;
		}
		status = SQLITE_ROW;
		while (status == SQLITE_ROW)
		{
			status = sqlite3_step(ptr);
		}
		if (status != SQLITE_DONE)
		{
			std::string err = sqlite3_errmsg(db);
			sqlite3_finalize(ptr);
			throw SQLErrorException().Msg(err + " (" + std::to_string(status) + ")");
		}
		sqlite3_finalize(ptr);
		return true;
	}
	
	
	Query* SQLiteConnection::tablesQuery(std::string tableName) const
	{
		if (tableName == "")
		{
			return query("SELECT name, sql AS statement FROM [sqlite_master] WHERE type='table'");
		}
		else
		{
			return query("SELECT name, sql AS statement FROM [sqlite_master] WHERE type='table' AND name='" + tableName + "'");
		}
	}
	
	bool SQLiteConnection::tableExists(std::string name) const
	{
		Query* q = query("SELECT name FROM [sqlite_master] WHERE type='table' AND name='" + name + "';");
		while (q->next())
		{
			delete q;
			return true;
		}
		delete q;
		return false;
	}
	
	std::vector<Connection::ColumnInfo> SQLiteConnection::tableColumns(const std::string tableName) const
	{
		std::vector<ColumnInfo> info;
		Query* tableInfo = query("PRAGMA table_info([" + tableName + "]);");
		
		while (tableInfo->next())
		{
			info.push_back(ColumnInfo(tableInfo->column<int>(0), tableInfo->column<std::string>(1), tableInfo->column<std::string>(2), tableInfo->column<int>(3), tableInfo->column<std::string>(4), tableInfo->column<int>(5)));
			
			
		}
		
		delete tableInfo;
		return info;
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
	
	std::vector<sqlite3_stmt*> SQLiteConnection::pending() const
	{
		std::vector<sqlite3_stmt*> vec;
		for (auto stmt = sqlite3_next_stmt(db, NULL); stmt != NULL; stmt = sqlite3_next_stmt(db, stmt))
		{
			vec.push_back(stmt);
		}
		return vec;
	}
}
}