#include <QUtils/World/World/Actor.h>



namespace QUtils { namespace World {
	
	Actor::Actor(World_t* world, const Vec_t pos) : Entity(world, pos)
	{
		
	}
	
	Actor::Actor(World_t* world) : Entity(world)
	{
		
	}
}
}