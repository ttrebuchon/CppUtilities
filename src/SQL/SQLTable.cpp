#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLColumn.h>
#include <QUtils/SQL/SQLQuery.h>
#include <QUtils/SQL/SQLClause.h>
#include <QUtils/SQL/SQLDatabase.h>
#include <QUtils/SQL/SQL_Name.h>


namespace QUtils
{
namespace SQL
{
namespace Internal
{
	SQLTable_Obj::SQLTable_Obj(const SQLDatabase db, const std::string name) : SQLDatabaseObject(db),
	_name(name),
	_columns(),
	_columnsByName(),
	_PK(NULL),
	name(_name),
	columns(&_columns, &_columnsByName, _PK),
	rows(db->connection->tableHasRid(name) ? std::static_pointer_cast<Internal::SQLRows_Obj>(std::make_shared<Internal::SQLRows_RID_Obj>()) : std::static_pointer_cast<Internal::SQLRows_Obj>(std::make_shared<Internal::SQLRows_PK_Obj>()), db)
	{
		refreshColumns();
	}
	
	SQLTable_Obj::SQLTable_Obj(const SQLDatabaseObject& obj, const std::string name) : SQLTable_Obj(obj.database, name)
	{
		
	}
	

	
	
	/*
	
	
	SQLTable& SQLTable::operator=(const SQLTable t)
	{
		SQLDatabaseObject::operator=(t);
		behind = t.behind;
		//rows = SQLRows(connection->tableHasRid(name) ? std::static_pointer_cast<Internal::SQLRows_Obj>(std::make_shared<Internal::SQLRows_RID_Obj>()) : std::static_pointer_cast<Internal::SQLRows_Obj>(std::make_shared<Internal::SQLRows_PK_Obj>()));
		rows = t.rows;
		columns = t.columns;
		_name = t._name;
		return *this;
	}*/
	
	
	
	
	long SQLTable_Obj::count() const
	{
		SQLQuery* q = connection->query("SELECT COUNT(rowid) FROM [" + name + "]");
		q->next();
		long n = q->column<long>(0);
		delete q;
		return n;
	}
	
	void SQLTable_Obj::drop()
	{
		connection->vQuery("DROP TABLE IF EXISTS " + name + ";");
	}
	
	
	SQLTable SQLTable_Obj::join(const SQLTable t, std::string col1, std::string col2) const
	{
		std::string tName1, tName2;
		tName1 = SQL_Name_Parse(name).back();
		tName2 = SQL_Name_Parse(t->name).back();
		connection->vQuery("CREATE TEMP TABLE [" + tName1 + "_" + tName2 + "] AS SELECT * FROM (" + name + " JOIN " + t->name + " ON " + name + ".[" + col1 + "]=" + t->name + ".[" + col2 + "]);");
		return SQLTable::Create(database, "[" + tName1 + "_" + tName2 + "]");
		
	}
	
	const std::shared_ptr<SQLColumn> SQLTable_Obj::primary() const
	{
		return _PK;
	}
	
	void SQLTable_Obj::refresh()
	{
		refreshColumns();
	}
	
	
	
	
	
	
	void SQLTable_Obj::refreshColumns()
	{
		_PK = NULL;
		_columns.clear();
		_columnsByName.clear();
		
		
		auto info = connection->tableColumns(name);
		std::shared_ptr<SQLColumn> ptr;
		
		if (connection->tableHasRid(name))
		{
			
			ptr = std::make_shared<SQLColumn>(-1, "rowid", connection->RIDType(), 1, "", 0, name);
			
			_columnsByName["rowid"] = ptr;
			//_columns.push_back(ptr);
		}
		
		for (auto col : info)
		{
			
			_columns.push_back(ptr = std::make_shared<SQLColumn>(std::get<0>(col), std::get<1>(col), std::get<2>(col), std::get<3>(col), std::get<4>(col), std::get<5>(col), name));
			_columnsByName[std::get<1>(col)] = ptr;
		}
		
		
		
		for (auto col : this->columns)
		{
			if (col->PK)
			{
				_PK = col;
				return;
			}
		}
	}
	
	SQLQuery* SQLTable_Obj::rowsQuery() const
	{
		return connection->query("SELECT rowid,* FROM [" + name + "];");
	}
	
	SQLQuery* SQLTable_Obj::select(std::string cols) const
	{
		return connection->query("SELECT " + cols + " FROM " + name + ";");
	}
	
	SQLQuery* SQLTable_Obj::select(std::string cols, SQLClause clause) const
	{
		return connection->query("SELECT " + cols + " FROM " + name + " WHERE " + clause.toString() + ";");
	}
	
	std::string SQLTable_Obj::tableStatement() const
	{
		std::string statement;
		SQLQuery* query = connection->tablesQuery(name);
		while (query->next())
		{
			statement = query->column<std::string>(1);
			delete query;
			return statement;
		}
		
		delete query;
		
		throw SQLErrorException().Msg("Could not find CREATE statement for table '" + name + "'");
		
	}
}
}
}