#pragma once

#include "../Vector.h"
#include "Base.h"
#include <memory>
#include <map>

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class Particle : public Base<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		public:
		typedef std::shared_ptr<typename Base<Num>::Particle_t> Ptr;
		typedef std::shared_ptr<const typename Base<Num>::Particle_t> CPtr;
		
		std::map<std::string, Vector_t> properties;
		
		
		virtual Vector_t position() const = 0;
		virtual Vector_t velocity() const = 0;
		virtual void position(const Vector_t) = 0;
		virtual void velocity(const Vector_t) = 0;
		virtual Num mass() const = 0;
		
	};
	
}
}
}