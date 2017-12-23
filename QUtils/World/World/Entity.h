#pragma once


#include "WorldObject.h"

namespace QUtils { namespace World {
	
	class Entity : public WorldObject
	{
		private:
		
		protected:
		
		public:
		typedef std::shared_ptr<Entity> Ptr;
		
	};
}
}