#include "../Tests_Helpers.h"


#include <Math/Matrix.h>

using namespace Util;
using namespace Math;



bool Math_Matrix()
{
	FuncMatrix<1, int> c1 = FuncMatrix<1, int>([](int i) -> int { return 4*i; });
	
	auto s1 = c1[3];
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
	
	
	
	
	
	auto matTestT = matTest.T();
	assert_ex(matTestT.size()[0] == matTest.size()[1]);
	assert_ex(matTestT.size()[1] == matTest.size()[0]);
	
	int removeX, removeY;
	removeX = 1;
	removeY = 0;
	auto matTestSM = matTestT.submatrix(removeY, removeX);
	
	
	matTest.size()[0] = matTest.size()[1] = matTestT.size()[0] = matTestT.size()[1] = 3;
	dout << "\n\nContracting Matrices..." << std::endl;
	
	print_matrix(matTest);
	print_matrix(matTestT);
	
	
	auto matTestC = matTest.contract(matTestT);
	dout << "\n\nContracted Matrix: " << std::endl;
	print_matrix(matTestC);
	
	
	
	
	dout << "\n\nTesting 2x2 contract 2x1..." << std::endl;
	matrix_t<2, double, int> testC_2_2 = new FuncMatrix<2, double, int>([] (int i, int j) {
		    return (j+1) + 2*i;
		});
	testC_2_2.size()[0] = testC_2_2.size()[1] = 2;
	matrix_t<1, double, int> testC_1_2 = new FuncMatrix<1, double, int>([] (int i) {
		    return (i+1);
		});
	testC_1_2.size()[0] = 2;
	dout << testC_2_2.toString() << " • " << testC_1_2.toString() << std::endl;
	auto testC_p = testC_2_2.contract(testC_1_2);
	dout << testC_p.toString() << std::endl;
	assert_ex(testC_p[0] == 5);
	assert_ex(testC_p[1] == 11);
	dout << "Passed\n\n" << std::endl;
	
	
	
	
	
	dout << "Determinant: " << std::endl;
	print_matrix(matTestC.submatrix(0, 0));
	dout << matTestC.submatrix(0, 0).det() << std::endl;
	
	auto testDets = [=] (auto m1, auto m2)
	{
		auto m3 = m1.contract(m2);
		
		auto d1 = m1.det();
		auto d2 = m2.det();
		auto d3 = m3.det();
		assert_ex(d3 == d1*d2);
	};
	
	matrix_t<2, double> matTestD = new FuncMatrix<2, double>([](int i, int j) { return (i % j) + (j % i); });
	
	
	matTestD.size()[0] = matTestD.size()[1] = 4;
	testDets(matTestD.submatrix(0, 0), matTestD.T().submatrix(0, 0));
	
	const int consec_size = 2;
	const int consec_dims = 2;
	
	auto consecutive_func = [consec_size] (auto i, auto j)
	{
		i += 1;
		j += 1;
		return (j + (i-1)*consec_size);
	};
	
	matrix_t<consec_dims, double, int> consec_m = new FuncMatrix<consec_dims, double, int>(consecutive_func);
	for (int i = 0; i < consec_dims; i++)
	{
		consec_m.size()[i] = consec_size;
	}
	
	print_matrix(consec_m);
	
	auto consecutive_func_3 = [consec_size] (auto i, auto j, auto k)
	{
		i += 1;
		j += 1;
		k += 1;
		return ((j-1)*consec_size + (i-1)*consec_size*consec_size + k);
	};
	
	matrix_t<consec_dims+1, double, int> consec_m_3 = new FuncMatrix<consec_dims+1, double, int>(consecutive_func_3);
	for (int i = 0; i < consec_dims+1; i++)
	{
		consec_m_3.size()[i] = consec_size;
	}
	
	dout << consec_m_3.toString() << std::endl;
	matrix_t<1, double, int> consec_m_1 = new FuncMatrix<1, double, int>([consec_size] (auto i){
		return i+1;
	});
	consec_m_1.size()[0] = consec_size;
	
	auto testC_1_1 = [] (int size) -> void
	{
		matrix_t<2, double> m1([] (int i, int j) -> double {
			return j+1;
		});
		
		m1.size()[0] = 1;
		m1.size()[1] = size;
		
		matrix_t<1, double, int> m2([] (auto i) {
			return i+1;
		});
		m2.size()[0] = size;
		
		auto p = m1.contract(m2);
		
		auto ansFunc = [] (int size) -> decltype(p[0])
		{
			decltype(p[0]) tot = 0;
			for (int i = 0; i < size; i++)
			{
				tot += (i+1)*(i+1);
			}
			return tot;
		};
		
		assert_ex(ansFunc(size) == p[0]);
	};
	testC_1_1(5);
	
	return true;
}