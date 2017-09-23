#define SRCTEST2
#include <string>
#include <vector>
namespace TestNS
{
	namespace TestNS2
	{
		//Hello
		//World!
		//This is a
		//test!
		std::string foo()
		{
			return "Hello!\b,\nworld.\b!\tTest\vTest2\n\n\fTest3\a\a\a\n\\Testing!";
		}
		double numFoo()
		{
			return 1998777.000000;
		}
		 std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	}
}
