#pragma once

#include "WorldObject.h"


namespace QUtils { namespace World {
	
	class Actor : public WorldObject
	{
		private:
		
		protected:
		
		public:
		typedef std::shared_ptr<Actor> Ptr;
	};
}
}