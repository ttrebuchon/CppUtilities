#pragma once
#include <QUtils/GUID.h>
#include <memory>
#include <unordered_map>
#include <map>
#include "WorldObject.h"

namespace QUtils { namespace World {
	
	class WorldObject;
	
	class World_t
	{
		private:
		
		
		protected:
		std::unordered_map<GUID, WorldObject::Ptr> objects;
		
		
		void registerObject(WorldObject*);
		
		public:
		typedef std::shared_ptr<World_t> Ptr;
		
		
		friend class WorldObject;
	};
	
	
}
}