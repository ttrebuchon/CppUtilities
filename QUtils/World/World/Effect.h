#pragma once
#include "WorldObject.h"
#include "Time.h"
#include <QUtils/Events.h>

namespace QUtils { namespace World {
	
	class Entity;
	
	class Effect : public WorldObject
	{
		protected:
		Effect(World_t*);
		
		EventHandler<std::shared_ptr<Entity>, bool&> effect;
		
		public:
		WORLD_OBJECT(Effect)
		EventHandler_Noexcept<> applying;
		EventHandler_Noexcept<> applied;
		
		virtual ~Effect();
		
		virtual Timespan time() const = 0;
		
		void apply(std::shared_ptr<Entity>, bool& remove);
		
		
	};
}
}