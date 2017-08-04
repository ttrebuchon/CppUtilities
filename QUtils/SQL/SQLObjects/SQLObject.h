#pragma once
#include <memory>

namespace QUtils
{
namespace SQL
{
	class SQLConnection;
	
	
	class SQLObject
	{
		protected:
		SQLConnection* _connection;
		
		SQLObject(SQLConnection* con);
		
		public:
		SQLConnection* const connection;
		
		SQLObject& operator=(const SQLObject&);
		
		
	};
}
}