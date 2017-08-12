#include <QUtils/SQL/SQLObjects.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLDatabase.h>

namespace QUtils
{
namespace SQL
{
	SQLObject::SQLObject(SQLConnection* con) : _connection(con), connection(_connection)
	{
		
	}
	
	SQLObject& SQLObject::operator=(const SQLObject& obj)
	{
		_connection = obj.connection;
		return *this;
	}
	
	
	
}
}