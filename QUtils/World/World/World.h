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
	
	class World_t
	{
		private:
		
		
		protected:
		std::shared_timed_mutex objects_m;
		std::unordered_map<GUID, WorldObject::Ptr> objects;
		WorldClock _clock;
		
		
		void registerObject(WorldObject*);
		
		public:
		typedef WorldClock::rep Tick_t;
		
		
		const WorldClock& clock;
		EventHandler_Noexcept<> paused;
		EventHandler_Noexcept<> resumed;
		
		World_t();
		
		WorldClock::duration go(WorldClock::duration = WorldClock::duration(-1));
		
		std::future<WorldClock::duration> goAsync(WorldClock::duration = WorldClock::duration(-1));
		
		
		friend class WorldObject;
	};
	
	
}
}