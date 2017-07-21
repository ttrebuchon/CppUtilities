#include "../Tests_Helpers.h"

#include <QUtils/Types/HasMethod.h>
#include <QUtils/Types/Functions.h>
#include <string>
class H
{
	public:
	virtual std::string f1() const
	{
		return "H_f1";
	}
};

class G : public H
{
	public:
	/*virtual std::string f1() const override
	{
		return "G_f1";
	}*/
	
	auto f2() const
	{
		return f1();
	}
};

QUTILS_HASMETHOD(f1);
QUTILS_HASMETHOD(f2);



class Invokeable
{
	private:
		
	public:
		
	template <class Arg>
	std::string operator()(Arg arg)
	{
		std::stringstream ss;
		ss << arg;
		return ss.str();
	}
	
	std::string operator()()
	{
		return "void";
	}
};



bool Test_Types()
{
	assert_ex((has_f1_method<H, std::string()>::value));
	assert_ex((has_f1_method<G, std::string()>::value));
	assert_ex((has_f2_method<G, std::string()>::value));
	assert_ex(!(has_f2_method<H, std::string()>::value));
	
	
	
	{
		auto lam = []()->int { return 4; };
		assert_ex((QUtils::Types::CallWithOptional<decltype(lam), int, int>::call(lam, 3, 2) == 4));
		
		
		auto lam2 = [](int x)->int { return x; };
		assert_ex((QUtils::Types::CallWithOptional<decltype(lam2), int>::call(lam2, 3) == 3));
		
		auto lam3 = [](int x, int y)->int { return x+y; };
		assert_ex((QUtils::Types::CallWithOptional<decltype(lam3), int, int>::call(lam3, 3, 2) == 5));
		
		
		
		assert_ex((QUtils::Types::Helpers::CanCallWith<QUtils::Types::Helpers::CallerTypesHolder<decltype(lam3), int, int>>::type::value));
		
		
		
		
		Invokeable inv;
		assert_ex((QUtils::Types::CallWithOptional<Invokeable, int, int>::call(inv, 3, 4) == "void"));
		
		assert_ex((QUtils::Types::CallWithOptional<Invokeable>::call(inv) == "void"));
		
	}
	
	return true;
}