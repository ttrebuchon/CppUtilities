#pragma once

namespace QUtils { namespace Reddit {
	
	
	
	enum struct Kind
	{
		t1,
		t2,
		t3,
		t4,
		t5,
		t6
	};
	
	template <Kind K>
	constexpr const char* KindToString()
	{
		static_assert((int)K >= 0, "");
		static_assert((int)K <= 5, "");
		switch (K)
		{
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
		}
	}
	
	constexpr const char* KindToString(const Kind k)
	{
		switch (k)
		{
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
		}
	}
	
}
}