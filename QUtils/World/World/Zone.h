#pragma once

#include "WorldObject.h"

namespace QUtils { namespace World {
	
	template <class>
	class Map;
	
	class Zone : public WorldObject
	{
		public:
		WORLD_OBJECT(Zone)
		
		
		private:
		
		protected:
		Vec_t absOrigin;
		Vec_t dimensions;
		std::shared_ptr<Map<double>> map;
		
		public:
		
		void relativeCoords(Vec_t& absolute) const
		{
			absolute -= absOrigin;
		}
		
	};
}
}