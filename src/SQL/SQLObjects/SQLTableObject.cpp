#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLObjects/SQLTableObject.h>


namespace QUtils
{
namespace SQL
{
	SQLTableObject::SQLTableObject(const SQLTable table) : SQLDatabaseObject(table->database), _table(table), table(_table)
	{
		
	}
	
	
	SQLTableObject& SQLTableObject::operator=(const SQLTableObject& obj)
	{
		SQLDatabaseObject::operator=(obj);
		_table = obj.table;
		return *this;
	}
}
}