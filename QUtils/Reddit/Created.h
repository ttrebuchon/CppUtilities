#pragma once
#include <string>

#include "Thing.h"

namespace QUtils { namespace Reddit {
	
	class Created : virtual public Thing
	{
		protected:
		Created();
		Created(RedditSystem*, json_ptr&&);
		
		public:
		
		long created() const;
		long created_utc() const;
	};
}
}