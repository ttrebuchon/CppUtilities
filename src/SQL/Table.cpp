#include <QUtils/SQL/Table.h>
#include <QUtils/SQL/Connection.h>
#include <QUtils/SQL/Column.h>
#include <QUtils/SQL/Query.h>

namespace QUtils
{
namespace SQL
{
	Table::Table(Connection* con, std::string name) : con(con), _columns(), _PK(NULL), name(name), columns(_columns)
	{
		refreshColumns();
	}
	
	long Table::count() const
	{
		Query* q = con->query("SELECT COUNT(rowid) FROM [" + name + "]");
		q->next();
		long n = q->column<long>(0);
		delete q;
		return n;
	}
	
	bool Table::drop()
	{
		if (con->tableExists(name))
		{
			con->vQuery("DROP TABLE [" + name + "];");
			return true;
		}
		return false;
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
		
		
		auto info = con->tableColumns(name);
		for (auto col : info)
		{
			_columns.push_back(std::make_shared<Column>(std::get<0>(col), std::get<1>(col), std::get<2>(col), std::get<3>(col), std::get<4>(col), std::get<5>(col)));
		}
		
		for (auto col : this->columns)
		{
			if (col->PK)
			{
				_PK = col;
			}
		}
	}
	
	
	
}
}