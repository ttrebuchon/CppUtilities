#pragma once
#include "Field.h"

namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class UniformMagnetic : public Field<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		Vector_t value;
		public:
		
		UniformMagnetic(const Vector_t f) : Field<Num>(), value(f)
		{}
		
		virtual Vector_t at(const Vector_t pos, const Num time) const override
		{ return value; }
		
		virtual std::string kind() const override
		{ return "magnetic"; }
	};
	
}
}
}