#include "../Tests.h"
#include <Math/tensor_t.h>

using namespace Utils;
using namespace Math;

bool Testing::Tensor_T()
{
	tensor_t<1, double> t;
	tensor_t<2, double> t2;
	assert_ex(t == NULL);
	//t = t * 2;
	//t *= 2;
	t = 4;
	//t.s();
	t2(1, 2) = 4;
	
	return true;
}