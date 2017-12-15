#pragma once

#include "System.h"
#include "Effects/Gravity.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	void System<Num>::step()
	{
		forces.clear();
		
		for (auto part : particles)
		{
			forces[part] = Vector_t(0, 0, 0);
			for (auto force : env->forces)
			{
				forces[part] += force->eval(*part, *this);
			}
		}
		
		
		if (env->gravity != 0)
		{
			Gravity<Num> gravity(env->gravity);
			for (auto part : particles)
			{
				forces[part] += gravity.eval(*part, *this);
			}
		}
		
		
		for (auto part : particles)
		{
			auto accel = forces[part]/part->mass();
			part->position(part->position() + part->velocity()*timescale + accel*0.5*timescale);
			part->velocity(part->velocity() + accel*timescale);
		}
		++ticks;
	}
	
}
}
}