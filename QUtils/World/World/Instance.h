#pragma once

#include "WorldObject.h"
#include "Map.h"


namespace QUtils { namespace World {
	
	class Instance : public WorldObject
	{
		private:
		
		protected:
		
		Instance(World_t* world, Map<float>::Ptr map) : WorldObject(world), map(map)
		{
			
		}
		
		public:
		WORLD_OBJECT(Instance)
		Map<float>::Ptr map;
		
		
	};
}
}