#include <QUtils/SQL/SQLClause.h>


namespace QUtils
{
namespace SQL
{
	SQLClause::SQLClause(const std::string lhs, const std::string op, const std::string rhs) : lhs(lhs), op(op), rhs(rhs)
	{
		
	}
	
	std::string SQLClause::toString() const
	{
		return lhs + op + rhs;
	}
	
	
	
	SQLClause SQLClause::operator&&(const SQLClause cl) const
	{
		return SQLClause("(" + lhs + op + rhs + ")", " AND ", "(" + cl.lhs + cl.op + cl.rhs + ")");
	}
	
	SQLClause SQLClause::operator||(const SQLClause cl) const
	{
		return SQLClause("(" + lhs + op + rhs + ")", " OR ", "(" + cl.lhs + cl.op + cl.rhs + ")");
	}
	
	SQLClause SQLClause::operator!() const
	{
		return SQLClause(lhs, " NOT " + op + " ", rhs);
	}
}
}