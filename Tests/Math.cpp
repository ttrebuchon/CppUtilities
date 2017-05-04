#include "../Tests.h"


#include <Math/Math.h>

using namespace Util;
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
	
	
	dout << "\n\n\n" << std::endl;
	
	
	
	
	
	
	
	
	FuncMatrix<1, int> c1 = FuncMatrix<1, int>([](int i) -> int { return 4*i; });
	
	auto s1 = c1[3];
	dout << s1 << std::endl;
	assert_ex(s1 == 12);
	
	std::function<int(int, int)> f([](int i, int j) -> int { return i*j; });
	
	auto f2 = [](int i, int j) -> int { return i*j; };
	
	FuncMatrix<2, double> m1(f2);
	auto c2_1 = m1[2];
	auto c1_2_1 = (*c2_1)[1];
	assert_ex(c1_2_1 == 2);
	
	matrix_t<2, double> mt1(new FuncMatrix<2, double>(f2));
	auto ct1_2_1 = mt1[2][1];
	assert_ex(ct1_2_1 == 2);
	auto ct2_1 = mt1[2];
	ct1_2_1 = ct2_1[1];
	assert_ex(ct1_2_1 == 2);
	
	matrix_t<2, double> matTest = new FuncMatrix<2, double>(f2);
	auto colT1_2_1 = matTest[2][1];
	assert_ex(colT1_2_1 == 2);
	auto colT2_1 = matTest[2];
	colT1_2_1 = colT2_1[1];
	assert_ex(colT1_2_1 == 2);
	
	dout << "Created..." << std::endl;
	matTest = new FuncMatrix<2, double>([](int i, int j) { return i*(i-j); });
	
	int matTest_n = 15;
	int matTest_m = 10;
	
	matTest.size()[0] = matTest_n;
	matTest.size()[1] = matTest_m;
	
	
	auto print_matrix = [](auto m)
	{
		for (auto i = 0; i < m.size()[0]; i++)
		{
			dout << "[ ";
			for (auto j = 0; j < m.size()[1]; j++)
			{
				dout << m[i][j] << ", ";
			}
			dout << "]" << std::endl;
		}
		dout << "\n\n" << std::endl;
	};
	
	/*for (int i = 0; i < matTest.size()[0]; i++)
	{
		dout << "[ ";
		for (int j = 0; j < matTest.size()[1]; j++)
		{
			dout << matTest[i][j] << ", ";
		}
		dout << "]" << std::endl;
	}*/
	
	print_matrix(matTest);
	
	
	
	
	
	
	auto matTestT = matTest.T();
	assert_ex(matTestT.size()[0] == matTest.size()[1]);
	assert_ex(matTestT.size()[1] == matTest.size()[0]);
	dout << "\n\nTransposed: " << std::endl;
	/*for (int i = 0; i < matTestT.size()[0]; i++)
	{
		dout << "[ ";
		for (int j = 0; j < matTestT.size()[1]; j++)
		{
			dout << matTestT[i][j] << ", ";
			assert_ex(matTestT[i][j] == matTest[j][i]);
		}
		dout << "]" << std::endl;
	}*/
	print_matrix(matTestT);
	
	
	int removeX, removeY;
	removeX = 1;
	removeY = 0;
	dout << "\n\nSubmatrix: (" << removeY << ", " << removeX << ")" << std::endl;
	auto matTestSM = matTestT.submatrix(removeY, removeX);
	
	print_matrix(matTestSM);
	
	
	matTest.size()[0] = matTest.size()[1] = matTestT.size()[0] = matTestT.size()[1] = 3;
	dout << "\n\nContracting Matrices..." << std::endl;
	
	print_matrix(matTest);
	//dout << "\n\n" << std::endl;
	print_matrix(matTestT);
	//dout << "\n\n" << std::endl;
	
	
	auto matTestC = matTest.contract(matTestT);
	dout << "\n\nContracted Matrix: " << std::endl;
	print_matrix(matTestC);
	//dout << "\n\n" << std::endl;
	auto matTest_4 = matTest;
	matTest_4.size()[0] = matTest_4.size()[1] = 4;
	for (int i = 0; i < 1; i++)
	{
		matTest_4 = matTest_4.contract(matTest_4);
	}
	print_matrix(matTest_4);
	//dout << "\n\n" << std::endl;
	print_matrix(matTest_4);
	
	
	dout << "Determinant: " << std::endl;
	print_matrix(matTestC.submatrix(0, 0));
	dout << matTestC.submatrix(0, 0).det() << std::endl;
	dout << matTestC.submatrix(0, 0).contract(matTestC.submatrix(0, 0)).det() << std::endl;
	
	
	
	
	dout << "\n\n\n" << std::endl;
	
	
	Term G("G"), M("M"), r("r");
	Term testEq = G*M/(r^2)*r;
	check(testEq.eval(), (G*M)/r);
	
	p_alive;
	return true;
}

bool Testing::Math()
{
	bool result = TestMath();
	dout << "\n\n" << std::endl;
	check_alive(0);
	return result;
	
}