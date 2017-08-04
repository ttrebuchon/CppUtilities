#include <QUtils/SQL/SQLRows.h>
#include <QUtils/SQL/SQLRow.h>
#include <QUtils/SQL/SQLTable.h>

#include <QUtils/Exception/NotImplemented.h>

#include <iostream>


namespace QUtils
{
namespace SQL
{
	QUTILS_CUSTOM_EXCEPTION(SQLTableHasNoRowIDException, Table has no rowid);
	
	
namespace Internal
{
	SQLRows_Obj::SQLRows_Obj(const SQLTable table) : SQLTableObject(table)
	{
		
	}
	
	SQLRows_Obj::~SQLRows_Obj()
	{
		
	}
	
	
	
	
	
	
	SQLRows_RID_Obj::SQLRows_RID_Obj(const SQLTable table) : SQLRows_Obj(table), containers()
	{
		
	}
	
	
	
	SQLRow SQLRows_RID_Obj::operator[](SQLRID rid) const
	{
		//TODO
		throw NotImp();
		
	}
	
	SQLRow SQLRows_RID_Obj::operator[](SQLPK val) const
	{
		//TODO
		throw NotImp();
	}
	
	
	
	SQLRows_PK_Obj::SQLRows_PK_Obj(const SQLTable table) : SQLRows_Obj(table), containers()
	{
		
	}
	
	
	SQLRow SQLRows_PK_Obj::operator[](SQLRID rid) const
	{
		throw SQLTableHasNoRowIDException();
	}
	
	SQLRow SQLRows_PK_Obj::operator[](SQLPK val) const
	{
		//TODO
		throw NotImp();
	}
	/*
}






	SQLRows::SQLRows(std::shared_ptr<Internal::SQLRows_Obj> behind, const SQLDatabase& db) : SQLDatabaseObject(db), behind(behind)
	{
		
	}
	
	
	
	SQLRow SQLRows::operator[](SQLRID rid) const
	{
		return (*behind)[rid];
	}
	
	SQLRow SQLRows::operator[](SQLPK val) const
	{
		return (*behind)[val];
	}*/
}
}
}