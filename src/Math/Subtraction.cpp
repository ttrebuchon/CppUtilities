#include <QUtils/Math/Subtraction.h>

#include <QUtils/Math/Addition.h>
#include <QUtils/Math/Num.h>

#include <iostream>
using std::cout;
using std::endl;

namespace QUtils
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
		else
		{
			right.push_back(r->copy());
		}
	}
	
	Subtraction::~Subtraction()
	{
		delete left;
		
		for (auto op : right)
		{
			delete op;
		}
		//right.clear();
	}
	
	String Subtraction::toString() const
	{
		String s;
		
		if (left->multiTerm())
		{
			//s << "(";
		}
		s << left->toString();
		if (left->multiTerm())
		{
			//s << ")";
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
		
		
		
		if (nL == NULL)
		{
			nL = new Num(((Num*)l)->value() - n);
			delete l;
		}
		return nL;
	}
	
	Expression* Subtraction::expand() const
	{
		auto left_expand = left->expand();
		auto right0_expand = right[0]->expand();
		
		auto exp = new Subtraction(left_expand, right0_expand);
		delete left_expand;
		delete right0_expand;
		
		for (int i = 1; i < right.size(); i++)
		{
			exp->right.push_back(right[i]->expand());
		}
		
		return exp;
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
	
	bool Subtraction::equals(const Expression* exp) const
	{
		throw NotImp();
	}
	
	bool Subtraction::contains(const Expression* exp) const
	{
		throw NotImp();
	}
}
}