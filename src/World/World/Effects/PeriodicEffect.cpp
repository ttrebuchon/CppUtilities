#include <QUtils/World/World/Effects/PeriodicEffect.h>
#include <QUtils/World/World/World.h>
#include <iostream>

namespace QUtils { namespace World {
namespace Effects {
	
	PeriodicEffect::PeriodicEffect(World_t* world, const Duration period) : Effect(world), _period(period), lastActivated(), lastActSet(false), periodicEffect()
	{
		this->effect += [&](auto ent, auto& remove)
		{
			if (!this->lastActSet)
			{
				this->lastActSet = true;
				lastActivated = this->time().start;
			}
			
			while (this->world->clock.now() - this->lastActivated >= this->period())
			{
				this->periodicEffect(ent, remove);
				this->lastActivated += this->period();
			}
		};
	}
	
	
	
	
}
}
}