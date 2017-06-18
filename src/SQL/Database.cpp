#include <QUtils/SQL/Database.h>
#include <QUtils/SQL/Table.h>
#include <QUtils/SQL/Connection.h>
#include <QUtils/SQL/Query.h>

namespace Util
{
namespace SQL
{
	Database::Database(Connection* con) : con(con)
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
		throw SQLErrorException().Msg("Table '" + table + "' not present in database");
	}
	
}
}