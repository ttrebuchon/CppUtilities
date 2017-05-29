#include "../Tests.h"
#include <Math/tensor_t.h>
#include <initializer_list>
#include <cmath>

using namespace Utils;
using namespace Math;

#define TOL 1

#define checkStdDev(x, func) auto x = func; \
assert_ex(x < TOL && x > -1*TOL); \
dout << #x << ": " << x << std::endl

typedef float Num;

Num invStdDev(std::function<Num(int, int)>, int h, int w);

bool Testing::Tensor_T()
{
	tensor_t<1, Num> t;
	
	
	tensor_t<2, Num> t2 = new DataMatrix<2, Num>( {{1, 1}, {1, 1}});
	assert_ex(t == NULL);
	t = 4;
	t2(1, 1) = 4;
	dout << t2.toString() << std::endl;
	t2(1) = {4, 5};
	dout << t2.toString() << std::endl;
	t2 = {{1, 2}, {3, 4}};
	dout << t2.toString() << std::endl;
	t2 = { t2[0], t2[1] };
	dout << t2.toString() << std::endl;
	t2 = { tensor_t<1, Num>([](int i) -> decltype(t2[0][0]) { return i; }, 2), {2, 3}};
	
	
	
	assert_ex(t2.det() == -2);

	
	
	t2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	tensor_t<1, Num> t2_P;
	auto t2_lu = LUP_Make(t2, &t2_P);
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