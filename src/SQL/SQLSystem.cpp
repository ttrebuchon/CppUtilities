#include <QUtils/SQL/SQLSystem.h>
#include <QUtils/SQL/SQLConnection.h>
#include <QUtils/SQL/ORM/SQLModels.h>

namespace QUtils
{
namespace SQL
{
	SQLSystem::SQLSystem(SQLConnection* _con) : con(_con), models(new SQLModels()), connection(con)
	{
		
	}
	
	
	
	std::shared_ptr<SQLSystem> SQLSystem::Create(SQLConnection* con)
	{
		return std::make_shared<SQLSystem>(con);
	}
	
	
	void SQLSystem::buildModels()
	{
		models->build(this);
	}
}
}