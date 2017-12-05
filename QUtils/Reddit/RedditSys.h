#pragma once
#include <set>
#include <string>
#include <map>

#include "ForwardDecs.h"

namespace QUtils { namespace Reddit {
	
	class RedditSystem
	{
		protected:
		mutable std::set<Thing*> items;
		const std::string url = "http://www.reddit.com";
		
		virtual std::string getPage(const std::string URL, const std::string queryStr) const = 0;
		
		void addThing(Thing*);
		
		mutable std::map<std::string, Thing*> thingsByName;
		
		public:
		RedditSystem() : items()
		{}
		
		Subreddit* subreddit(const std::string);
		Link* link(const std::string);
		
		Thing* parseJSON(const std::string);
		
		friend class Thing;
	};
	
	
	
}
}