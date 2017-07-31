#include <QUtils/SQL/SQLColumns.h>
#include <string>


namespace QUtils
{
namespace SQL
{
	const SQLColumn& SQLColumns::operator[](const std::string columnName) const
	{
		return *(columnsByName.at(columnName));
	}
	
	
	typedef SQLColumns::iterator iterator;
	
	iterator SQLColumns::begin() const
	{
		return columns.begin();
	}
	
	iterator SQLColumns::end() const
	{
		return columns.end();
	}
}
}