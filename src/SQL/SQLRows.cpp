#include <QUtils/SQL/SQLRows.h>
#include <QUtils/SQL/SQLRow.h>
#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLQuery.h>
#include <QUtils/SQL/SQLColumn.h>

#include <QUtils/Exception/Exception.h>
#include <QUtils/Exception/NotImplemented.h>


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
	
	
	
	SQLRow SQLRows_RID_Obj::operator[](SQLRID rid)
	{
		std::shared_ptr<SQLRow_Obj> rowObj;
		if (containers.count(rid) > 0)
		{
			if (rowObj = containers.at(rid).lock())
			{
				return SQLRow(rowObj);
			}
			else
			{
				containers.erase(rid);
			}
		}
		
		auto query = std::shared_ptr<SQLQuery>(connection->query("SELECT * FROM " + table->name + " WHERE rowid=@RID LIMIT 1;"));
		query->bind(1, (C_ValueType<Integer>::type)rid);
		if (!query->next())
		{
			throw SQLErrorException().Msg("No row with rowid " + std::to_string(rid)).Line(__LINE__).Function(__func__);
		}
		
		rowObj = std::shared_ptr<SQLRow_Obj>(new SQLRow_Obj(query, table->name, rid));
		
		containers[rid] = rowObj;
		return SQLRow(rowObj);
	}
	
	SQLRow SQLRows_RID_Obj::operator[](SQLPK val)
	{
		//TODO
		auto PK = table->primary();
		if (PK == NULL)
		{
			throw SQLErrorException().Msg("Can't find primary key column in " + table->name).File(__FILE__).Line(__LINE__);
		}
		SQLQuery* ridQuery = connection->query("SELECT rowid FROM " + table->name + " WHERE @PK=@VAL");
		ridQuery->bind(1, table->primary()->name);
		ridQuery->bind(2, val);
		while (ridQuery->next())
		{
			SQLRID rid(ridQuery->column<typename C_ValueType<Integer>::type>(0));
			delete ridQuery;
			return (*this)[rid];
		}
		delete ridQuery;
		throw SQLErrorException().Msg("No row with provided primary key value").File(__FILE__).Line(__LINE__);
	}
	
	
	
	SQLRows_PK_Obj::SQLRows_PK_Obj(const SQLTable table) : SQLRows_Obj(table), containers()
	{
		
	}
	
	
	SQLRow SQLRows_PK_Obj::operator[](SQLRID rid)
	{
		throw SQLTableHasNoRowIDException();
	}
	
	SQLRow SQLRows_PK_Obj::operator[](SQLPK val)
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