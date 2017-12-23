#pragma once
#include <QUtils/GUID.h>
#include <memory>

namespace QUtils { namespace World {
	
	class World_t;
	
	class WorldObject
	{
		private:
		
		protected:
		World_t* world;
		GUID objID;
		WorldObject(World_t*, const GUID);
		WorldObject(World_t*);
		
		
		public:
		typedef std::shared_ptr<WorldObject> Ptr;
		
		inline const GUID& id() const
		{ return objID; }
		
		
		friend class World_t;
	};
}
}