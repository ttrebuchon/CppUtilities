#include <QUtils/SQL/Clause.h>


namespace QUtils
{
namespace SQL
{
	Clause::Clause(const std::string lhs, const std::string op, const std::string rhs) : lhs(lhs), op(op), rhs(rhs)
	{
		
	}
	
	std::string Clause::toString() const
	{
		return lhs + op + rhs;
	}
	
	
	
	Clause Clause::operator&&(const Clause cl) const
	{
		return Clause("(" + lhs + op + rhs + ")", " AND ", "(" + cl.lhs + cl.op + cl.rhs + ")");
	}
	
	Clause Clause::operator||(const Clause cl) const
	{
		return Clause("(" + lhs + op + rhs + ")", " OR ", "(" + cl.lhs + cl.op + cl.rhs + ")");
	}
	
	Clause Clause::operator!() const
	{
		return Clause(lhs, " NOT " + op + " ", rhs);
	}
}
}