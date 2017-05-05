#include <Math/Multiplication.h>

#include <Math/Num.h>
#include <Math/Exponent.h>
#include <Math/Division.h>

#include <iostream>

namespace Util
{
namespace Math
{
	Multiplication::Multiplication(const Expression* e1, const Expression* e2) : operands()
	{
		if (e1->multiTerm() && !e2->multiTerm())
		{
			std::swap(e1, e2);
		}
		
		if (e2->type() == exp_type.Num && e1->type() != exp_type.Num)
		{
			std::swap(e1, e2);
		}
		
		
		
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
		std::vector<Division*> divOps;
		std::vector<int> divIndexes;
		for (int i = 0; i < operands.size(); i++)
		{
			if (operands[i]->type() == exp_type.Division)
			{
				divIndexes.push_back(i);
				divOps.push_back((Division*)operands[i]);
			}
		}
		if (divOps.size() > 0)
		{
			//TODO
			std::vector<const Expression*> tops, bottoms;
			for (Division* div : divOps)
			{
				tops.push_back(div->top);
				bottoms.push_back(div->bottom);
			}
			
			for (int i = 0; i < operands.size(); i++)
			{
				if (std::find(divIndexes.begin(), divIndexes.end(), i) != divIndexes.end())//contains(i))
				{
					continue;
				}
				tops.push_back(operands[i]);
			}
			Multiplication* nTop = new Multiplication(tops[0], tops[1]);
			for (int i = 2; i < tops.size(); i++)
			{
				nTop->operands.push_back(tops[i]->copy());
			}
			
			Expression* nBottom = NULL;
			
			//TODO
			if (bottoms.size() == 1)
			{
				nBottom = bottoms[0]->copy();
			}
			else
			{
				nBottom = new Multiplication(bottoms[0], bottoms[1]);
				auto mnBottom = (Multiplication*)nBottom;
				for (auto i = 2; i < bottoms.size(); i++)
				{
					mnBottom->operands.push_back(bottoms[i]->copy());
				}
			}
			
			auto nDiv = new Division(nTop, nBottom);
			delete nTop;
			delete nBottom;
			
			auto nDiv_eval = nDiv->eval();
			delete nDiv;
			return nDiv_eval;
			
		}
		
		
		
		
		
		
		
		
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
		
		auto v = group(ops);
		for (auto t : v)
		{
			if (std::get<1>(t) == 1)
			{
				ops.push_back(std::get<0>(t));
			}
			else
			{
				Num* co = new Num(std::get<1>(t));
				ops.push_back(new Exponent(std::get<0>(t), co));
				delete co;
				delete std::get<0>(t);
			}
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
	
	Expression* Multiplication::expand() const
	{
		auto ex1 = operands[0]->expand();
		auto ex2 = operands[1]->expand();
		auto exp = new Multiplication(ex1, ex2);
		delete ex1;
		delete ex2;
		
		for (int i = 2; i < operands.size(); i++)
		{
			exp->operands.push_back(operands[i]->expand());
		}
		
		return exp;
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
	
	bool Multiplication::equals(const Expression* exp) const
	{
		throw NotImp();
	}
	
	bool Multiplication::contains(const Expression* exp) const
	{
		throw NotImp();
	}
	
}
}