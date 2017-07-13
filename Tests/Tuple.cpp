#include "../Tests_Helpers.h"

#include <QUtils/Tuple/Tuple.h>

using QUtils::Tuple;



bool Test_Tuple()
{
	Tuple<int, char> t1(1, 'a');
	
	assert_ex(t1.get<0>() == 1);
	assert_ex(t1.get<1>() == 'a');
	auto t2 = t1;
	t1.get<1>() = 'b';
	assert_ex(t1.get<0>() == 1);
	assert_ex(t1.get<1>() == 'b');
	assert_ex(t2.get<0>() == 1);
	assert_ex(t2.get<1>() == 'a');
	
	auto t3 = t2.concat(t1);
	assert_ex(t3.get<0>() == 1);
	assert_ex(t3.get<1>() == 'a');
	assert_ex(t3.get<2>() == 1);
	assert_ex(t3.get<3>() == 'b');
	
	Tuple<int, char, int, char, double, double> t4 = t3.append<double, double>(1, 2);
	assert_ex(t4.get<4>() == 1);
	assert_ex(t4.get<5>() == 2);
	
	t4.get<5>() /= 4;
	assert_ex(t4.get<5>() == 0.5);
	
	
	
	auto l1 = [] (int i, char c)
	{
		assert_ex(i == 1);
		assert_ex(c == 'a');
	};
	t1.get<1>() = 'a';
	assert_ex(t1.get<0>() == 1);
	assert_ex(t1.get<1>() == 'a');
	t1.useAsArgs(l1);
	
	assert_ex(t1 == t3.takeFront<2>());
	
	Tuple<double, double> t5 = t4.takeBack<2>();
	
	assert_ex(t5.get<0>() == 1);
	assert_ex(t5.get<1>() == 0.5);
	
	return true;
}