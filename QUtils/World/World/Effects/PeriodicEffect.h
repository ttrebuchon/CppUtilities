#pragma once

#include "../Effect.h"
#include "../Time.h"

namespace QUtils { namespace World {
namespace Effects {
	
	class PeriodicEffect : public Effect
	{
		public:
		WORLD_OBJECT(PeriodicEffect)
		
		private:
		
		protected:
		Duration _period;
		Time lastActivated;
		bool lastActSet;
		EventHandler<std::shared_ptr<Entity>, bool&> periodicEffect;
		
		
		PeriodicEffect(World_t*, const Duration period);
		
		public:
		
		virtual ~PeriodicEffect() = default;
		
		inline const Duration& period() const
		{ return _period; }
		
	};
	
	
}
}
}