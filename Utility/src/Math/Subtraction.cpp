#include <Math/Subtraction.h>

#include <Math/Addition.h>
#include <Math/Num.h>

namespace Util
{
namespace Math
{
	Subtraction::Subtraction(const Expression* l, const Expression* r) : left(l->copy()), right()
	{
		if (r->type() == exp_type.Addition)
		{
			for (auto op : ((Addition*)r)->operands)
			{
				right.push_back(op->copy());
			}
		}
	}
	
	Subtraction::~Subtraction()
	{
		delete left;
		
		for (auto op : right)
		{
			delete op;
		}
		right.clear();
	}
	
	String Subtraction::toString() const
	{
		String s;
		
		if (left->multiTerm())
		{
			s << "(";
		}
		s << left->toString();
		if (left->multiTerm())
		{
			s << ")";
		}
		
		
		for (auto o : right)
		{
			s << " - ";
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
	
	Expression* Subtraction::eval() const
	{
		long double n = 0;
		std::vector<Expression*> ops;
		for (auto op : right)
		{
			auto e = op->eval();
			if (e->type() == exp_type.Num)
			{
				n += ((Num*)e)->value();
				delete e;
			}
			else
			{
				ops.push_back(e);
			}
		}
		
		Expression* l = left->eval();
		Expression* nL = NULL;
		
		if (l->type() != exp_type.Num)
		{
			nL = l;
		}
		
		if (ops.size() > 0)
		{
			if (n != 0)
			{
				if (nL != NULL)
				{
					ops.push_back(new Num(n));
				}
				else
				{
					auto tmpL = (Num*)nL;
					nL = new Num(tmpL->value() - n);
					delete tmpL;
				}
			}
			else
			{
				nL = l;
			}
			/*if (ops.size() == 1)
			{
				auto ret = new Subtraction(nL, ops[0]);
				delete nL;
				delete ops[0];
				return ret;
			}*/
			Subtraction* s = new Subtraction(nL, ops[0]);
			delete ops[0];
			for (int i = 1; i < ops.size(); i++)
			{
				s->right.push_back(ops[i]);
			}
			return s;
		}
		return nL;
	}
	
	Expression* Subtraction::copy() const
	{
		if (right.size() <= 0)
		{
			return left->copy();
		}
		auto s = new Subtraction(left, right[0]->copy());
		for (int i = 1; i < right.size(); i++)
		{
			s->right.push_back(right[i]->copy());
		}
		return s;
	}
}
}