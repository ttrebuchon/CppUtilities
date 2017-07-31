#pragma once
#include <string>

namespace QUtils
{
namespace SQL
{
	class SQLClause
	{
		protected:
		const std::string lhs;
		const std::string op;
		const std::string rhs;
		
		public:
		
		SQLClause(const std::string, const std::string, const std::string);
		
		std::string toString() const;
		
		
		SQLClause operator&&(const SQLClause) const;
		SQLClause operator||(const SQLClause) const;
		SQLClause operator!() const;
	};
	
}
}