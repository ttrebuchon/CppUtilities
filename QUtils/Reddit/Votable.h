#pragma once
#include <string>

#include "Thing.h"

namespace QUtils { namespace Reddit {
	
	class Votable : virtual public Thing
	{
		protected:
		Votable();
		Votable(RedditSystem*, json_ptr&&);
		
		public:
		
		int ups() const;
		int downs() const;
		short likes() const;
	};
}
}