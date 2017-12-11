#pragma once
#include "Thing.h"
#include <string>
#include <list>

namespace QUtils { namespace Reddit {
	
	class More : public Thing
	{
		protected:
		mutable std::list<std::string> _children;
		mutable bool childrenSet = false;
		
		More(RedditSystem*, json_ptr&&);
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::more;
		
		std::string parent_id() const;
		const std::list<std::string>& children() const;
		
		
		virtual typename Reddit::Kind kind() const override
		{
			return Kind;
		}
		
		
		template <class>
		friend class MoreListing;
		friend class RedditSystem;
	};
}
}