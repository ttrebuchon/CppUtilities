#include "../Tests.h"

#include <LazyLoad/LazyLoad.h>
#include <string>

struct TStruct
{
	int x;
	int y;
	
	TStruct() : x(0), y(0)
	{ }
	
	TStruct(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	TStruct operator+(const TStruct& t)
	{
		return {x+t.x, y+t.y};
	}
	
	
};

std::ostream& operator<<(std::ostream& o, const TStruct& t)
{
	o << "(" << t.x << ", " << t.y << ")";
	return o;
}

bool Testing::Lazy()
{
	Util::LazyLoad<std::string*> l;
	*l = "Hello";
	dout << l->c_str() << std::endl;
	assert_ex(strcmp(l->c_str(), "Hello") == 0);
	
	Util::LazyLoad<std::string> ls;
	ls = "Test";
	dout << ((std::string&)ls).c_str() << std::endl;
	assert_ex(strcmp(((std::string&)ls).c_str(), "Test") == 0);
	
	((std::string&)ls) += *l;
	
	dout << (std::string&)ls << std::endl;
	assert_ex((std::string&)ls == "TestHello");
	
	Util::LazyLoad<std::string> stacklaz;
	
	auto g = stacklaz;
	stacklaz = "Hello, world!";
	assert_ex(stacklaz == "Hello, world!");
	assert_ex(g != "Hello, world!");
	
	
	g = "Testing";
	assert_ex(g == "Testing");
	assert_ex(stacklaz == "Hello, world!");
	
	dout << l << std::endl;
	assert_ex(NULL != l);
	assert_ex(l != NULL);
	assert_ex(!(NULL == l));
	assert_ex(!(l == NULL));
	
	l.free();
	l = nullptr;
	l.free();
	assert_ex(l.v() == NULL);
	
	dout << (g + " Pt. 2") << std::endl;
	
	Util::LazyLoad<TStruct> tsl;
	
	auto x = (tsl + TStruct(4, 4));
	
	dout << x << std::endl;
	dout << tsl << std::endl;
	
	return true;
}