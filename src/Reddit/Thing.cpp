#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Debug/dassert.h>

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
		dassert(this->json->count("id") > 0);
		dassert(this->json->count("name") > 0);
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
	
	void Thing::refresh(bool thorough)
	{
		throw NotImp();
	}
}
}