#pragma once
#include "Base.h"
#include <list>
#include <map>
#include "Particle.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class System : public Base<Num>
	{
		public:
		
		
		private:
		
		protected:
		BASE_USINGS(Num)
		
		
		
		public:
		std::list<typename Particle_t::Ptr> particles;
		std::shared_ptr<Environment_t> env;
		unsigned long long ticks;
		Num timescale = 1;
		std::map<typename Particle_t::Ptr, Vector_t> forces;
		
		System() : particles(), env(), ticks(0), timescale(1), forces()
		{}
		
		virtual void step();
	};
	
}
}
}
#include "System.hpp"