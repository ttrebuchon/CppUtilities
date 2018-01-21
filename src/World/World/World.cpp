#include <QUtils/World/World/World.h>
#include <QUtils/World/World/WorldObject.h>
#include <QUtils/World/World/Instance.h>

#include <QUtils/Exception/NotImplemented.h>
#include <mutex>
#include <QUtils/Debug/dassert.h>

namespace QUtils { namespace World {
	
	World_t::World_t() : objects_m(), instances_m(), objects(), _clock(), clock(_clock)
	{
		
	}
	
	void World_t::registerObject(WorldObject* obj)
	{
		WorldObject::Ptr ptr;
		
		{
			FullLock_t lock(objects_m);
			ptr = objects[obj->id()] = obj->shared_from_this();
		}
		
		dassert(ptr != nullptr);
		
		if (ptr->type == WorldType::Instance)
		{
			FullLock_t lock(instances_m);
			instances.push_back(std::dynamic_pointer_cast<Instance>(ptr));
			dassert(instances.back() != nullptr);
		}
	}
	
	
	WorldClock::duration World_t::go(WorldClock::duration length)
	{
		auto start = clock.now();
		
		
		if (length.count() < 0)
		{
			length = WorldClock::max() - clock.now();
			//length = WorldClock::duration(INT_MAX);
		}
		
		try
		{
			std::list<std::future<void>> tasks;
			WorldClock::time_point lastTick;
			resumed();
			while (clock.now() - start < length)
			{
				lastTick = clock.now();
				tickStarting();
				_clock.advance(100);
				{
					ReadLock_t inst_lock(instances_m);
					for (auto inst : instances)
					{
						tasks.push_back(std::async(std::launch::async, &World_t::runInstance, this, inst));
					}
				}
				//throw NotImp();
				for (auto& task : tasks)
				{
					task.get();
				}
				tasks.clear();
				tickEnding(lastTick, clock.now());
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
	
	void World_t::runInstance(Instance::Ptr inst)
	{
		bool remove;
		for (auto ent : inst->entities)
		{
			for (auto effect : ent->effects)
			{
				effect->apply(ent, remove);
			}
		}
	}
}
}