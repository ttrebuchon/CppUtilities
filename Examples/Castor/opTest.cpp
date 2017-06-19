#include "test.h"
#include <castor.h>

using namespace castor;

typedef lref<int> Num;

void opTest()
{
	auto _mul = [](Num op1, Num op2, Num result) -> relation {
		return eq_f(result, op2*op1);
	};
	
	Num x=4, y=9, z;
	auto r = _mul(x, y, z);
	while (r())
	{
		cout << *z << endl;
	}
}