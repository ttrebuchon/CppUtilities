#include "test.h"
#include <castor.h>
#include <vector>
#include <functional>

using namespace castor;

class T
{
	public:
	string str;
	
	T() : str()
	{ }
	
	T(const string s) : str(s)
	{
	}
	
	T(const char* s) : str(s)
	{
	}
	
	T(const T& t) : str(t.str)
	{
	}
	
	/*T& operator=(const T& t)
	{
		this->str = t.str;
		return *this;
	}*/
	
	bool operator==(const T t) const
	{
		return (t.str == str);
	}
	
	
};

void tTest()
{
	typedef T A;
	auto tr = [&] (lref<A> l1, lref<A> l2) -> relation {
		return eq("E", l2);
	};
	lref<A> l1("H"), l2;
	relation r1 = tr(l1, l2);
	while (r1())
	{
		cout << l2->str << endl;
		//cout << *l2 << endl;
	}
}