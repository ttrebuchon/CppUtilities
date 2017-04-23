#include <Math/Exponent.h>

#include <Math/Num.h>

#include <cmath>

namespace Util
{
namespace Math
{
	Exponent::Exponent(const Expression* b, const Expression* e) : b(b->copy()), e(e->copy())
	{
		
	}
	
	Exponent::~Exponent()
	{
		delete b;
		delete e;
	}
	
	String Exponent::toString() const
	{
		String s;
		if (b->multiTerm())
		{
			s << "(" << b->toString() << ")";
		}
		else
		{
			s << b->toString();
		}
		
		s << "^";
		
		if (e->multiTerm())
		{
			s << "(" << e->toString() << ")";
		}
		else
		{
			s << e->toString();
		}
		
		return s;
	}
	
	Expression* Exponent::eval() const
	{
		auto be = b->eval();
		auto ee = e->eval();
		
		if (be->type() == exp_type.Num)
		{
			Num* bn = (Num*)be;
			if (bn->value() == 0 || bn->value() == 1)
			{
				delete ee;
				return bn;
			}
			
			if (ee->type() == exp_type.Num)
			{
				long double n = pow(bn->value(), ((Num*)ee)->value());
				delete bn;
				delete ee;
				return new Num(n);
			}
		}
		
		if (ee->type() == exp_type.Num)
		{
			Num* en = (Num*)ee;
			
			if (en->value() == 0)
			{
				delete en;
				delete be;
				return new Num(1);
			}
			
			if (en->value() == 1)
			{
				delete en;
				return be;
			}
		}
		
		auto e = new Exponent(be, ee);
		delete be;
		delete ee;
		return e;
	}
	
	Expression* Exponent::copy() const
	{
		return new Exponent(b, e);
	}
	
	bool Exponent::equals(const Expression* exp) const
	{
		throw NotImp();
	}
	
}
}