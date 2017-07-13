#include <QUtils/Math/Division.h>

#include <QUtils/Math/Num.h>
#include <QUtils/Math/Multiplication.h>


namespace QUtils
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
		std::vector<const Expression*> tops, bottoms, cancelled;
		auto exp_top = top->copy();//->eval();//expand();
		if (exp_top->type() == exp_type.Multiplication)
		{
			tops = ((Multiplication*)exp_top)->operands;
		}
		else
		{
			tops.push_back(exp_top);
		}
		
		auto exp_bot = bottom->copy();//->eval();//expand();
		
		if (exp_bot->type() == exp_type.Multiplication)
		{
			bottoms = ((Multiplication*)exp_bot)->operands;
		}
		else
		{
			bottoms.push_back(exp_bot);
		}
		
		for (int i = 0; i < tops.size(); i++)
		{
			for (int k = 0; k < bottoms.size(); k++)
			{
				if (tops[i]->equals(bottoms[k]))
				{
					cancelled.push_back(tops[i]);
					cancelled.push_back(bottoms[k]);
					tops.erase(tops.begin()+i);
					bottoms.erase(bottoms.begin()+k);
					i = 0;
					k = 0;
					break;
				}
			}
		}
		
		Expression* nBottom = nullptr;
		Expression* nTop = nullptr;
		if (bottoms.size() <= 0)
		{
			if (tops.size() <= 0)
			{
				delete exp_top;
				delete exp_bot;
				return new Num(1);
			}
			
			if (tops.size() == 1)
			{
				
				auto top0E = tops[0]->eval();
				delete exp_top;
				delete exp_bot;
				return top0E;
			}
			
			nTop = new Multiplication(tops[0], tops[1]);
			for (int i = 2; i < tops.size(); i++)
			{
				((Multiplication*)nTop)->operands.push_back(tops[i]->copy());
			}
			
			auto nTopE = nTop->eval();
			delete nTop;
			delete exp_top;
			delete exp_bot;
			return nTopE;
		}
		else
		{
			if (bottoms.size() == 1)
			{
				nBottom = bottoms[0]->eval();
			}
			else
			{
				nBottom = new Multiplication(bottoms[0], bottoms[1]);
				for (int i = 2; i < bottoms.size(); i++)
				{
					((Multiplication*)nBottom)->operands.push_back(bottoms[i]->copy());
				}
			}
			
			auto nBtmTmp = nBottom->eval();
			delete nBottom;
			nBottom = nBtmTmp;
		}
		
		if (tops.size() <= 0)
		{
			nTop = new Num(1);
		}
		else
		{
			if (tops.size() == 1)
			{
				nTop = tops[0]->eval();
			}
			else
			{
				nTop = new Multiplication(tops[0], tops[1]);
				for (int i = 2; i < tops.size(); i++)
				{
					((Multiplication*)nTop)->operands.push_back(tops[i]->copy());
				}
				auto nTopTmp = nTop->eval();
				delete nTop;
				nTop = nTopTmp;
			}
		}
		
		delete exp_top;
		delete exp_bot;
		
		
		
		
		
		
		
		
		auto t = nTop->eval();
		delete nTop;
		auto b = nBottom->eval();
		delete nBottom;
		
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
	
	Expression* Division::expand() const
	{
		auto t_expand = top->expand();
		auto b_expand = bottom->expand();
		auto exp = new Division(t_expand, b_expand);
		delete t_expand;
		delete b_expand;
		return exp;
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
	
	bool Division::equals(const Expression* exp) const
	{
		throw NotImp();
	}
	
	bool Division::contains(const Expression* exp) const
	{
		throw NotImp();
	}
	
}
}