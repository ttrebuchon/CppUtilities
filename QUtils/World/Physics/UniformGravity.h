#pragma once
#include "UniformForce.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class UniformGravity : public UniformForce<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		public:
		
		UniformGravity(const Vector_t f) : UniformForce<Num>(f)
		{}
		
		virtual Vector_t eval(const Particle_t& p, const System_t&) const override
		{
			return this->force*p.mass();
		}
	};
	
}
}
}