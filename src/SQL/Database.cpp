#include <QUtils/SQL/Database.h>
#include <QUtils/SQL/Table.h>
#include <QUtils/SQL/Connection.h>
#include <QUtils/SQL/Query.h>

namespace Util
{
namespace SQL
{
	Database::Database(Connection* con) : lastTables(NULL), con(con)
	{
		
	}
	
	
	Table Database::operator[](std::string table) const
	{
		Query* tables = con->tablesQuery();
		while ((*tables)())
		{
			if (tables->column<std::string>(0) == table)
			{
				delete tables;
				return Table(con, table);
			}
			tables->next();
		}
		delete tables;
		throw SQLErrorException().Msg("Table [" + table + "] not present in database");
	}
	
	
	
	
	
	
	
	
	
	Database::iterator::iterator(Connection* con, std::shared_ptr<std::vector<std::string>> names, bool end) : vIt(), names(names), con(con)
	{
		if (end)
		{
			vIt = names->end();
		}
		else
		{
			vIt = names->begin();
		}
	}
	
	
	
	Table Database::iterator::operator*() const
	{
		return Table(con, *vIt);
	}
	
	typename Database::iterator Database::iterator::operator++()
	{
		iterator it(con, names);
		it.vIt = this->vIt;
		vIt++;
		return it;
	}
	
	bool Database::iterator::operator==(const iterator it) const
	{
		return (vIt == it.vIt);
	}
	
	bool Database::iterator::operator!=(const iterator it) const
	{
		return !(operator==(it));
	}
	
	typename Database::iterator Database::begin()
	{
		lastTables = std::make_shared<std::vector<std::string>>();
		Query* q = con->tablesQuery();
		
		while (q->next())
		{
			lastTables->push_back(q->column<std::string>(0));
		}
		delete q;
		
		return iterator(con, lastTables);
	}
	
	typename Database::iterator Database::end() const
	{
		return iterator(con, lastTables, true);
	}
	
}
}