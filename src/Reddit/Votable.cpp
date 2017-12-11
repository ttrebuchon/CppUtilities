#include <QUtils/Reddit/Votable.h>
#include <QUtils/Debug/dassert.h>

namespace QUtils { namespace Reddit {
	
	Votable::Votable() : Thing(nullptr, nullptr)
	{
		dassert(json != nullptr);
		dassert(json->count("ups") > 0);
		dassert(json->count("downs") > 0);
		dassert(json->count("likes") > 0);
	}
	
	Votable::Votable(RedditSystem* sys, json_ptr&& j) : Thing(sys, std::forward<json_ptr>(j))
	{
		dassert(json->count("ups") > 0);
		dassert(json->count("downs") > 0);
		dassert(json->count("likes") > 0);
	}
}
}