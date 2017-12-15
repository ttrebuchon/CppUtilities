#pragma once
#include "Base.h"
#include "Force.h"
#include <list>

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class Environment : public Base<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		
		public:
		std::list<typename Force_t::Ptr> forces;
		std::list<typename Field_t::Ptr> fields;
		Num gravity;
		
		
	};
	
}
}
}