#include <Math/Num.h>


namespace Util
{
namespace Math
{
	Num::Num(long double n) : n(n)
	{
		
	}
	
	Num::~Num()
	{
		
	}
	
	String Num::toString() const
	{
		return std::to_string(n);
	}
	
	long double Num::value() const
	{
		return n;
	}
	
	Expression* Num::eval() const
	{
		return copy();
	}
	
	Expression* Num::copy() const
	{
		return new Num(n);
	}
}
}