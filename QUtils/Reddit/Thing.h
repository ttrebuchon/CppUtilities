#pragma once
#include <string>
#include <memory>
#include <json/json.hpp>
#include "Kind.h"

namespace QUtils { namespace Reddit {
	
	class RedditSystem;
	
	class Thing
	{
		public:
		typedef std::unique_ptr<nlohmann::json> json_ptr;
		
		protected:
		RedditSystem* sys;
		json_ptr json;
		
		
		public:
		Thing(RedditSystem* sys, json_ptr&&);
		virtual ~Thing();
		
		
		std::string id() const;
		std::string name() const;
		Kind kind() const;
		
		virtual void refresh();
		
	};
	
	
	
}
}