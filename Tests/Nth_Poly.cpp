#include "../Tests.h"
#include <vector>
#include <cmath>

#define USE_MATH

#ifdef USE_MATH
#include <Math/Matrix.h>

using namespace Utils;
using namespace Math;
#endif

bool Testing::nth_Poly()
{
	typedef double N;
	
	
	
	matrix_t<1, N> realCoeffs;
	realCoeffs = new DataMatrix<1, N>({0, 0, 10/2});
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
	
	
	
	//...Set in and out
	
	auto n = in.size();
	assert_ex(in.size() == out.size());
	
	Math::matrix_t<2, N> M([=] (int i, int j)
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
	
	auto solSize = realCoeffs.size()[0];
	
	
	M.setSize(1, solSize);
	M(0, 0) = n;
	
	
	assert_ex(M(0, 0) == n);
	M.setSize(0, n);
	assert_ex(M(0, 0) == n);
	assert_ex(M(0)[0] == n);
	assert_ex(M[0][0] == n);
	
	
	
	dout << M.toString() << std::endl;
	
	
	
	Math::matrix_t<1, N> V([=] (int i)
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
	
	return true;
}