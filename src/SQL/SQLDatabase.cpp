#include <QUtils/SQL/SQLDatabase.h>
#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLQuery.h>

namespace QUtils
{
namespace SQL
{
	SQLDatabase::SQLDatabase(SQLConnection* con) : lastTables(NULL), con(con)
	{
		
	}
	
	
	SQLTable SQLDatabase::operator[](std::string table) const
	{
		SQLQuery* tables = con->tablesQuery();
		while ((*tables)())
		{
			if (tables->column<std::string>(0) == table)
			{
				delete tables;
				return SQLTable(con, table);
			}
			tables->next();
		}
		delete tables;
		throw SQLErrorException().Msg("SQLTable [" + table + "] not present in database");
	}
	
	
	
	
	
	
	
	
	
	SQLDatabase::iterator::iterator(SQLConnection* con, std::shared_ptr<std::vector<std::string>> names, bool end) : vIt(), names(names), con(con)
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
	
	
	
	SQLTable SQLDatabase::iterator::operator*() const
	{
		return SQLTable(con, *vIt);
	}
	
	typename SQLDatabase::iterator SQLDatabase::iterator::operator++()
	{
		iterator it(con, names);
		it.vIt = this->vIt;
		vIt++;
		return it;
	}
	
	bool SQLDatabase::iterator::operator==(const iterator it) const
	{
		return (vIt == it.vIt);
	}
	
	bool SQLDatabase::iterator::operator!=(const iterator it) const
	{
		return !(operator==(it));
	}
	
	typename SQLDatabase::iterator SQLDatabase::begin()
	{
		lastTables = std::make_shared<std::vector<std::string>>();
		SQLQuery* q = con->tablesQuery();
		
		while (q->next())
		{
			lastTables->push_back(q->column<std::string>(0));
		}
		delete q;
		
		return iterator(con, lastTables);
	}
	
	typename SQLDatabase::iterator SQLDatabase::end() const
	{
		return iterator(con, lastTables, true);
	}
	
}
}