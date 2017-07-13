#include "../Tests_Helpers.h"


#include <QUtils/Math/Math.h>

using namespace QUtils;
using namespace Math;

#define OUTPUT
#define ALIVE_OUT


#ifdef OUTPUT

#define check(x, n) dout << (x).toString() << " == " << #n << std::endl; \
assert_ex((x).toString() == #n)

    #ifdef ALIVE_COUNTER
    
    #define check_alive(x) p_alive; \
assert_ex(Expression::alive() == x)

        #ifdef ALIVE_OUT

        #define p_alive dout << "\tAlive: " << Expression::alive() << std::endl
    
        #else
    
        #define p_alive
    
        #endif
    
    #else

    #define check_alive(x)

    #define p_alive

    #endif

#else

#define check(x, n) assert_ex((x).toString() == #n)

    #ifdef ALIVE_COUNTER

    #define check_alive(x) assert_ex(Expression::alive() == x)

    #else

    #define check_alive(x)

    #endif

#define p_alive

#endif

bool TestMath()
{
	
	
	Term _4(4);
	check(_4, 4);
	check_alive(1);
	
	Term _4__4 = _4 + _4;
	check(_4__4, 4 + 4);
	check_alive(4);
	
	Term _8 = _4__4.eval();
	check(_8, 8);
	check_alive(5);
	
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
	
	Term _6__2 = Term(6)^2;
	check(_6__2, 6^2);
	check(_6__2.eval(), 36);
	
	Term _9__7 = Term(9) - 7;
	check(_9__7, 9 - 7);
	check(_9__7.eval(), 2);
	
	Term _5__2 = Term(5) / 2;
	check(_5__2, 5/2);
	check(_5__2.eval(), 2.5);
	
	Term x2__4 = x / 4 * x;
	check(x2__4.eval(), (x^2)/4);
	
	Term _5 = _5__2 * 2;
	check(_5, 2*(5/2));
	check(_5.eval(), 5);
	
	Term _x2__4 = (x / 2) * (x / 2);
	check(_x2__4.eval(), (x^2)/4);
	
	
	
	
	
	Term G("G"), M("M"), r("r");
	Term testEq = G*M/(r^2)*r;
	
	p_alive;
	return true;
}

bool IntermediateMath()
{
	bool result = TestMath();
	dout << "\n\n" << std::endl;
	check_alive(0);
	return result;
	
}