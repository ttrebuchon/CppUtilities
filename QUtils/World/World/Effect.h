#pragma once
#include "SharedPtrOnly.h"
#include "Time.h"

namespace QUtils { namespace World {
	
	class Effect
	{
		protected:
		
		
		public:
		SHARED_PTR_ONLY(Effect)
		
		virtual ~Effect();
		
		virtual Timespan time() const = 0;
	};
}
}