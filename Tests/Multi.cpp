#include "../Tests_Helpers.h"

#include <QUtils/Multi/Multi.h>
#include <exception>
#include <type_traits>

void someFunc(int x)
{
	for (int i = 0; i < x; i++)
	{
		
	}
	dout << "someFunc(" << x << ")\n";
}

bool Test_Multi()
{
	auto F2 = [](auto x) -> auto
	{
		dout << "F2(" << x << ")\n";
		return 42;
	};
	std::thread t(someFunc, 4);
	std::thread t2(F2, 8);
	
	auto t2_2 = std::async(F2, 7);
	
	t2_2.wait();
	dout << "t2_2: " << t2_2.get() << "\n";
	t2.join();
	t.join();
	
	
	
	return true;
}