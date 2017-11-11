#include <QUtils/Iterable/Iterable.h>

#include "../Tests_Helpers.h"

#include <vector>

void basicTest();
void test1();

DEF_TEST(Iterable)
{
	basicTest();
	test1();
	return true;
}



void basicTest()
{
	std::vector<int> vec = {1, 2, 3, 4};
	vec.reserve(4);
	vec.shrink_to_fit();
	assert_ex(vec.capacity() == 4);
	QUtils::Iterable::IIterable<int> range(vec.begin(), vec.end());
	
	int i = 0;
	for (auto x : range)
	{
		assert_ex(x == ++i);
	}
	
	{
	
	QUtils::Iterable::IIterable<int>::iterator it1;
	assert_ex(it1 != range.begin());
	
	QUtils::Iterable::IIterable<int>::iterator it2(range.begin());
	assert_ex(it2 == range.begin());
	assert_ex(it1 != it2);
	
	
	assert_ex(*it2 == 1);
	*it2 = 0;
	assert_ex(*it2 == 0);
	assert_ex(vec[0] == 0);
	vec[0] = 1;
	assert_ex(*it2 == 1);
	assert_ex(vec[0] == 1);
	
	auto vec2 = range.toVector();
	assert_ex(vec == vec2);
	
	}
	
	QUtils::Iterable::IIterable<int> range2(vec);
	
	assert_ex(range.begin() == range2.begin());
	
	{
		auto vec2 = range2.toVector();
		assert_ex(vec2 == vec);
	}
	
	int* origBegin = &vec[0];
	
	{
		
		int* x = &vec[0];
		assert_ex(vec.capacity() == 4);
		vec.push_back(5);
		int* y = &vec[0];
		assert_ex(x != y);
	}
	
	{
		auto vec2 = range2.toVector();
		assert_ex(vec2 == vec);
	}
	
	std::vector<int> vec2 = {6, 7, 8, 9};
	vec2.shrink_to_fit();
	assert_ex(vec2.capacity() == 4);
	
	if (origBegin == &vec2[0])
	{
		auto vec3 = range.toVector();
		assert_ex(vec != vec3);
		i = 0;
		for (auto x : range)
		{
			assert_ex(x != ++i);
		}
	}
}

void test1()
{
	std::vector<int> vec = {0, 1, 2, 3, 4};
	using namespace QUtils::Iterable;
	IIterable<int> ran(vec);
	
	std::vector<int> vec2 = ran.toVector();
	std::list<int> list = ran.toList();
	
	
	int i;
	
	i = 0;
	for (auto& x : vec2)
	{
		assert_ex(vec[i++] == x);
	}
	
	i = 0;
	for (auto& x : list)
	{
		assert_ex(vec[i++] == x);
	}
}