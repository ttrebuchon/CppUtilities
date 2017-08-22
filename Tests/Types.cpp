#include "../Tests_Helpers.h"

#include <QUtils/Types/Types.h>
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
	
	
	
	{
		typedef std::tuple<int, char, int, double, char> types;
		
		auto max = std::max({sizeof(int), sizeof(char), sizeof(int), sizeof(double), sizeof(char)});
		auto min = std::min({sizeof(int), sizeof(char), sizeof(int), sizeof(double), sizeof(char)});
		
		dout << QUtils::Types::PrintTypes<typename QUtils::Types::TypeSizes<types>::type>() << "\n";
		assert_ex((std::is_same<typename QUtils::Types::TypeSizes<types>::type, QUtils::Types::Sequence<sizeof(int), sizeof(char), sizeof(int), sizeof(double), sizeof(char)>>::value));
		assert_ex(QUtils::Types::MaxTypeSize<types>::Max == max);
		assert_ex(QUtils::Types::MaxTypeSize<types>::value == max);
		
		assert_ex(QUtils::Types::MinTypeSize<types>::Min == min);
		assert_ex(QUtils::Types::MinTypeSize<types>::value == min);
	}
	
	{
		//dout << sizeof(QUtils::Types::TypeWithSize<1>) << "\n";
		assert_ex(sizeof(QUtils::Types::TypeWithSize<1>) == 1);
		assert_ex(sizeof(QUtils::Types::TypeWithSize<2>) == 2);
		assert_ex(sizeof(QUtils::Types::TypeWithSize<3>) == 3);
		assert_ex(sizeof(QUtils::Types::TypeWithSize<4>) == 4);
		
		#define CHECK_SIZE(x) assert_ex(sizeof(QUtils::Types::TypeWithSize<x>) == x)
		
		CHECK_SIZE(5);
		CHECK_SIZE(6);
		CHECK_SIZE(7);
		CHECK_SIZE(8);
		CHECK_SIZE(9);
		CHECK_SIZE(10);
		
		CHECK_SIZE(64);
		CHECK_SIZE(128);
		CHECK_SIZE(256);
		CHECK_SIZE(512);
		CHECK_SIZE(1024);
		
		
		CHECK_SIZE(2048);
		CHECK_SIZE(3072);
		CHECK_SIZE(4096);
		
		CHECK_SIZE(1024*1024);
		
		CHECK_SIZE(1024*1024*1024);
		
		
	}
	
	return true;
}