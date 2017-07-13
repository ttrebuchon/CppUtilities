#include <QUtils/Math/Num.h>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace QUtils
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
		std::stringstream ss;
		ss << std::setprecision(9) << n;
		return ss.str();
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