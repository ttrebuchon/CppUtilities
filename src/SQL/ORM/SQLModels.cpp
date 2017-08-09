#include <QUtils/SQL/ORM/SQLModels.h>
#include <QUtils/SQL/SQLSystem.h>

namespace QUtils
{
namespace SQL
{
	void SQLModels::build(SQLSystem* sys)
	{
		for (auto pair : models)
		{
			pair.second->create(this);
		}
	}
}
}