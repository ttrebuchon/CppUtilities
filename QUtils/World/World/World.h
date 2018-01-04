#pragma once
#include <QUtils/GUID.h>
#include <memory>
#include <unordered_map>
#include <map>
#include "WorldObject.h"
#include <QUtils/Events.h>
#include "Time.h"

namespace QUtils { namespace World {
	
	class WorldObject;
	
	class World_t
	{
		private:
		
		
		protected:
		std::unordered_map<GUID, WorldObject::Ptr> objects;
		WorldClock _clock;
		
		
		void registerObject(WorldObject*);
		
		public:
		typedef std::shared_ptr<World_t> Ptr;
		typedef WorldClock::rep Tick_t;
		const WorldClock& clock;
		EventHandler_Noexcept<> paused;
		EventHandler_Noexcept<> resumed;
		
		World_t();
		
		WorldClock::duration go(const WorldClock::duration = WorldClock::duration(-1));
		
		
		friend class WorldObject;
	};
	
	
}
}