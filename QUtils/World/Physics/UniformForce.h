#pragma once
#include "Force.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class UniformForce : public Force<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		public:
		Vector_t force;
		
		UniformForce(const Vector_t f) : force(f)
		{}
		
		virtual Vector_t eval(const Particle_t&, const System_t&) const override
		{
			return force;
		}
	};
	
}
}
}