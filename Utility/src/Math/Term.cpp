#include <Math/Term.h>
#include <Math/Expression.h>

#include <Math/Exponent.h>
#include <Math/Multiplication.h>
#include <Math/Division.h>
#include <Math/Addition.h>
#include <Math/Subtraction.h>

#include <Math/Num.h>


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
	
	
	
	/*
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
	}*/
	
	Term Term::operator+(Term t) const
	{
		return Term((*exp)+t.exp);
	}
	/*
	Term Term::operator-(Term t) const
	{
		return Term((*exp)-t.exp);
	}*/
	
	
}
}