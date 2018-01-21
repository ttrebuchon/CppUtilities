#pragma once

#include "WorldObject.h"
#include "Map.h"
#include "Entity.h"
//#include "Collections/ReadableCollection.h"


namespace QUtils { namespace World {
	
	class Instance : public WorldObject
	{
		private:
		
		protected:
		std::list<Entity::Ptr> _entities;
		
		Instance(World_t* world, Map<double>::Ptr map);
		
		public:
		WORLD_OBJECT(Instance)
		Map<double>::Ptr map;
		const std::list<Entity::Ptr>& entities;
		
		void addEntity(const Entity::Ptr);
		
	};
}
}