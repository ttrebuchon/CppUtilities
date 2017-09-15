#include <QUtils/SQL/SQLQuery.h>

namespace QUtils
{
namespace SQL
{
	SQLQuery::~SQLQuery()
	{
		
	}
	
	
	template <> 
	double SQLQuery::column<double>(int index) const
	{
		return columnDouble(index);
	}
	
	template <> 
	int SQLQuery::column<int>(int index) const
	{
		return columnInt(index);
	}
	
	template <> 
	long SQLQuery::column<long>(int index) const
	{
		return columnLong(index);
	}
	
	template <> 
	long long SQLQuery::column<long long>(int index) const
	{
		return columnLongLong(index);
	}
	
	template <> 
	std::string SQLQuery::column<std::string>(int index) const
	{
		return columnString(index);
	}
	
	
}
}