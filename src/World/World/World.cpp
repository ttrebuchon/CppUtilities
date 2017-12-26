#include <QUtils/World/World/World.h>
#include <QUtils/World/World/WorldObject.h>

namespace QUtils { namespace World {
	
	void World_t::registerObject(WorldObject* obj)
	{
		objects[obj->id()] = obj->shared_from_this();
	}
}
}