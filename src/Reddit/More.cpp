#include <QUtils/Reddit/More.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	More::More(RedditSystem* sys, json_ptr&& j) : Thing(sys, std::forward<json_ptr>(j))
	{
		dassert(json->count("parent_id") > 0);
		dassert(json->count("children") > 0);
		dassert(this->name().substr(0, 5) == "more_");
	}
	
	
	#define PROPERTY(TYPE, NAME) CLASS_PROPERTY(More, TYPE, NAME)
	
	PROPERTY(std::string, parent_id)
	
	const std::list<std::string>& More::children() const
	{
		if (!childrenSet)
		{
			_children = json->at("children").get<std::list<std::string>>();
			childrenSet = true;
		}
		return _children;
	}
	
}
}