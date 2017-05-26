#include "../Tests.h"
#include <Math/tensor_t.h>
#include <initializer_list>

using namespace Utils;
using namespace Math;

bool Testing::Tensor_T()
{
	tensor_t<1, double> t;
	
	
	tensor_t<2, double> t2 = new DataMatrix<2, double>( {{1, 1}, {1, 1}});
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
	t2 = { tensor_t<1, double>([](int i) -> double { return i; }, 2), {2, 3}};
	
	
	
	assert_ex(t2.det() == -2);
	
	t2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	assert_ex(t2.det() == 0);
	
	
	tensor_t<2, double> invTest = new FuncMatrix<2, double>([](int i, int j) {
		return 2*i + (j+1);
	}, 2, 2);
	dout << "invTest: " << invTest.toString() << std::endl;
	auto invTesti = invTest.inv();
	dout << "invTesti: " << invTesti.toString() << std::endl;
	dout << "invTest.invTesti: " << invTest.contract(invTesti).toString() << std::endl;
	
	return true;
}