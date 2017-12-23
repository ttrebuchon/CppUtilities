#pragma once

#include "../Vector.h"

namespace QUtils { namespace World {
	
	
	template <class T>
	class Map
	{
		private:
		
		protected:
		
		public:
		typedef Vector<T> Vec_t;
		
		
		virtual bool hits(const Vec_t& bsse, const Vec_t& dir, Vec_t* result) const = 0;
		
		virtual T slant(const Vec_t& pos, const Vec_t& dir) const = 0;
	};
}
}