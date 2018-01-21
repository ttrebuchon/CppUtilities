#include <QUtils/World/World/Instance.h>


namespace QUtils { namespace World {
	
	Instance::Instance(World_t* world, Map<double>::Ptr map) : WorldObject(world), _entities(), map(map), entities(_entities)
	{
		this->_type = WorldType::Instance;
	}
	
	void Instance::addEntity(const Entity::Ptr ent)
	{
		_entities.push_back(ent);
	}
		
}
}