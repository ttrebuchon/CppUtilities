#include <Math/Var.h>


namespace Util
{
namespace Math
{
	Var::Var(String s) : name(s)
	{
		
	}
	
	Var::~Var()
	{
		
	}
	
	String Var::toString() const
	{
		return name;
	}
	
	Expression* Var::eval() const
	{
		return copy();
	}
	
	Expression* Var::copy() const
	{
		return new Var(name);
	}
		
	bool Var::equals(const Expression* exp) const
	{
		auto evaled = exp->eval();
		if (evaled->type() == type())
		{
			if (((Var*)evaled)->name == name)
			{
				delete evaled;
				return true;
			}
		}
		delete evaled;
		return false;
	}
	
	
}
}