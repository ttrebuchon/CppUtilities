#include "../Tests.h"
#include <Rules/Rules.h>

using namespace Utils::Rules;

template <std::string* ptr>
struct Ptr
{
	
};

bool Testing::RulesEngine()
{
	auto eng = new Engine();
	
	
	dout << eng << std::endl;
	
	eng->assertf<std::string>("male", "tim");
	eng->assertf<std::string>("male", "bill");
	eng->assertf<std::string, int>("age", "tim", 4);
	
	auto maleCheck = eng->checkf<std::string>("male");
	castor::lref<std::string> person;
	auto maleRel = maleCheck(person);
	while (maleRel())
	{
		dout << *person << " is a male" << std::endl;
	}
	
	auto ageCheck = eng->checkf<std::string, int>("age");
	person.reset();
	castor::lref<int> age;
	auto ageRel = ageCheck(person, age);
	while (ageRel())
	{
		dout << *person << " is " << *age << std::endl;
	}
	
	eng->assertf<std::string, int>("age", "bill", 20);
	
	ageCheck = eng->checkf<std::string, int>("age");
	person.reset();
	age.reset();
	ageRel = ageCheck(person, age);
	while (ageRel())
	{
		dout << *person << " is " << *age << std::endl;
	}
	
	
	delete eng;
	return true;
}