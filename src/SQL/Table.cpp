#include <QUtils/SQL/Table.h>
#include <QUtils/SQL/Connection.h>
#include <QUtils/SQL/Column.h>

namespace Util
{
namespace SQL
{
	Table::Table(Connection* con, std::string name) : con(con), _columns(), name(name)
	{
		auto info = con->tableColumns(name);
		for (auto col : info)
		{
			_columns.push_back(std::make_shared<Column>(std::get<0>(col), std::get<1>(col), std::get<2>(col), std::get<3>(col), std::get<4>(col), std::get<5>(col)));
		}
		
	}
	
	
	
}
}