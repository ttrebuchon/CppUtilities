#pragma once

#include "WorldObject.h"
#include "Effect.h"
#include "Collections/EffectSet.h"

namespace QUtils { namespace World {
	
	class Entity : public WorldObject
	{
		public:
		WORLD_OBJECT(Entity)
		
		private:
		
		protected:
		Entity(World_t*, const Vec_t);
		Entity(World_t*);
		Vec_t _pos;
		
		public:
		EffectSet effects;
		
		inline Vec_t pos() const
		{ return _pos; }
		
		inline void setPos(const Vec_t p)
		{ _pos = p; }
		
		virtual ~Entity();
		
	};
}
}