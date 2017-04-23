#include "../Tests.h"


#include <Math/Math.h>

using namespace Util;
using namespace Math;

#define go
bool Testing::Math()
{
	#ifdef go
	Term t(4);
	
	Term t2(4);
	Term t3 = t + t2;
	Term t4 = t3.eval();
	#endif
	
	dout << t3.toString() << std::endl;
	dout << t4.toString() << std::endl;
	
	dout << t.exp << " - " << t.exp->type() << std::endl;
	dout << t2.exp << " - " << t2.exp->type() << std::endl;
	dout << t3.exp << " - " << t3.exp->type() << std::endl;
	for (auto exp : ((Addition*)t3.exp)->operands)
	{
		dout << "\t" << exp << " - " << exp->type() << std::endl;
	}
	dout << t4.exp << " - " << t4.exp->type() << std::endl;
	
	return true;
}