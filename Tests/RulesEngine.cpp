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
	
	dout << "Testing many facts..." << std::endl;
	for (int i = 0; i < 1000; i++)
	{
		eng->assertf<std::string>((i % 2 == 0 ? "male" : "female"), std::to_string(i));
	}
	dout << "Added..." << std::endl;
	person.reset();
	auto males = eng->checkf<std::string>("male")(person);
	int result = 0;
	while (males())
	{
		if ((result %= 100) == 0)
		{
		dout << *person << " is a male" << std::endl;
		}
		result++;
	}
	
	eng->rule<std::string, std::string>("gender", [](const Engine* eng, auto p, auto g)
	{
		return (eng->checkf<std::string>("male")(p) && castor::eq(g, "male")) || (eng->checkf<std::string>("female")(p) && castor::eq(g, "female"));
	});
	
	
	castor::lref<std::string> gender;
	person.reset();
	auto genders = eng->checkf<std::string, std::string>("gender")(person, gender);
	result = 0;
	while (genders())
	{
		if ((result %= 100) == 0)
		{
		dout << *person << " is a " << *gender << std::endl;
		}
		result++;
	}
	
	
	
	delete eng;
	
	return true;
}