#include "../Tests.h"
#include <Math/tensor_t.h>
#include <initializer_list>

using namespace Utils;
using namespace Math;

bool Testing::Tensor_T()
{
	tensor_t<1, double> t;
	
	
	tensor_t<2, double> t2 = new DataMatrix<2, double>( {{1, 1}, {1, 1}});
	dout << "t2 set" << std::endl;
	assert_ex(t == NULL);
	//t = t * 2;
	//t *= 2;
	t = 4;
	//t.s();
	t2(1, 1) = 4;
	dout << t2.toString() << std::endl;
	t2(1) = {4, 5};
	dout << t2.toString() << std::endl;
	t2 = {{1, 2}, {3, 4}};
	dout << t2.toString() << std::endl;
	t2 = { t2[0], t2[1] };
	dout << t2.toString() << std::endl;
	t2 = { tensor_t<1, double>([](int i) -> double { return i; }), {2, 3}};
	dout << t2.toString() << std::endl;
	
	for (int i = 0; i < 2; i++)
	{
		dout << t2.size(i) << ", ";
	}
	dout << std::endl;
	
	
	dout << t2.det() << std::endl;
	
	//auto f = new FuncMatrix<1, double>([](int i) { return 0; });
	//tensor_t<1, double> t3 = std::make_shared<FuncMatrix<1, double>>([](int i) { return 0; });
	return true;
}