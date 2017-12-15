#pragma once

namespace QUtils { namespace World {
	
	template <class Num>
	struct Vector;
	
namespace Physics {
	
	template <class Num>
	class Particle;
	
	template <class Num>
	class System;
	
	template <class Num>
	class Environment;
	
	template <class Num>
	class Force;
	
	template <class Num>
	class Field;
	
	
	
	
	template <class Num>
	class Base
	{
		protected:
		typedef Particle<Num> Particle_t;
		typedef System<Num> System_t;
		typedef Environment<Num> Environment_t;
		typedef Force<Num> Force_t;
		typedef World::Vector<Num> Vector_t;
		typedef Field<Num> Field_t;
	};
	
	#define BASE_USINGS(Num) \
	typedef typename Base<Num>::Particle_t Particle_t; \
	typedef typename Base<Num>::System_t System_t; \
	typedef typename Base<Num>::Environment_t Environment_t; \
	typedef typename Base<Num>::Force_t Force_t; \
	typedef typename Base<Num>::Vector_t Vector_t; \
	typedef typename Base<Num>::Field_t Field_t;
	
}
}
}