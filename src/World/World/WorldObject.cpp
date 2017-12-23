#include <QUtils/World/World/WorldObject.h>
#include <QUtils/World/World/World.h>


namespace QUtils { namespace World {
	
	
	
	WorldObject::WorldObject(World_t* world, const GUID id) : world(world), objID(id)
	{
		world->registerObject(this);
	}
	
	WorldObject::WorldObject(World_t* world) : world(world), objID(GUID::Create())
	{
		world->registerObject(this);
	}
}
}