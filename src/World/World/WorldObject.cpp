#include <QUtils/World/World/WorldObject.h>
#include <QUtils/World/World/World.h>


namespace QUtils { namespace World {
	
	void WorldObject::registerObj()
	{
		world->registerObject(this);
	}
	
	WorldObject::WorldObject(World_t* world, const GUID id) : world(world), objID(id), _type(WorldType::Other), type(_type)
	{
		
	}
	
	WorldObject::WorldObject(World_t* world) : world(world), objID(GUID::Create()), _type(WorldType::Other), type(_type)
	{
		
	}
}
}