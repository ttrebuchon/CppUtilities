#pragma once
#include <QUtils/GUID.h>
#include <memory>
#include <unordered_map>
#include <map>
#include "WorldObject.h"
#include <QUtils/Events.h>
#include "Time.h"
#include <future>
#include <shared_mutex>

namespace QUtils { namespace World {
	
	class WorldObject;
	class Instance;
	
	class World_t
	{
		private:
		
		
		protected:
		
		typedef std::shared_timed_mutex Shared_m;
		typedef std::lock_guard<Shared_m> FullLock_t;
		typedef std::shared_lock<Shared_m> ReadLock_t;
		
		mutable Shared_m objects_m;
		mutable Shared_m instances_m;
		std::unordered_map<GUID, WorldObject::Ptr> objects;
		WorldClock _clock;
		std::vector<std::shared_ptr<Instance>> instances;
		
		
		void registerObject(WorldObject*);
		void runInstance(std::shared_ptr<Instance>);
		
		public:
		typedef WorldClock::rep Tick_t;
		
		
		const WorldClock& clock;
		EventHandler_Noexcept<> paused;
		EventHandler_Noexcept<> resumed;
		EventHandler_Noexcept<> tickStarting;
		EventHandler_Noexcept<WorldClock::time_point, WorldClock::time_point> tickEnding;
		
		World_t();
		
		WorldClock::duration go(WorldClock::duration = WorldClock::duration(-1));
		
		std::future<WorldClock::duration> goAsync(WorldClock::duration = WorldClock::duration(-1));
		
		
		friend class WorldObject;
	};
	
	
}
}