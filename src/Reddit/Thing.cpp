#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Reddit {
	
	Thing::Thing(RedditSystem* sys, json_ptr&& json) : sys(sys), json()
	{
		this->json.swap(json);
		sys->addThing(this);
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