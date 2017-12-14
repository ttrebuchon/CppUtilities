#pragma once
#include <string>

namespace QUtils { namespace Reddit {
	
	
	
	enum struct Kind
	{
		none,
		more,
		t1,
		t2,
		t3,
		t4,
		t5,
		t6,
		Listing
	};
	
	template <Kind K>
	constexpr const char* KindToString()
	{
		static_assert((int)K >= 0, "");
		static_assert((int)K <= 8, "");
		switch (K)
		{
			case Kind::none:
				return "none";
				
			case Kind::more:
				return "more";
				
			case Kind::t1:
				return "comment";
			
			case Kind::t2:
				return "account";
			
			case Kind::t3:
				return "link";
			
			case Kind::t4:
				return "message";
			
			case Kind::t5:
				return "subreddit";
			
			case Kind::t6:
				return "award";
				
			case Kind::Listing:
				return "Listing";
		}
	}
	
	constexpr const char* KindToString(const Kind k)
	{
		switch (k)
		{
			case Kind::none:
				return "none";
				
			case Kind::more:
				return "more";
				
			case Kind::t1:
				return "comment";
			
			case Kind::t2:
				return "account";
			
			case Kind::t3:
				return "link";
			
			case Kind::t4:
				return "message";
			
			case Kind::t5:
				return "subreddit";
			
			case Kind::t6:
				return "award";
				
			case Kind::Listing:
				return "Listing";
			
			default:
				return "none";
		}
	}
	
	constexpr Kind StringToKind(const char* str)
	{
		#define CASE(x, y) \
		if (::strcmp(str, x) == 0) \
		{ \
			return Kind::y; \
		}
		
		CASE("more", more);
		CASE("comment", t1);
		CASE("t1", t1);
		CASE("account", t2);
		CASE("t2", t2);
		CASE("link", t3);
		CASE("t3", t3);
		CASE("message", t4);
		CASE("t4", t4);
		CASE("subreddit", t5);
		CASE("t5", t5);
		CASE("award", t6);
		CASE("t6", t6);
		CASE("Listing", Listing);
		
		return Kind::none;
		
		#undef CASE
	}
	
	Kind StringToKind(const std::string str);
	
}
}