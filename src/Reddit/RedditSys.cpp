#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/RedditSys.h>
#include <QUtils/Reddit/Subreddit.h>
#include <QUtils/Reddit/Link.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/String.h>
#include <iostream>

namespace QUtils { namespace Reddit {
	
	Subreddit* RedditSystem::subreddit(const std::string name)
	{
		String lower = String(name).toLower();
		
		if (thingsByName.count(lower) > 0)
		{
			return (Subreddit*)thingsByName.at(lower);
		}
		auto j = nlohmann::json::parse(this->getPage(url + "/r/" + name + "/about.json", ""));
		dassert(j.count("kind") == 1);
		if (j.at("kind") == "Listing")
		{
			dassert(j.count("data") == 1);
			j = j.at("data");
			dassert(j.count("children") == 1);
			j = j.at("children");
			dassert(j.is_array());
			dassert(j.size() == 0);
			return NULL;
		}
		
		dassert(j.at("kind") == "t5");
		j = j.at("data");
		
		auto jptr = std::make_unique<nlohmann::json>();
		std::swap(*jptr, j);
		
		auto sub = new Subreddit(this, (Thing::json_ptr&&)std::move(jptr));
		
		thingsByName[lower] = sub;
		String lowerFullName = sub->name();
		lowerFullName = lowerFullName.toLower();
		
		if (thingsByName.count(lowerFullName) <= 0)
		{
			thingsByName[lowerFullName] = sub;
			
		}
		
		return sub;
	}
	
	Link* RedditSystem::link(const std::string id)
	{
		String low = String(id).toLower();
		if (thingsByName.count("t3_" + low) > 0)
		{
			auto link = dynamic_cast<Link*>(thingsByName.at("t3_" + low));
			if (link == NULL)
			{
				thingsByName.erase("t3_" + low);
			}
			else
			{
				return link;
			}
		}
		auto j = nlohmann::json::parse(this->getPage(url + "/" + id + ".json", ""));
		dassert(j.is_array());
		j = j[0];
		dassert(j.is_object());
		dassert(j.at("kind") == "Listing");
		dassert(j.at("data").is_object());
		j = j.at("data").at("children");
		dassert(j.is_array());
		j = j[0];
		dassert(j.at("kind") == "t3");
		
		j = j.at("data");
		
		auto jptr = std::make_unique<nlohmann::json>();
		std::swap(*jptr, j);
		
		auto link = new Link(this, (Thing::json_ptr&&)std::move(jptr));
		
		String name = String(link->name()).toLower();
		if (thingsByName.count(name) <= 0)
		{
			thingsByName[name] = link;
		}
		
		return link;
	}
	
	void RedditSystem::addThing(Thing* thing)
	{
		items.insert(thing);
		if (thingsByName.count(thing->name()) <= 0 && thing->name() != "")
		{
			thingsByName[thing->name()] = thing;
		}
	}
}
}