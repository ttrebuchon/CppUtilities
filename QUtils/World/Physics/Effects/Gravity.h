#pragma once

#include "../Force.h"
#include "../System.h"


namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class Gravity : public Force<Num>
	{
		private:
		constexpr static Num G = 6.67408*pow(10, -11);
		
		protected:
		BASE_USINGS(Num)
		Num _scale;
		
		
		Vector_t calc(const Particle_t& p1, const Particle_t& p2) const
		{
			const auto r = p2.position() - p1.position();
			return _scale*p1.mass()*p2.mass()*r / pow(r.value(), 3);
		}
		
		public:
		
		Gravity(const Num s) : _scale(s)
		{}
		
		virtual Vector_t eval(const Particle_t& p, const System_t& sys) const override
		{
			Vector_t sum;
			for (auto part : sys.particles)
			{
				if (part.get() == &p)
				{
					continue;
				}
				sum += calc(p, *part);
			}
			return G*sum;
		}
		
	};
	
}
}
}