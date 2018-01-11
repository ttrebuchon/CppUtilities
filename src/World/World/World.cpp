#include <QUtils/World/World/World.h>
#include <QUtils/World/World/WorldObject.h>

#include <QUtils/Exception/NotImplemented.h>
#include <mutex>

namespace QUtils { namespace World {
	
	World_t::World_t() : objects_m(), objects(), _clock(), clock(_clock)
	{
		
	}
	
	void World_t::registerObject(WorldObject* obj)
	{
		std::lock_guard<std::shared_timed_mutex> lock(objects_m);
		objects[obj->id()] = obj->shared_from_this();
	}
	
	
	WorldClock::duration World_t::go(WorldClock::duration length)
	{
		auto start = clock.now();
		
		
		if (length.count() < 0)
		{
			length = WorldClock::duration(INT_MAX);
		}
		
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
	
	std::future<WorldClock::duration> World_t::goAsync(WorldClock::duration length)
	{
		return std::async(std::launch::async,
		[&, length]()
		{
			return this->go(length);
		});
	}
}
}