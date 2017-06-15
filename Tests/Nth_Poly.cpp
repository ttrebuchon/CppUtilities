#include "../Tests_Helpers.h"
#include <vector>
#include <cmath>

#define USE_MATH

#ifdef USE_MATH
#include <QUtils/Math/Matrix.h>

using namespace Utils;
using namespace Math;
#endif

tensor_t<1, double> EstimateFunc(std::function<double(double)>, int n, int extras);

std::function<double(double)> Polynomial(tensor_t<1, double> coefficients)
{
	std::function<double(double)> func = [] (double) { return 0; };
	
	for (int i = 0; i < coefficients.size(0); i++)
	{
		double c = coefficients(i);
		func = [c, i, func] (double x)
		{
			return func(x) + c*pow(x, i);
		};
	}
	return func;
}

void Test_Multiple_Reg();

bool nth_poly_run()
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
	dout << "Result: " << dfT.toString() << std::endl;
	
	
	
	
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
	
	
	
	dout << "Estimate for 4x^4 + 9x^2 + x + 16: " << EstimateFunc([](double x) { return 4*pow(x, 4) + 9*pow(x, 2) + x + 16; }, 5, 90).toString() << "\n" << std::endl;
	
	dout << "\n\nEstimate for 4x + 16: " << EstimateFunc([](double x) { return 4*x + 16; }, 10, 90).toString() << "\n\n\n" << std::endl;
	
	
	auto pseudoPopGrowth = [](int iterations) -> tensor_t<1, double> {
		
		tensor_t<1, double> data = new DataMatrix<1, double>();
		data.setSize(0, iterations);
		
		
		
		int pop[4] = {2, 4, 0, 0};
		
		
		for (int i = 0; i < iterations; i++)
		{
			data(i) = 0;
			for (int n = 0; n < 4; n++)
			{
				data(i) += pop[n];
			}
			
			int newGen = 0;
			for (int n = 1; n < 4; n++)
			{
				newGen += pop[n]/2;
			}
			
			for (int n = 3; n > 0; n--)
			{
				pop[n] = pop[n-1];
			}
			
			pop[0] = newGen;
		}
		
		assert_ex(data.size(0) != 0);
		return data;
		
	};
	
	auto popY = pseudoPopGrowth(50);
	dout << "popY calculated..." << std::endl;
	assert_ex(popY.size(0) != 0);
	tensor_t<2, double> popA = new DataMatrix<2, double>();
	popA.setSize(0, popY.size(0));
	popA.setSize(1, 10);
	assert_ex(popY.size(0) != 0);
	assert_ex(popA.size(0) != 0);
	assert_ex(popA.size(1) != 0);
	dout << "Filling popA..." << std::endl;
	for (int i = 0; i < popA.size(0); i++)
	{
		for (int n = 0; n < popA.size(1); n++)
		{
			popA(i, n) = pow(i, n);
		}
	}
	dout << "Calculating pop est..." << std::endl;
	auto popX = popA.inv().contract(popY);
	dout << popX.toString() << std::endl;
	auto popEst = Polynomial(popX);
	double err = 0;
	for (int i = 0; i < popY.size(0); i++)
	{
		err += pow((popY(i) - popEst(i)), 2);
	}
	dout << "R²: " << err << std::endl;
}



tensor_t<1, double> EstimateFunc(std::function<double(double)> func, int n, int extras)
{
	tensor_t<2, double> A = new DataMatrix<2, double>();
	
	A.setSize(0, n+1+extras);
	A.setSize(1, n+1);
	
	tensor_t<1, double> Y = new DataMatrix<1, double>();
	Y.setSize(0, n+1+extras);
	
	for (int i = 0; i < n+1+extras; i++)
	{
		for (int j = 0; j < n+1; j++)
		{
			A(i, j) = pow(i, j);
		}
		Y(i) = func(i);
	}
	auto X = A.inv().contract(Y);
	return X;
}