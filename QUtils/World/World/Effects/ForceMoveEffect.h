#pragma once

#include "PeriodicEffect.h"
#include "../../Vector.h"

namespace QUtils { namespace World {
namespace Effects {
	
	class ForceMove : public PeriodicEffect
	{
		public:
		WORLD_OBJECT(ForceMove)
		
		private:
		
		protected:
		Vec_t velocity;
		Timespan when;
		
		
		ForceMove(World_t*, const Vec_t vel, const Duration period, const Time end);
		
		
		public:
		
		virtual ~ForceMove() = default;
		
		virtual Timespan time() const;
		
	};
	
	
}
}
}