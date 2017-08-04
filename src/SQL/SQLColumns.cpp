#include <QUtils/SQL/SQLColumns.h>
#include <QUtils/SQL/Errors.h>
#include <string>


namespace QUtils
{
namespace SQL
{
	const SQLColumn& SQLColumns::operator[](const std::string columnName) const
	{
		try
		{
		return *(columnsByName->at(columnName));
		}
		catch (...)
		{
			throw SQLErrorException(std::current_exception()).Function(__func__).Msg("column: \"" + columnName + "\"");
		}
	}
	
	SQLColumns& SQLColumns::operator=(const SQLColumns& cols)
	{
		columns = cols.columns;
		columnsByName = cols.columnsByName;
		return *this;
	}
	
	
	typedef SQLColumns::iterator iterator;
	
	iterator SQLColumns::begin() const
	{
		return columns->begin();
	}
	
	iterator SQLColumns::end() const
	{
		return columns->end();
	}
}
}