#include "Func/Func.h"
#include "../Tests.h"

void tfunc1()
{
	//std::cout << __func__ << std::endl;
}

int AddFunc(int a, int b)
{
	return a+b;
}

int SubFunc(int a, int b)
{
	return (a-b);
}

class TClass
{
	private:
	
	public:
	static int count;
	
	static void func()
	{
		count++;
	}
	
	void f2()
	{
		count--;
	}
};

int TClass::count = 0;

bool Testing::Func()
{
	using Utils::Func;
	using Utils::MemberFunc;
	
	
	Func<void> f;
	Func<int, int, int> adder;
	
	f = &tfunc1;
	f();
	adder = AddFunc;
	int a = 17, b = 248;
	//std::cout << "Sum of " << a << " and " << b << ": " << adder(a, b) << std::endl;
	assert_ex(adder(a, b) == (a+b));
	
	assert_ex(TClass::count == 0);
	
	Func<void> tF = TClass::func;
	
	tF();
	assert_ex(TClass::count == 1);
	
	adder = &SubFunc;
	//std::cout << "Difference of " << a << " and " << b << ": " << adder(a, b) << std::endl;
	assert_ex(adder(a, b) == (a-b));
	
	
	TClass c;
	Func<void>* tF2 = new MemberFunc<TClass, void>(&c, &TClass::f2);
	
	(*tF2)();
	assert_ex(TClass::count == 0);
	
	return true;
}