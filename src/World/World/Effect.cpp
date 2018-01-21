#include <QUtils/World/World/Effect.h>
#include <QUtils/World/World/Entity.h>

namespace QUtils { namespace World {
	
	Effect::Effect(World_t* world) : WorldObject(world), effect(), applying(), applied()
	{
		
	}
	
	Effect::~Effect()
	{
		
	}
	
	void Effect::apply(Entity::Ptr ent, bool& remove)
	{
		applying();
		effect(ent, remove);
		applied();
	}
}
}