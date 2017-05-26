#include "../Tests.h"
#include <vector>
#include <cmath>

#define USE_MATH

#ifdef USE_MATH
#include <Math/Matrix.h>

using namespace Utils;
using namespace Math;
#endif

void Test_Multiple_Reg();

bool Testing::nth_Poly()
{
	tensor_t<2, double> fT = new FuncMatrix<2, double>([](int i, int j) {
		return i*2 + (j+1);
	}, 2, 2);
	
	tensor_t<1, double> dT = new DataMatrix<1, double>();
	dT.setSize(0, 2);
	dT(0) = 0;
	dT(1) = 1;
	
	dout << "L: " << fT.toString() << std::endl;
	dout << "R: " << dT.toString() << std::endl;
	auto dfT = fT.contract(dT);
	std::cout << "Result: " << dfT.toString() << std::endl;
	
	
	
	
	typedef double N;
	
	
	
	tensor_t<1, N> realCoeffs = new DataMatrix<1, N>({2, 3, 10/2});
	dout << realCoeffs[0] << std::endl;
	auto realFunc = [=](auto in) -> decltype(in) {
		auto c1 = realCoeffs[0];
		auto c2 = realCoeffs[1];
		auto c3 = realCoeffs[2];
		
		return c1 + c2*in + c3*in*in;
	};
	
	
	std::vector<N> in = { 0, 1, 2 };
	
	std::vector<N> out(in.size());
	for (auto i = 0; i < in.size(); i++)
	{
		out[i] = realFunc(in[i]);
		dout << in[i] << " --> " << out[i] << std::endl;
	}
	
	
	auto n = in.size();
	assert_ex(in.size() == out.size());
	
	Math::tensor_t<2, N> M([=] (int i, int j)
	{
		
		auto ret = in[0];
		ret = 0;
		if (i+j > 0)
		{
		for (int k = 0; k < n; k++)
		{
			auto tmp = in[k];
			tmp = pow(in[k], i+j);
			ret += tmp;
		}
		}
		return ret;
	});
	
	auto solSize = realCoeffs.size(0);
	
	
	M.setSize(1, solSize);
	M(0, 0) = n;
	
	
	assert_ex(M(0, 0) == n);
	M.setSize(0, n);
	assert_ex(M(0, 0) == n);
	assert_ex(M(0)[0] == n);
	assert_ex(M[0][0] == n);
	
	
	
	dout << M.toString() << std::endl;
	
	
	
	Math::tensor_t<1, N> V([=] (int i)
	{
		auto ret = in[0];
		ret = 0;
		for (int k = 0; k < n; k++)
		{
			auto tmp = in[0];
			if (i >= 1)
			{
				tmp = in[k];
			}
			else
			{
				tmp = 1;
			}
			
			tmp = pow(tmp, i);
			tmp *= out[k];
			ret += tmp;
		}
		return ret;
	});
	V.setSize(n);
	dout << V.toString() << std::endl;
	
	auto possV = M.contract(realCoeffs);
	dout << possV.toString() << std::endl;
	assert_ex(possV == V);
	
	Test_Multiple_Reg();
	
	return true;
}

void Test_Multiple_Reg()
{
	dout << "\n\nTesting Multiple Regression..." << std::endl;
	typedef double N;
	
	tensor_t<1, N> coef = new DataMatrix<1, N>({1, 2, 3});
	
	auto realFunc = [=] (auto x, auto y) -> decltype(x) {
		return coef[0] + coef[1]*x + coef[2]*y;
	};
	
	tensor_t<2, N> in = new DataMatrix<2, N>({{0, 0}, {1, 0}, {0, 1}});
	
	assert_ex(in.size(1)+1 == coef.size(0));
	
	tensor_t<1, N> out = new DataMatrix<1, N>();
	out.setSize(0, in.size(0));
	for (auto i = 0; i < in.size(0); i++)
	{
		out(i) = realFunc(in[i][0], in[i][1]);
	}
	
	tensor_t<2, N> M([=] (auto i, auto j) -> N
	{
		if (j == 0)
		{
			return 1;
		}
		return in[i][j-1];
	}, in.size(0), in.size(1)+1);
	dout << M.toString() << std::endl;
	assert_ex(M.size(0) == in.size(0));
	assert_ex(M.size(1) == in.size(1) + 1);
	
	assert_ex(M.contract(coef) == out);
	//coef = M.T().contract(M).inv().contract(M.T()).contract(out)
	auto Mi = M.inv();
	auto Mi_out = Mi.contract(out);
	
	dout << "M inv: " << Mi.toString() << std::endl;
	dout << "out: " << out.toString() << std::endl;
	dout << "M^-1.out: " << Mi_out.toString() << std::endl;
	dout << "Coef: " << coef.toString() << std::endl;
	assert_ex(coef == Mi_out);
	
}