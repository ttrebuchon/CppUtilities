#include <Math/Term.h>
#include <Math/Expression.h>

#include <Math/Exponent.h>
#include <Math/Multiplication.h>
#include <Math/Division.h>
#include <Math/Addition.h>
#include <Math/Subtraction.h>

#include <Math/Num.h>
#include <Math/Var.h>


namespace Util
{
namespace Math
{
	Term::Term(Expression* exp) : exp(exp)
	{
		
	}
	
	Term::Term(long double n) : exp(new Num(n))
	{
		
	}
	
	Term::Term(int i) : Term((long double)i)
	{
	}
	
	Term::Term(String vname) : exp(new Var(vname))
	{
		
	}
	
	Term::Term(const char* vname) : exp(new Var(vname))
	{
		
	}
	
	Term::Term(const char c) : exp(new Var(std::string() + c))
	{
		
	}
	
	Term::Term(const Term& t) : exp(t.exp->copy())
	{
		
	}
	
	Term::~Term()
	{
		delete exp;
	}
	
	String Term::toString() const
	{
		return exp->toString();
	}
	
	Term Term::eval() const
	{
		return Term(exp->eval());
	}
	
	
	Term& Term::operator=(const Term& t)
	{
		if (exp != NULL)
		{
			delete exp;
			exp = NULL;
		}
		
		exp = t.exp->copy();
		return *this;
	}
	
	Term& Term::operator=(const String s)
	{
		if (exp != NULL)
		{
			delete exp;
			exp = NULL;
		}
		
		exp = new Var(s);
		return *this;
	}
	
	Term& Term::operator=(const char* s)
	{
		return operator=(String(s));
	}
	
	
	
	
	Term Term::operator*(Term t) const
	{
		return Term((*exp)*t.exp);
	}
	
	Term Term::operator^(Term t) const
	{
		return Term((*exp)^t.exp);
	}
	
	Term Term::operator/(Term t) const
	{
		return Term((*exp)/t.exp);
	}
	
	Term Term::operator+(Term t) const
	{
		return Term((*exp)+t.exp);
	}
	
	Term Term::operator-(Term t) const
	{
		return Term((*exp)-t.exp);
	}
	
	
	//Non-Member Functions
	
	Term operator*(long double n, const Term& t)
	{
		return Term(n)*t;
	}
	
	Term operator^(long double n, const Term& t)
	{
		return Term(n)^t;
	}
	
	Term operator/(long double n, const Term& t)
	{
		return Term(n)/t;
	}
	
	Term operator+(long double n, const Term& t)
	{
		return Term(n)+t;
	}
	
	Term operator-(long double n, const Term& t)
	{
		return Term(n)-t;
	};
	
}
}