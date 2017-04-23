#include <Math/Expression.h>
#include <Math/Exponent.h>
#include <Math/Multiplication.h>
#include <Math/Division.h>
#include <Math/Addition.h>
#include <Math/Subtraction.h>


namespace Util
{
namespace Math
{
	Multiplication* Expression::operator*(Expression* e) const
	{
		return new Multiplication(this, e);
	}
	
	Exponent* Expression::operator^(Expression* e) const
	{
		return new Exponent(this, e);
	}
	
	Division* Expression::operator/(Expression* e) const
	{
		return new Division(this, e);
	}
	
	Addition* Expression::operator+(Expression* e) const
	{
		return new Addition(this, e);
	}
	
	Subtraction* Expression::operator-(Expression* e) const
	{
		return new Subtraction(this, e);
	}
	
	
	
	
}
}