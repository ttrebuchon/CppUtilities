#pragma once
#include <string>

namespace QUtils
{
namespace SQL
{
	class Clause
	{
		protected:
		const std::string lhs;
		const std::string op;
		const std::string rhs;
		
		public:
		
		Clause(const std::string, const std::string, const std::string);
		
		std::string toString() const;
		
		
		Clause operator&&(const Clause) const;
		Clause operator||(const Clause) const;
		Clause operator!() const;
	};
	
}
}