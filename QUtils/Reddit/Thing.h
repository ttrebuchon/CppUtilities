#pragma once
#include <string>
#include <memory>
#include <json/json.hpp>
#include "Kind.h"
#include "RedditSys.h"

namespace QUtils { namespace Reddit {
	
	class RedditSystem;
	
	template <class>
	class Listing;
	
	class Thing
	{
		public:
		typedef std::unique_ptr<nlohmann::json> json_ptr;
		
		protected:
		mutable RedditSystem* sys;
		json_ptr json;
		
		
		Thing* parseURL(const std::string url, const std::string queryStr = "") const;
		Thing* parse(const std::string json) const;
		
		template <class T = Thing>
		Listing<T>* parseListingURL(const std::string url, const std::string query) const;
		
		public:
		Thing(RedditSystem* sys, json_ptr&&, bool addToSys = true);
		virtual ~Thing();
		
		
		std::string id() const;
		std::string name() const;
		Kind kind() const;
		
		virtual void refresh();
		
	};
	
	
	
}
}

#include "Thing.hpp"