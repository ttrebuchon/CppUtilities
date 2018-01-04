#include <QUtils/World/World/World.h>
#include <QUtils/World/World/WorldObject.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace World {
	
	World_t::World_t() : objects(), _clock(), clock(_clock)
	{
		
	}
	
	void World_t::registerObject(WorldObject* obj)
	{
		objects[obj->id()] = obj->shared_from_this();
	}
	
	
	WorldClock::duration World_t::go(const WorldClock::duration length)
	{
		auto start = clock.now();
		
		
		/*if (count < 0)
		{
			
		}*/
		
		try
		{
			resumed();
			while (clock.now() - start < length)
			{
				//throw NotImp();
				_clock.advance();
			}
		}
		catch (...)
		{
			paused();
			throw;
		}
		paused();
		
		return clock.now() - start;
	}
}
}