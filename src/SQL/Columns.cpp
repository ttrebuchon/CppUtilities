#include <QUtils/SQL/Columns.h>
#include <string>


namespace QUtils
{
namespace SQL
{
	const Column& Columns::operator[](const std::string columnName) const
	{
		return *(columnsByName.at(columnName));
	}
	
	
	typedef Columns::iterator iterator;
	
	iterator Columns::begin() const
	{
		return columns.begin();
	}
	
	iterator Columns::end() const
	{
		return columns.end();
	}
}
}