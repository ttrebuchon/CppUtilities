#include <QUtils/SQL/ValueType.h>

namespace QUtils
{
namespace SQL
{
	template <>
	constexpr bool SQL_Primitive<std::string>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<int>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<long>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<double>()
	{
		return true;
	}
	
	
}
}