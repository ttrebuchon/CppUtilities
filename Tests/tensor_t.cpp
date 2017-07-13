#include "../Tests_Helpers.h"
#include <QUtils/Math/tensor_t.h>
#include <initializer_list>
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::number;


using namespace QUtils;
using namespace Math;

#define TOL 1

#define checkStdDev(x, func) auto x = func; \
assert_ex(x < TOL && x > -1*TOL); \
dout << #x << ": " << x << std::endl

//typedef number<cpp_dec_float<14368>> Num;
//typedef number<cpp_dec_float<0>> Num;
typedef float Num;

Num invStdDev(std::function<Num(int, int)>, int h, int w);

void testDataMatrix_T();

bool tensor_t_run()
{
	tensor_t<1, Num> t;
	
	
	tensor_t<2, Num> t2 = new DataMatrix<2, Num>( {{1, 1}, {1, 1}});
	assert_ex(t == NULL);
	t2 = t2 / 4;
	t = 4;
	t2(1, 1) = 4;
	dout << t2.toString() << std::endl;
	t2(1) = tensor_t<1, Num>({4, 5});
	dout << t2.toString() << std::endl;
	t2 = {{1, 2}, {3, 4}};
	dout << t2.toString() << std::endl;
	t2 = { t2[0], t2[1] };
	dout << t2.toString() << std::endl;
	t2 = { tensor_t<1, Num>([](int i) -> decltype(t2[0][0]) { return i; }, 2), {2, 3}};
	
	
	
	assert_ex(t2.det() == -2);

	
	
	t2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	tensor_t<1, Num> t2_P;
	auto t2_lu = LUP_Container<2, Num, int>::LUP_Make(t2, &t2_P);
	dout << "\n\nt2_lu: \n" << t2_lu.toString() << "\n" << std::endl;
	dout <<  "t2_P: \n" << t2_P.toString() << "\n\n" << std::endl;

	dout << "t2.det() -> " << t2.det() << std::endl;
	assert_ex(t2.det() == 0);
	
	
	tensor_t<2, Num> invTest = new FuncMatrix<2, Num>([](int i, int j) {
		return 2*i + (j+1);
	}, 2, 2);
	dout << "invTest: " << invTest.toString() << std::endl;
	auto invTesti = invTest.inv();
	dout << "invTesti: " << invTesti.toString() << std::endl;
	dout << "invTest.invTesti: " << invTest.contract(invTesti).toString() << std::endl;
	
	int w = 2;
	tensor_t<2, Num> invT2 = new FuncMatrix<2, Num>([=](int i, int j) {
		return i*w + (j+1);
	}, 4, w);
	
	dout << "invT2: " << invT2.toString() << std::endl;
	auto invT2i = invT2.inv();
	dout << "invT2i: " << invT2i.toString() << std::endl;
	auto id = invT2i.contract(invT2);
	dout << "id: " << id.toString() << std::endl;
	
	auto reconstruction = invT2.contract(id);
	dout << "Reconstruction: " << reconstruction.toString() << std::endl;
	auto err = invT2 - reconstruction;
	dout << "Err: " << err.toString() << std::endl;
	
	Num stdDev = 0;
	int iSize = err.size(0);
	int jSize = err.size(1);
	for (int i = 0; i < iSize; i++)
	{
		for (int j = 0; j < jSize; j++)
		{
			stdDev += pow(err(i, j), 2);
		}
	}
	stdDev /= iSize*jSize;
	stdDev = sqrt(stdDev);
	dout << "StdDev: " << stdDev << std::endl;
	
	checkStdDev(stdDev2, invStdDev([=](int i, int j) { return i*w + (j+1); }, 4, w));
	
	checkStdDev(stdDev3, invStdDev([] (int i, int j) -> Num { return (i == j); }, 4, 4));
	
	checkStdDev(stdDev4, invStdDev([] (int i, int j) -> Num { return i*2 + (j+1); }, 2, 2));
	
	checkStdDev(stdDev5, invStdDev([] (int i, int j) -> Num { return sin(i+1)*cos(2*j + i); }, 2, 2));
	
	testDataMatrix_T();
	
	return true;
}



Num invStdDev(std::function<Num(int, int)> f, int h, int w)
{
	tensor_t<2, Num> invT2 = new FuncMatrix<2, Num>(f, h, w);
	auto invT2i = invT2.inv();
	auto id = invT2i.contract(invT2);
	
	auto reconstruction = invT2.contract(id);
	auto err = invT2 - reconstruction;
	
	Num stdDev = 0;
	int iSize = err.size(0);
	int jSize = err.size(1);
	for (int i = 0; i < iSize; i++)
	{
		for (int j = 0; j < jSize; j++)
		{
			stdDev += pow(err(i, j), 2);
		}
	}
	stdDev /= iSize*jSize;
	stdDev = sqrt(stdDev);
	return stdDev;
	
}

void testDataMatrix_T()
{
	dout << "Checking rank 2 tensor..." << std::endl;
	int h = 10;
	int w = 9;
	int z = 10;
	
	tensor_t<2, double> fMat = new FuncMatrix<2, double>([=] (int i, int j)
	{
		return static_cast<double>(i*w + (j+1));
	}, h, w);
	
	
	tensor_t<2, double> dMat = new DataMatrix<2, double>();
	
	dMat.setSize(0, h);
	dMat.setSize(1, w);
	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			dMat(i, j) = static_cast<double>(i*w + j + 1);
		}
	}
	
	
	auto fMat_T = fMat.T();
	auto dMat_T = dMat.T();
	
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			assert_ex(fMat_T(i, j) == dMat_T(i, j));
		}
	}
	
	
	
	
	
	
	
	dout << "Checking rank 3 tensor..." << std::endl;
	
	tensor_t<3, double> fMat_3 = new FuncMatrix<3, double>([=] (int i, int j, int k)
	{
		return static_cast<double>(i*w + (j+1) + k*h*w);
	}, h, w, z);
	
	
	tensor_t<3, double> dMat_3 = new DataMatrix<3, double>();
	
	dMat_3.setSize(0, h);
	dMat_3.setSize(1, w);
	dMat_3.setSize(2, z);
	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			for (int k = 0; k < z; k++)
			{
				dMat_3(i, j, k) = static_cast<double>(i*w + j + 1 + k*w*h);
			}
		}
	}
	
	
	auto fMat_3_T = fMat_3.T();
	auto dMat_3_T = dMat_3.T();
	
	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < w; j++)
		{
			for (int k = 0; k < h; k++)
			{
				assert_ex(fMat_3_T(i, j, k) == dMat_3_T(i, j, k));
			}
		}
	}
}