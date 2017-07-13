#include <QUtils/Math/Expression.h>
#include <QUtils/Math/Exponent.h>
#include <QUtils/Math/Multiplication.h>
#include <QUtils/Math/Division.h>
#include <QUtils/Math/Addition.h>
#include <QUtils/Math/Subtraction.h>


namespace QUtils
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
	
	
	
	
	
	std::vector<std::tuple<Expression*, int>> group(std::vector<Expression*>& vec)
	{
		std::vector<std::tuple<Expression*, int>> v;
		
		for (auto it = vec.begin(); it != vec.end();)
		{
			int n = 0;
			for (auto s = it+1; s != vec.end(); ++s)
			{
				if ((*it)->equals(*s))
				{
					n++;
					--s;
					delete (*(s+1));
					vec.erase(s+1);
				}
			}
			++n;
			v.emplace_back(*it, n);
			vec.erase(it);
			
			it = vec.begin();
		}
		
		return v;
	}
	
	
	
	
}
}