#pragma once

#include "../Force.h"
#include "../System.h"


namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class MagneticFieldForce : public Force<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		
		Vector_t calc(const Particle_t& p1, typename Field_t::CPtr field, const Num t) const
		{
			return p1.velocity().cross(field->at(p1.position(), t));
		}
		
		public:
		
		virtual Vector_t eval(const Particle_t& p, const System_t& sys) const override
		{
			if (p.properties.count("charge") <= 0)
			{
				return {0, 0, 0};
			}
			Vector_t sum;
			for (auto ptr : sys.env->fields)
			{
				if (ptr->kind() == "magnetic")
				{
					sum += calc(p, ptr, sys.ticks*sys.timescale);
				}
			}
			
			return sum*(p.properties.at("charge").value());
		}
		
	};
	
}
}
}