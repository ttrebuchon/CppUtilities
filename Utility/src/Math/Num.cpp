#include <Math/Num.h>
#include <iomanip>

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
		return ((std::stringstream)(std::stringstream() << std::setprecision(9) << n)).str();
		//return std::to_string(n);
	}
	
	long double Num::value() const
	{
		return n;
	}
	
	Expression* Num::eval() const
	{
		return copy();
	}
	
	Expression* Num::expand() const
	{
		return copy();
	}
	
	Expression* Num::copy() const
	{
		return new Num(n);
	}
	
	bool Num::equals(const Expression* e) const
	{
		if (e->type() == type())
		{
			return (value() == ((Num*)e)->value());
		}
		
		auto ee = e->eval();
		if (ee->type() == type())
		{
			long double n = ((Num*)ee)->value();
			delete ee;
			return (value() == n);
		}
		
		return false;
	}
	
	bool Num::contains(const Expression* exp) const
	{
		return equals(exp);
	}
}
}