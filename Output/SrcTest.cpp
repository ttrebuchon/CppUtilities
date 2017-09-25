#include <sstream>
#define TESTNS_DEFINED
namespace TestNS
{
	std::string helloWorld()
	{
		std::stringstream ss;
		ss  << "Hello,\n world!\n" << "4.5\n";
		return ss.str();
	}
}
