#include <QUtils/SQL/SQLObjects.h>
#include <QUtils/SQL/SQLDatabase.h>
#include <QUtils/SQL/SQLTable.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/SQLQuery.h>

namespace QUtils
{
namespace SQL
{
	
	
namespace Internal
{
	SQLDatabase_Obj::SQLDatabase_Obj(SQLConnection* connection, const std::string name) : SQLObject(connection), name(name), lastTables(NULL)
	{
		
	}
	
	SQLDatabase_Obj::SQLDatabase_Obj(SQLConnection* con) : SQLDatabase_Obj(con, con->getDefaultDBName())
	{
		
	}
	
	
	std::shared_ptr<SQLDatabase_Obj> SQLDatabase_Obj::Create(SQLConnection* connection, const std::string name)
	{
		return std::shared_ptr<SQLDatabase_Obj>(new SQLDatabase_Obj(connection, name));
	}






	
	SQLTable SQLDatabase_Obj::operator[](std::string table) const
	{
		SQLQuery* tables = connection->tablesQuery();
		while ((*tables)())
		{
			if (tables->column<std::string>(0) == table)
			{
				delete tables;
				return SQLTable::Create(SQLDatabase(((SQLDatabase_Obj*)this)->shared_from_this()), "[" + table + "]");
			}
			tables->next();
		}
		delete tables;
		throw SQLErrorException().Msg("SQLTable [" + table + "] not present in database");
	}
	
	
	/*SQLDatabase& SQLDatabase_Obj::operator=(const SQLDatabase& db)
	{
		SQLObject::operator=(db);
		behind = db.behind;
		_name = db._name;
		
		return *this;
	}*/
	
	
	
	
	
	
	
	
	/*
	SQLDatabase_Obj::iterator::iterator(SQLDatabase_Obj& db, std::shared_ptr<std::vector<std::string>> names, bool end) : SQLObject(db.connection), vIt(), names(names), behind(db.behind)
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
	
	SQLDatabase::iterator::iterator(std::shared_ptr<Internal::SQLDatabase_Obj> behind, std::shared_ptr<std::vector<std::string>> names, bool end) : SQLObject(behind->connection), vIt(), names(names), behind(behind)
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
	
	
	
	SQLTable SQLDatabase_Obj::iterator::operator*() const
	{
		return SQLTable::Create(SQLDatabase(this), "[" + *vIt + "]");
	}
	
	typename SQLDatabase::iterator SQLDatabase::iterator::operator++()
	{
		iterator it(behind, names);
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
		behind->lastTables = std::make_shared<std::vector<std::string>>();
		SQLQuery* q = connection->tablesQuery();
		
		while (q->next())
		{
			behind->lastTables->push_back(q->column<std::string>(0));
		}
		delete q;
		
		return iterator(*this, behind->lastTables);
	}
	
	typename SQLDatabase::iterator SQLDatabase::end()
	{
		return iterator(*this, behind->lastTables, true);
	}*/
	
}
}
}