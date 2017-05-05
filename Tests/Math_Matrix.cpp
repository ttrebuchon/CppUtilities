#include "../Tests_Helpers.h"


#include <Math/Matrix.h>

using namespace Util;
using namespace Math;



bool Math_Matrix()
{
	//dout << "\n\n\n" << std::endl;
	
	
	
	
	
	
	
	
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
	
	auto testDets = [=] (auto m1, auto m2)
	{
		//dout << "\n\n" << std::endl;
		auto m3 = m1.contract(m2);
		
		/*print_matrix(m1);
		print_matrix(m2);
		print_matrix(m3);*/
		
		auto d1 = m1.det();
		//dout << "Det 1: " << d1 << std::endl;
		auto d2 = m2.det();
		//dout << "Det 2: " << d2 << std::endl;
		auto d3 = m3.det();
		//dout << "Det 3: " << d3 << std::endl;
		
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
	
	/*dout << consec_m_1.toString() << std::endl;
	
	dout << consec_m_3.contract(consec_m_1).toString() << std::endl;
	
	dout << "M3 Det: " << consec_m_3.det() << std::endl;
	dout << "M2 Det: " << consec_m.det() << std::endl;
	
	dout << "M3 • M2 Det: " << consec_m_3.contract(consec_m).det() << std::endl;
	dout << "M3 • M2:\n" << consec_m_3.contract(consec_m).toString() << std::endl;
	
	
	
	dout << "M2 • M1:\n" << consec_m.contract(consec_m_1).toString() << std::endl;*/
	
	

	return true;
	
	
}