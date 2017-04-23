#include "../Tests.h"


#include <Math/Math.h>

using namespace Util;
using namespace Math;

#define OUTPUT

#ifdef OUTPUT
#define check(x, n) dout << (x).toString() << " == " << #n << std::endl; \
assert_ex((x).toString() == #n)
#else
#define check(x, n) assert_ex((x).toString() == #n)
#endif

bool Testing::Math()
{
	Term _4(4);
	check(_4, 4);
	
	Term _4__4 = _4 + _4;
	check(_4__4, 4 + 4);
	
	Term _8 = _4__4.eval();
	check(_8, 8);
	
	Term x("x");
	check(x, x);
	
	Term _3 = 3;
	check(_3, 3);
	
	Term y = "y";
	check(y, y);
	
	Term z = 'z';
	check(z, z);
	
	check(2*x, 2*x);
	check((x*2).eval(), 2*x);
	check((x + x).eval(), 2*x);
	check(x + y, x + y);
	check((x + x + 4).eval(), 2*x + 4);
	
	Term x2 = x^2;
	check(x2, x^2);
	
	check((x*x).eval(), x^2);
	
	
	return true;
}