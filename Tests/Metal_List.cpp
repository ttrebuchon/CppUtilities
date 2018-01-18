#include "../Tests_Helpers.h"
#include <QUtils/BareMetal/List.h>

using namespace QUtils::Metal;


DEF_TEST(Metal_List)
{
	List<int> l1;
	l1.push_back(1);
	l1.push_front(0);
	
	
	{
		for (auto it = l1.begin(); it != l1.end(); ++it)
		{
			dout << *it << std::endl;
		}
		int i = 0;
		for (const auto& n : l1)
		{
			assert_ex(n == i++);
		}
		
		assert_ex(i == 2);
		assert_ex(l1.size() == 2);
	}
	
	::operator new(100);
	assert_ex(metal_build_test() == 0);
	
	return true;
}