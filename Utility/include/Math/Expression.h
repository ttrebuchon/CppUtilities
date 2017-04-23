#pragma once

#include <String/String.h>

#include "TypeEnum.h"

#include <Exception/NotImplemented.h>

#include <vector>
#include <tuple>

namespace Util
{
namespace Math
{
	class Multiplication;
	class Exponent;
	class Division;
	class Addition;
	class Subtraction;
	
	class Expression
	{
		private:
		
		protected:
		
		public:
		#ifdef DEBUG
		#define ALIVE_COUNTER
		static int& alive() { static int a = 0; return a; }
		Expression() { alive()++; }
		#endif
		virtual ~Expression() {
			#ifdef DEBUG
			alive()--;
			#endif
			}
		
		
		virtual String toString() const = 0;
		virtual Expression* eval() const = 0;
		
		virtual bool multiTerm() const = 0;
		virtual Exp_type::type type() const = 0;
		
		virtual Expression* copy() const = 0;
		
		virtual bool equals(const Expression*) const = 0;
		
		Multiplication* operator*(Expression*) const;
		Exponent* operator^(Expression*) const;
		Division* operator/(Expression*) const;
		Addition* operator+(Expression*) const;
		Subtraction* operator-(Expression*) const;
		
	};
	
	std::vector<std::tuple<Expression*, int>> group(std::vector<Expression*>&);
	
	
}
}