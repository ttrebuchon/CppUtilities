#include <Math/Exponent.h>

#include <Math/Num.h>
#include <Math/Multiplication.h>

#include <cmath>
#include <iostream>

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
	
	Expression* Exponent::expand() const
	{
		auto evaled = eval();
		if (evaled->type() != type())
		{
			return evaled;
		}
		
		auto e = ((Exponent*)evaled)->e;
		auto b = ((Exponent*)evaled)->b;
		
		
		if (e->type() == exp_type.Num)
		{
			Multiplication* exp = new Multiplication(b, b);
			long double e_value = ((Num*)e)->value();
			int i = 2;
			for (i = 2; i < (int)e_value; i++)
			{
				exp->operands.push_back(b->copy());
			}
			if ((int)e_value != e_value)
			{
			auto diff = new Num(e_value - i);
			exp->operands.push_back(new Exponent(b, diff));
			delete diff;
			}
			std::cout << "-->" << exp->toString() << std::endl;
			return exp;
			
		}
		return evaled;
		
		
	}
	
	Expression* Exponent::copy() const
	{
		return new Exponent(b, e);
	}
	
	bool Exponent::equals(const Expression* exp) const
	{
		bool result = false;
		auto ev = eval();
		auto e_exp = exp->eval();
		if (ev->type() != type())
		{
			result = ev->equals(e_exp);
			delete ev;
			delete e_exp;
			return result;
		}
		
		Exponent* ex = (Exponent*)ev;
		
		if (e_exp->type() == type())
		{
			Exponent* t = (Exponent*)e_exp;
			if (ex->b->equals(t->b) && ex->e->equals(t->e))
			{
				delete t;
				delete ev;
				return true;
			}
			
			throw NotImp();
		}
		
		return false;
		
	}
	
	bool Exponent::contains(const Expression* exp) const
	{
		throw NotImp();
	}
	
}
}