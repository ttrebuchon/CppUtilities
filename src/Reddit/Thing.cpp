#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Reddit {
	
	Thing* Thing::parseURL(const std::string url, const std::string queryStr) const
	{
		return sys->parseURL(url, queryStr);
	}
	
	Thing* Thing::parse(const std::string json) const
	{
		return sys->parse(json);
	}
	
	Thing::Thing(RedditSystem* sys, json_ptr&& json, bool addToSys) : sys(sys), json()
	{
		this->json.swap(json);
		if (addToSys)
		{
			sys->addThing(this);
		}
	}
	
	Thing::~Thing()
	{
		
	}
	
	std::string Thing::id() const
	{
		return json->at("id");
	}
	
	std::string Thing::name() const
	{
		return json->at("name");
	}
	
	void Thing::refresh()
	{
		throw NotImp();
	}
}
}