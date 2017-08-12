#include <QUtils/SQL/ORM/SQLModels.h>
#include <QUtils/SQL/ORM/SQLModel.h>
#include <QUtils/SQL/SQLSystem.h>
#include <QUtils/SQL/ORM/SQLPrimitiveModel.h>
#include <QUtils/SQL/Errors.h>

#include <QUtils/Exception/NotImplemented.h>


namespace QUtils
{
namespace SQL
{
	void SQLModels::build(SQLSystem* sys)
	{
		for (auto pair : models)
		{
			pair.second->initModel(this);
		}
		
		throw NotImp();
	}
	
	ValueType SQLModels::getSQLType(std::type_index tIndex)
	{
		if (primitiveModels.count(tIndex) > 0)
		{
			return primitiveModels.at(tIndex)->dbType();
		}
		
		if (models.count(tIndex) > 0)
		{
			if (models.at(tIndex)->idType == Null)
			{
				models.at(tIndex)->initModel(this);
			}
			return models.at(tIndex)->idType;
		}
		
		throw SQLModelConfigException().Function(__func__).Msg(std::string("Could not find ValueType for ") + tIndex.name());
	}
}
}