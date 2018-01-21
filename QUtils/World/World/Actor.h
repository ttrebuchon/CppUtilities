#pragma once

#include "Entity.h"


namespace QUtils { namespace World {
	
	class Actor : public Entity
	{
		public:
		WORLD_OBJECT(Actor)
		
		
		private:
		
		protected:
		Actor(World_t*, const Vec_t);
		Actor(World_t*);
		
		public:
		
		
	};
}
}