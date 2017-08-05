#include <QUtils/SQL/SQLRow.h>
#include <QUtils/SQL/SQLQuery.h>

namespace QUtils
{
namespace SQL
{
namespace Internal
{
	SQLRow_Obj::SQLRow_Obj(std::shared_ptr<SQLQuery> query, const std::string table, SQLRID rid) : _rowid(rid), _pkIndex(-1), pkValue(), rowQuery(query), rowid(_rowid), pkIndex(_pkIndex), table(table)
	{
		
	}
	
	SQLRow_Obj::~SQLRow_Obj()
	{
		
	}
	
	
	
	
	
	std::string SQLRow_Obj::operator[](const size_t col)
	{
		return rowQuery->column<std::string>(col);
	}
}
}
}