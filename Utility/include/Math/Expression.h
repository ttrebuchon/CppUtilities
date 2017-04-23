#pragma once

#include <String/String.h>

#include "TypeEnum.h"


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
		virtual ~Expression() {}
		
		
		virtual String toString() const = 0;
		virtual Expression* eval() const = 0;
		
		virtual bool multiTerm() const = 0;
		virtual Exp_type::type type() const = 0;
		
		virtual Expression* copy() const = 0;
		
		Multiplication* operator*(Expression*) const;
		Exponent* operator^(Expression*) const;
		Division* operator/(Expression*) const;
		Addition* operator+(Expression*) const;
		Subtraction* operator-(Expression*) const;
		
	};
	
	
}
}