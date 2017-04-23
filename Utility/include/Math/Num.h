#pragma once

#include "Expression.h"
namespace Util
{
namespace Math
{
	class Num : public Expression
	{
		private:
		
		protected:
		long double n;
		
		public:
		Num(long double n);
		virtual ~Num();
		
		long double value() const;
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		bool multiTerm() const override { return false; }
		
		virtual Exp_type::type type() const { return exp_type.Num; }
		
		virtual Expression* copy() const override;
		
	};
	
	
}
}