#pragma once

namespace QUtils
{
namespace SQL
{
	template <class F>
	void SQLiteConnection::setUpdateCallback(F f)
	{
		updateHook = [f](int code, const char* db, const char* table, long long row)
		{
			f(code, db, table, row);
		};
		registerUpdateHook();
	}
	
	template <class F>
	void SQLiteConnection::setAuthorizerCallback(F f)
	{
		authorizerHook = [f](auto... args) -> int
		{
			return f(args...);
		};
		registerAuthorizerHook();
	}
}
}