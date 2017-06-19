#include <QUtils/SQL/Query.h>

namespace Util
{
namespace SQL
{
	Query::~Query()
	{
		
	}
	
	
	template <> 
	double Query::column<double>(int index) const
	{
		return columnDouble(index);
	}
	
	template <> 
	int Query::column<int>(int index) const
	{
		return columnInt(index);
	}
	
	template <> 
	long Query::column<long>(int index) const
	{
		return columnLong(index);
	}
	
	template <> 
	std::string Query::column<std::string>(int index) const
	{
		return columnString(index);
	}
	
	
	
	
	
	
}
}