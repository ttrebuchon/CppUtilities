#include <QUtils/SQL/SQLSystem.h>
#include <QUtils/SQL/SQLSystem.hpp>
#include <QUtils/SQL/ORM/SQLModel.h>
#include <QUtils/SQL/ORM/SQLModel.hpp>

#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/GUID/GUID.h>

namespace QUtils
{
namespace SQL
{
	namespace DefaultModels
	{
		struct GUIDModel
		{
			
			 const std::function<std::string(QUtils::GUID)> toSQL = [](QUtils::GUID obj)
			{
				return to_string(obj);
			};
			
			const std::function<QUtils::GUID(std::string)> fromSQL =
			[](std::string val) -> QUtils::GUID
			{
				return GUID::FromString(val);
			};
		};
	}
	
	void SQLSystem::initDefaultModels()
	{
		#ifdef QUTILS_GUID_ENABLED
		DefaultModels::GUIDModel guidModel;
		this->primitiveType<QUtils::GUID, std::string>(guidModel.toSQL, guidModel.fromSQL);
		#endif
		
		this->primitiveType<unsigned int, long>();
		this->primitiveType<unsigned long, long long>();
	}
	
}
}