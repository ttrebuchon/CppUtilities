#include "../Tests_Helpers.h"

#include <QUtils/Types/HasMethod.h>
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


bool Test_Types()
{
	assert_ex((has_f1_method<H, std::string()>::value));
	assert_ex((has_f1_method<G, std::string()>::value));
	assert_ex((has_f2_method<G, std::string()>::value));
	assert_ex(!(has_f2_method<H, std::string()>::value));
	
	return true;
}