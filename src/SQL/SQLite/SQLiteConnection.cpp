#include <QUtils/SQL/SQLite/SQLiteConnection.h>
#include <QUtils/SQL/SQLite/SQLiteQuery.h>
#include <QUtils/SQL/SQL_Name.h>

#include <QUtils/String/String.h>

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
	
	void SQLiteConnection::registerAuthorizerHook()
	{
		sqlite3_set_authorizer(db, &Helpers::sqlite_callback<int, int, const char*, const char*, const char*, const char*>, (void*)&authorizerHook);
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
			throw SQLErrorException().Msg(sqlite3_errmsg(db) + std::string("\t\tQuery: '") + str + "'").Function(__func__).File(__FILE__).Line(__LINE__);
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
			throw SQLErrorException().Msg(err + " (" + std::to_string(status) + ") " + std::string("\t\tQuery: '") + query + "'");
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
	
	
	SQLQuery* SQLiteConnection::tablesQuery(std::string tableName) const
	{
		if (tableName == "")
		{
			return query("SELECT name, sql AS statement FROM [sqlite_master] WHERE type='table'");
		}
		else
		{
			if (tableName[0] == '[')
			{
				tableName = SQL_Name_Parse(tableName).back();
			}
			auto q = query("SELECT name, sql AS statement FROM [sqlite_master] WHERE type='table' AND name=@NAME");
			q->bind("@NAME", tableName);
			return q;
		}
	}
	
	bool SQLiteConnection::tableExists(const std::string name) const
	{
		SQLQuery* q = query("SELECT name FROM [sqlite_master] WHERE type='table' AND name=@TABLENAME;");
		q->bind("@TABLENAME", name);
		
		
		while (q->next())
		{
			delete q;
			return true;
		}
		delete q;
		return false;
	}
	
	std::vector<SQLConnection::ColumnInfo> SQLiteConnection::tableColumns(const std::string tableName) const
	{
		auto parsed = SQL_Name_Parse(tableName);
		std::string prefix = "";
		for (size_t i = 0; i < parsed.size()-1; ++i)
		{
			prefix += "[" + parsed[i] + "].";
		}
		std::vector<ColumnInfo> info;
		SQLQuery* tableInfo = query("PRAGMA " + prefix + "table_info([" + parsed.back() + "]);");
		
		while (tableInfo->next())
		{
			info.push_back(ColumnInfo(tableInfo->column<int>(0), tableInfo->column<std::string>(1), tableInfo->column<std::string>(2), tableInfo->column<int>(3), tableInfo->column<std::string>(4), tableInfo->column<int>(5)));
			
			
		}
		
		delete tableInfo;
		return info;
	}
	
	bool SQLiteConnection::tableHasRid(const std::string tableName)
	{
		QUtils::String statement;
		SQLQuery* query = tablesQuery(tableName);
		while (query->next())
		{
			statement = query->column<std::string>(1);
			delete query;
			return !statement.toUpper().contains("WITHOUT ROWID");
		}
		
		delete query;
		query = this->query("SELECT rowid FROM " + tableName + " LIMIT 1;");
		while (query->next())
		{
			delete query;
			return true;
		}
		delete query;
		return false;
	}
	
	
	void SQLiteConnection::attachDatabase(const std::string schema, const std::string URI)
	{
		try
		{
			vQuery("ATTACH DATABASE '" + URI + "' AS [" + schema + "];");
		}
		catch (...)
		{
			throw SQLErrorException(std::current_exception()).Function(__func__).File(__FILE__).Line(__LINE__);
		}
	}
	
	std::string SQLiteConnection::getDefaultDBName() const
	{
		return "main";
	}
	
	std::vector<std::string> SQLiteConnection::getDatabases() const
	{
		
		SQLQuery* q = NULL;
		try
		{
			std::vector<std::string> databases;
			q = query("PRAGMA DATABASE_LIST;");
			while (q->next())
			{
				databases.push_back(q->column<std::string>(1));
			}
			delete q;
			return databases;
		}
		catch (...)
		{
			if (q != NULL)
			{
				delete q;
			}
			throw SQLErrorException(std::current_exception()).Function(__func__).Line(__LINE__);
		}
	}
	
	
	std::string SQLiteConnection::RIDType() const
	{
		return "INTEGER";
	}
	
	void SQLiteConnection::createTables(const std::vector<SQLTableBuilder>& builders)
	{
		vQuery("BEGIN;");
		
		std::string text;
		for (auto& builder : builders)
		{
			text = "CREATE TABLE " + builder.to_string() + ";";
			vQuery(text);
		}
		
		
		vQuery("COMMIT;");
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