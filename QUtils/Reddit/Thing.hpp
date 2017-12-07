#pragma once
#include "Thing.h"
#include "RedditSys.h"

namespace QUtils { namespace Reddit {
	
	template <class T = Thing>
	Listing<T>* Thing::parseListingURL(const std::string url, const std::string query) const
	{
		return sys->parseListingURL<T>(url, query);
	}
	
}
}