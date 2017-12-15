#pragma once

#include "Base.h"
#include <memory>


namespace QUtils { namespace World {
namespace Physics {
	
	template <class Num>
	class Field : public Base<Num>
	{
		private:
		
		protected:
		BASE_USINGS(Num)
		
		
		public:
		typedef std::shared_ptr<typename Base<Num>::Field_t> Ptr;
		typedef std::shared_ptr<const typename Base<Num>::Field_t> CPtr;
		
		virtual Vector_t at(const Vector_t pos, const Num time) const = 0;
		
		virtual std::string kind() const = 0;
	};
	
}
}
}