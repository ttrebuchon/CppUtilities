#pragma once

#include "Particle.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class StandardParticle : public Particle<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		
		public:
		Vector_t pos;
		Vector_t vel;
		Num _mass;
		
		virtual Vector_t position() const override { return pos; }
		virtual Vector_t velocity() const override { return vel; }
		virtual void position(const Vector_t v) override { pos = v; }
		virtual void velocity(const Vector_t v) override { vel = v; }
		virtual Num mass() const override { return _mass; }
		
	};
	
}
}
}