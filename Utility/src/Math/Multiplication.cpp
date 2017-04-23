#include <Math/Multiplication.h>

#include <Math/Num.h>

namespace Util
{
namespace Math
{
	Multiplication::Multiplication(const Expression* e1, const Expression* e2) : operands()
	{
		if (e1->type() == type())
		{
			for (auto op : ((Multiplication*)e1)->operands)
			{
				operands.push_back(op->copy());
			}
		}
		else
		{
			operands.push_back(e1->copy());
		}
		
		if (e2->type() == type())
		{
			for (auto op : ((Multiplication*)e2)->operands)
			{
				operands.push_back(op->copy());
			}
		}
		else
		{
			operands.push_back(e2->copy());
		}
	}
	
	Multiplication::~Multiplication()
	{
		for (int i = 0; i < operands.size(); i++)
		{
			delete operands[i];
		}
		operands.clear();
	}
	
	String Multiplication::toString() const
	{
		bool first = true;
		String s;
		for (auto o : operands)
		{
			if (!first)
			{
				s << "*";
			}
			else
			{
				first = false;
			}
			if (o->multiTerm())
			{
				s << "(";
			}
			s << o->toString();
			if (o->multiTerm())
			{
				s << ")";
			}
		}
		return s;
	}
	
	Expression* Multiplication::eval() const
	{
		long double n = 1;
		std::vector<Expression*> ops;
		for (auto op : operands)
		{
			auto e = op->eval();
			if (e->type() == exp_type.Num)
			{
				n *= ((Num*)e)->value();
				delete e;
			}
			else
			{
				ops.push_back(e);
			}
		}
		
		if (n == 0)
		{
			for (auto op : ops)
			{
				delete op;
			}
			return new Num(0);
		}
		
		if (ops.size() > 0)
		{
			if (n != 1)
			{
				ops.push_back(new Num(n));
			}
			if (ops.size() == 1)
			{
				return ops[0];
			}
			Multiplication* m = new Multiplication(ops[0], ops[1]);
			delete ops[0];
			delete ops[1];
			for (int i = 2; i < ops.size(); i++)
			{
				m->operands.push_back(ops[i]);
			}
			return m;
		}
		
		
		return new Num(n);
	}
		
	Expression* Multiplication::copy() const
	{
		auto c = new Multiplication(operands[0], operands[1]);
		for (int i = 2; i < operands.size(); i++)
		{
			c->operands.push_back(operands[i]->copy());
		}
		return c;
	}
	
}
}