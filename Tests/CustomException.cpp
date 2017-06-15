#include "../Tests_Helpers.h"
#include "QUtils/Exception/Exception.h"

#include <sstream>

UTIL_CUSTOM_EXCEPTION(SomeException, SomeMsg);

UTIL_CUSTOM_EXCEPTION(TestException, TestMessage);

bool Test_CustomException()
{
	try
	{
		throw SomeException();
	}
	catch (std::exception& e)
	{
		dout << "Caught Exception: " << e.what() << std::endl;
		assert_ex(std::string("SomeMsg") == e.what());
	}
	
	try
	{
		throw TestException();
	}
	catch (std::exception& e)
	{
		assert_ex(std::string("TestMessage") == e.what());
	}
	
	return true;
}