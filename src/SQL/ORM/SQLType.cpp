#include <QUtils/SQL/ORM/SQLType.h>


namespace QUtils
{
namespace SQL
{
	std::shared_ptr<SQLType> SQLType::Create(const std::string val)
	{
		return std::make_shared<SQLTextType>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const long val)
	{
		return std::make_shared<SQLIntegerType>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const long long val)
	{
		return std::make_shared<SQLInteger64Type>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const double val)
	{
		return std::make_shared<SQLDoubleType>(val);
	}
}
}