#include <QUtils/SQL/SQLSystem.h>


#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace SQL
{
	
	
	SQLSystem::SQLSystem(SQLConnection* _con, bool withDefaultModels) : con(_con), models(new SQLModels()), connection(con)
	{
		if (withDefaultModels)
		{
			initDefaultModels();
		}
	}
	
	
	
	std::shared_ptr<SQLSystem> SQLSystem::Create(SQLConnection* con, bool withDefaultModels)
	{
		return std::make_shared<SQLSystem>(con, withDefaultModels);
	}
	
	
	void SQLSystem::buildModels(bool dropIfConflict)
	{
		models->build(this);
		throw NotImp();
	}
}
}