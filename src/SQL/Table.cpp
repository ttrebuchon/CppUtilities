#include <QUtils/SQL/Table.h>
#include <QUtils/SQL/Connection.h>
#include <QUtils/SQL/Column.h>
#include <QUtils/SQL/Query.h>

namespace QUtils
{
namespace SQL
{
	Table::Table(Connection* con, std::string name) : con(con), _name(name), _columns(), _columnsByName(), _PK(NULL), /*columns(_columns), columnsByName(_columnsByName),*/ columns(_columns, _columnsByName, _PK), name(_name)
	{
		refreshColumns();
	}
	
	Table& Table::operator=(const Table t)
	{
		con = t.con;
		_columns = t._columns;
		_columnsByName = t._columnsByName;
		_PK = t._PK;
		_name = t._name;
		return *this;
	}
	
	long Table::count() const
	{
		Query* q = con->query("SELECT COUNT(rowid) FROM [" + name + "]");
		q->next();
		long n = q->column<long>(0);
		delete q;
		return n;
	}
	
	void Table::drop()
	{
		con->vQuery("DROP TABLE IF EXISTS [" + name + "];");
	}
	
	
	Table Table::join(const Table t, std::string col1, std::string col2) const
	{
		con->vQuery("CREATE TEMP TABLE [" + name + "_" + t.name + "] AS SELECT * FROM ([" + name + "] JOIN [" + t.name + "] ON [" + name + "].[" + col1 + "]=[" + t.name + "].[" + col2 + "]);");
		return Table(con, name + "_" + t.name);
		
	}
	
	const std::shared_ptr<Column> Table::primary() const
	{
		return _PK;
	}
	
	void Table::refresh()
	{
		refreshColumns();
	}
	
	
	
	
	
	
	void Table::refreshColumns()
	{
		_PK = NULL;
		_columns.clear();
		_columnsByName.clear();
		
		
		auto info = con->tableColumns(name);
		std::shared_ptr<Column> ptr;
		for (auto col : info)
		{
			
			_columns.push_back(ptr = std::make_shared<Column>(std::get<0>(col), std::get<1>(col), std::get<2>(col), std::get<3>(col), std::get<4>(col), std::get<5>(col), name));
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
	
	Query* Table::rows() const
	{
		return con->query("SELECT rowid,* FROM [" + name + "];");
	}
	
	Query* Table::select(std::string cols) const
	{
		return con->query("SELECT " + cols + " FROM [" + name + "];");
	}
	
	std::string Table::tableStatement() const
	{
		std::string statement;
		Query* query = con->tablesQuery(name);
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