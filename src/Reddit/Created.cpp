#include <QUtils/Reddit/Created.h>
#include <QUtils/Debug/dassert.h>

namespace QUtils { namespace Reddit {
	
	Created::Created() : Thing(nullptr, nullptr)
	{
		dassert(json != nullptr);
		dassert(json->count("created") > 0);
		dassert(json->count("created_utc") > 0);
	}
	
	Created::Created(RedditSystem* sys, json_ptr&& j) : Thing(sys, std::forward<json_ptr>(j))
	{
		dassert(json->count("created") > 0);
		dassert(json->count("created_utc") > 0);
	}
}
}