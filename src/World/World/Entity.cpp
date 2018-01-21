#include <QUtils/World/World/Entity.h>
#include <iostream>

namespace QUtils { namespace World {
	
	Entity::Entity(World_t* world, const Vec_t pos) : WorldObject(world), _pos(pos), effects()
	{
		
	}
	
	Entity::Entity(World_t* world) : Entity(world, Vec_t(0,0,0))
	{
		
	}
	
	Entity::~Entity()
	{
		
	}
}
}