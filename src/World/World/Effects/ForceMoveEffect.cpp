#include <QUtils/World/World/Effects/ForceMoveEffect.h>
#include <QUtils/World/World/World.h>
#include <QUtils/World/World/Entity.h>


namespace QUtils { namespace World {
namespace Effects {
	
	ForceMove::ForceMove(World_t* world, const Vec_t vel, const Duration period, const Time end) : PeriodicEffect(world, period), velocity(vel), when(world->clock.now(), end)
	{
		this->periodicEffect += [this](auto ent, auto& remove)
		{
			const auto delta = this->world->clock.now() - lastActivated;
			ent->setPos(ent->pos() + (delta.count())/static_cast<double>(_period.count())*velocity);
			remove = false;
		};
	}
	
	Timespan ForceMove::time() const
	{
		return when;
	}
}
}
}