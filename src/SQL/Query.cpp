#include <QUtils/SQL/Query.h>


namespace Util
{
namespace SQL
{
	Query::~Query()
	{
		
	}
	
	
	template <> 
	double Query::column<double>(int index)
	{
		return columnDouble(index);
	}
	
	template <> 
	int Query::column<int>(int index)
	{
		return columnInt(index);
	}
	
	template <> 
	long Query::column<long>(int index)
	{
		return columnLong(index);
	}
	
	template <> 
	std::string Query::column<std::string>(int index)
	{
		return columnString(index);
	}
}
}