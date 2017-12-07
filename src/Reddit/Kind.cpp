#include <QUtils/Reddit/Kind.h>
#include <string>

namespace QUtils { namespace Reddit {
	
	Kind StringToKind(const std::string str)
	{
		#define CASE(x, y) \
		if (str == x) \
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
		
		return Kind::none;
		
		#undef CASE
	}
}
}