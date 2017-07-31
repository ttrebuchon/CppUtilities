#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLColumn.h>
#include <QUtils/SQL/SQLQuery.h>

namespace QUtils
{
namespace SQL
{
	SQLTable::SQLTable(SQLConnection* con, std::string name) : con(con), _name(name), _columns(), _columnsByName(), _PK(NULL), /*columns(_columns), columnsByName(_columnsByName),*/ columns(_columns, _columnsByName, _PK), name(_name)
	{
		refreshColumns();
	}
	
	SQLTable& SQLTable::operator=(const SQLTable t)
	{
		con = t.con;
		_columns = t._columns;
		_columnsByName = t._columnsByName;
		_PK = t._PK;
		_name = t._name;
		return *this;
	}
	
	long SQLTable::count() const
	{
		SQLQuery* q = con->query("SELECT COUNT(rowid) FROM [" + name + "]");
		q->next();
		long n = q->column<long>(0);
		delete q;
		return n;
	}
	
	void SQLTable::drop()
	{
		con->vQuery("DROP TABLE IF EXISTS [" + name + "];");
	}
	
	
	SQLTable SQLTable::join(const SQLTable t, std::string col1, std::string col2) const
	{
		con->vQuery("CREATE TEMP TABLE [" + name + "_" + t.name + "] AS SELECT * FROM ([" + name + "] JOIN [" + t.name + "] ON [" + name + "].[" + col1 + "]=[" + t.name + "].[" + col2 + "]);");
		return SQLTable(con, name + "_" + t.name);
		
	}
	
	const std::shared_ptr<SQLColumn> SQLTable::primary() const
	{
		return _PK;
	}
	
	void SQLTable::refresh()
	{
		refreshColumns();
	}
	
	
	
	
	
	
	void SQLTable::refreshColumns()
	{
		_PK = NULL;
		_columns.clear();
		_columnsByName.clear();
		
		
		auto info = con->tableColumns(name);
		std::shared_ptr<SQLColumn> ptr;
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
			}
		}
	}
	
	SQLQuery* SQLTable::rows() const
	{
		return con->query("SELECT rowid,* FROM [" + name + "];");
	}
	
	SQLQuery* SQLTable::select(std::string cols) const
	{
		return con->query("SELECT " + cols + " FROM [" + name + "];");
	}
	
	std::string SQLTable::tableStatement() const
	{
		std::string statement;
		SQLQuery* query = con->tablesQuery(name);
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