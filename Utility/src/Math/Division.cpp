#include <Math/Division.h>

#include <Math/Num.h>


namespace Util
{
namespace Math
{
	Division::Division(const Expression* e1, const Expression* e2) : top(e1->copy()), bottom(e2->copy())
	{
		
	}
	
	Division::~Division()
	{
		delete top;
		delete bottom;
	}
	
	Expression* Division::eval() const
	{
		auto t = top->eval();
		auto b = bottom->eval();
		
		if ((t->type() == b->type()) && t->type() == exp_type.Num)
		{
			long double n;
			n = ((Num*)t)->value();
			n /= ((Num*)b)->value();
			delete t;
			delete b;
			return new Num(n);
		}
		
		if (b->type() == exp_type.Num)
		{
			if (((Num*)b)->value() == 1)
			{
				delete b;
				return t;
			}
		}
		
		auto d = new Division(t, b);
		delete t;
		delete b;
		return d;
	}
	
	String Division::toString() const
	{
		String s;
		if (top->multiTerm())
		{
			s << "(";
		}
		s << top->toString();
		if (top->multiTerm())
		{
			s << ")";
		}
		
		s << "/";
		
		if (bottom->multiTerm())
		{
			s << "(";
		}
		s << bottom->toString();
		if (bottom->multiTerm())
		{
			s << ")";
		}
		
		return s;
	}
	
	Expression* Division::copy() const
	{
		return new Division(top, bottom);
	}
	
}
}