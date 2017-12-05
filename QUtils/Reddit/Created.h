#pragma once
#include <string>

#include "Thing.h"

namespace QUtils { namespace Reddit {
	
	class Created : virtual public Thing
	{
		protected:
		Created() : Thing(nullptr, nullptr) {}
		
		public:
		
		long created() const;
		long created_utc() const;
	};
}
}