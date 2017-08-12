#pragma once

#include "../SQLTypeDefs.h"
#include "SQLObject.h"

namespace QUtils
{
namespace SQL
{

	
	class SQLDatabaseObject : public SQLObject
	{
		protected:
		SQLDatabase _database;
		
		SQLDatabaseObject(const SQLDatabase DB);
		
		public:
		const SQLDatabase& database;
		
		SQLDatabaseObject& operator=(const SQLDatabaseObject&);
	};
	
	
}
}