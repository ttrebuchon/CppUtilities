#pragma once

#include "WorldObject.h"
#include "Effect.h"
#include "Collections/EffectSet.h"

namespace QUtils { namespace World {
	
	class Entity : public WorldObject
	{
		private:
		
		protected:
		Entity(World_t* world) : WorldObject(world), effects()
		{}
		
		public:
		WORLD_OBJECT(Entity)
		EffectSet effects;
		
		virtual ~Entity();
		
	};
}
}