#include "../Tests_Helpers.h"


#include <Math/Matrix.h>
#include <vector>
#include <string>
#include <type_traits>

using namespace Util;
using namespace Math;

int Matrix_Counter::alive = 0;

bool Math_Matrix_Go();
bool Test_Arithmetic();
bool Test_DataMatrix();

bool Math_Matrix()
{
	bool result = Math_Matrix_Go();
	dout << "Alive: " << Matrix_Counter::alive << std::endl;
	return result;
}

bool Math_Matrix_Go()
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
	
	matrix_t<2, double> mt1(std::make_shared<FuncMatrix<2, double>>(f2));
	auto ct1_2_1 = mt1[2][1];
	assert_ex(ct1_2_1 == 2);
	auto ct2_1 = mt1[2];
	ct1_2_1 = ct2_1[1];
	assert_ex(ct1_2_1 == 2);
	
	matrix_t<2, double> matTest;
	matTest = std::make_shared<FuncMatrix<2, double>>(f2);
	auto colT1_2_1 = matTest[2][1];
	assert_ex(colT1_2_1 == 2);
	auto colT2_1 = matTest[2];
	colT1_2_1 = colT2_1[1];
	assert_ex(colT1_2_1 == 2);
	
	matTest = std::make_shared<FuncMatrix<2, double>>([](int i, int j) { return i*(i-j); });
	
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
	matrix_t<2, double, int> testC_2_2(std::make_shared<FuncMatrix<2, double, int>>([] (int i, int j) {
		    return (j+1) + 2*i;
		}));
	testC_2_2.size()[0] = testC_2_2.size()[1] = 2;
	matrix_t<1, double, int> testC_1_2(std::make_shared<FuncMatrix<1, double, int>>([] (int i) {
		    return (i+1);
		}));
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
	
	matrix_t<2, double> matTestD(std::make_shared<FuncMatrix<2, double>>([](int i, int j) { return (i % j) + (j % i); }));
	
	
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
	
	matrix_t<consec_dims, double, int> consec_m(std::make_shared<FuncMatrix<consec_dims, double, int>>(consecutive_func));
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
	
	matrix_t<consec_dims+1, double, int> consec_m_3(std::make_shared<FuncMatrix<consec_dims+1, double, int>>(consecutive_func_3));
	for (int i = 0; i < consec_dims+1; i++)
	{
		consec_m_3.size()[i] = consec_size;
	}
	
	dout << consec_m_3.toString() << std::endl;
	matrix_t<1, double, int> consec_m_1(std::make_shared<FuncMatrix<1, double, int>> ([consec_size] (auto i){
		return i+1;
	}));
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
	
	
	
	return Test_Arithmetic();
}














bool Test_Arithmetic()
{
	dout << "\n\nTesting matrix arithmetic..." << endl;
	
	matrix_t<1, double> m1([] (auto i) { return 4 - i; });
	matrix_t<1, double> m2([] (auto i) { return i; });
	auto m3 = m1 + m2;
	m3.size()[0] = 5;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m3[i] == 4);
	}
	
	m3 = m1 - m2;
	m3.size()[0] = 5;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m3[i] == (4 - 2*i));
	}
	
	
	
	
	
	
	
	m1.size()[0] = 6;
	m3 = m1 + m2;
	assert_ex(m3.size()[0] == 6);
	for (int i = 0; i < 6; i++)
	{
		assert_ex(m3[i] == 4);
	}
	
	
	
	
	
	m1.size()[0] = -1;
	auto m4 = m1*m2;
	m4.size()[0] = 5;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m4[i] == ((4-i)*i));
	}
	
	m4 = m1*10;
	m4.size()[0] = 5;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m4[i] == ((4-i)*10));
	}
	
	
	
	
	
	
	
	matrix_t<2, double> m21([] (auto i, auto j) { return (4 - i)*(j+1); });
	matrix_t<2, double> m22([] (auto i, auto j) { return i+j; });
	
	auto m23 = m21 + m22;
	m23.size()[0] = 5;
	m23.size()[1] = 5;
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m23[i][j] == ((4 - i)*(j+1) + (i+j)));
	}
	}
	
	m23 = m21 - m22;
	m23.size()[0] = 5;
	m23.size()[1] = 5;
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m23[i][j] == ((4 - i)*(j+1) - (i+j)));
	}
	}
	
	
	
	
	
	
	
	m21.size()[0] = 6;
	m21.size()[1] = 7;
	m23 = m21 + m22;
	assert_ex(m23.size()[0] == 6);
	assert_ex(m23.size()[1] == 7);
	for (int i = 0; i < 6; i++) {
	for (int j = 0; j < 7; j++)
	{
		assert_ex(m23[i][j] == ((4 - i)*(j+1) + (i+j)));
	}
	}
	
	
	
	
	
	m21.size()[0] = -1;
	m21.size()[1] = -1;
	auto m24 = m21*m22;
	m24.size()[0] = 5;
	m24.size()[1] = 5;
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m24[i][j] == ((4 - i)*(j+1)*(i+j)));
	}
	}
	
	
	m24 = m21*10;
	m24.size()[0] = 5;
	m24.size()[1] = 5;
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m24[i][j] == ((4 - i)*(j+1)*10));
	}
	}
	
	
	
	
	
	
	dout << "Passed." << std::endl;
	return true;//Test_DataMatrix();
}

bool Test_DataMatrix()
{
	dout << "\n\nTesting Data Matrix..." << endl;
	
	auto vecFromFunc = [](auto func, int size)
	{
		std::vector<double> v(size);
		for (auto i = 0; i < size; i++)
		{
			v[i] = func(i);
		}
		return v;
	};
	
	auto vecFrom2dFunc = [vecFromFunc](auto func, int size1, int size2)
	{
		std::vector<std::vector<double>> v(size1);
		for (auto i = 0; i < size1; i++)
		{
			v[i] = vecFromFunc([=] (auto j) { return func(i, j); }, size2);
		}
		return v;
	};
	
	
	
	
	
	matrix_t<1, double> m1(std::make_shared<DataMatrix<1, double>>(vecFromFunc([] (auto i) { return 4 - i; }, 5)));
	matrix_t<1, double> m2(std::make_shared<DataMatrix<1, double>>(vecFromFunc([] (auto i) { return i; }, 5)));
	auto m3 = m1 + m2;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m3[i] == 4);
	}
	assert_ex(m3.size()[0] == 5);
	
	m3 = m1 - m2;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m3[i] == (4 - 2*i));
	}
	assert_ex(m3.size()[0] == 5);
	
	
	
	
	auto m4 = m1*m2;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m4[i] == ((4-i)*i));
	}
	assert_ex(m4.size()[0] == 5);
	
	m4 = m1*10;
	for (int i = 0; i < 5; i++)
	{
		assert_ex(m4[i] == ((4-i)*10));
	}
	assert_ex(m4.size()[0] == 5);
	
	
	
	
	
	
	
	matrix_t<2, double> m21(std::make_shared<DataMatrix<2, double>>(vecFrom2dFunc([] (auto i, auto j) { return (4 - i)*(j+1); }, 5, 5)));
	
	//matrix_t<2, double> m22(std::make_shared<DataMatrix<2, double>>(vecFrom2dFunc([] (auto i, auto j) { return i+j; }, 5, 5)));
	dout << "Arriving..." << std::endl;
	matrix_t<2, double> m22;
	dout << "Initted as Null" << std::endl;
	m22 = new DataMatrix<2, double>(vecFrom2dFunc([] (auto i, auto j) { return i+j; }, 5, 5));
	dout << "Assigned..." << std::endl;
	
	auto m23 = m21 + m22;
	assert_ex(m23.size()[0] == 5);
	assert_ex(m23.size()[1] == 5);
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m23[i][j] == ((4 - i)*(j+1) + (i+j)));
	}
	}
	
	
	
	
	m23 = m21 - m22;
	assert_ex(m23.size()[0] == 5);
	assert_ex(m23.size()[1] == 5);
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m23[i][j] == ((4 - i)*(j+1) - (i+j)));
	}
	}
	
	
	
	
	
	auto m24 = m21*m22;
	assert_ex(m24.size()[0] == 5);
	assert_ex(m24.size()[1] == 5);
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m24[i][j] == ((4 - i)*(j+1)*(i+j)));
	}
	}
	
	
	m24 = m21*10;
	assert_ex(m24.size()[0] == 5);
	assert_ex(m24.size()[1] == 5);
	for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++)
	{
		assert_ex(m24[i][j] == ((4 - i)*(j+1)*10));
	}
	}
	
	
	
	for (int i = 0; i < m24.size()[0]; i++)
	{
		for (int k = 0; k < m24.size()[1]; k++)
		{
			static_assert(std::is_same<decltype(m24(i, k)), double&>::value, "Type error in Math_Matrix.cpp, Test_DataMatrix()");
			static_assert(std::is_same<decltype(m24(i)[k]), double>::value, "Type error in Math_Matrix.cpp, Test_DataMatrix()");
			m24(i, k) = 3;
			++m24(i, k);
			
			assert_ex(m24[i][k] == 4);
			assert_ex(m24(i, k) == 4);
			assert_ex(m24(i)(k) == 4);
			assert_ex(m24(i)[k] == 4);
			assert_ex(m24[i](k) == 4);
		}
	}
	
	
	
	dout << "Passed." << endl;
	
	return true;
}