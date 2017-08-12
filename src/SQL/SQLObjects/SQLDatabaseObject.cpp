#include <QUtils/SQL/SQLObjects.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLDatabase.h>

namespace QUtils
{
namespace SQL
{
	SQLDatabaseObject::SQLDatabaseObject(const SQLDatabase DB) : SQLObject(DB->connection), _database(DB), database(_database)
	{
		
	}
	
	
	SQLDatabaseObject& SQLDatabaseObject::operator=(const SQLDatabaseObject& obj)
	{
		SQLObject::operator=(obj);
		_database = obj.database;
		return *this;
	}
}
}