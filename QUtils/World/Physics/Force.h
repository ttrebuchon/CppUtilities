#pragma once
#include "../Vector.h"
#include "Particle.h"
#include <memory>

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class Force : public Base<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		public:
		typedef std::shared_ptr<typename Base<Num>::Force_t> Ptr;
		typedef std::shared_ptr<const typename Base<Num>::Force_t> CPtr;
		
		
		
		virtual Vector_t eval(const Particle_t&, const System_t&) const = 0;
	};
	
}
}
}