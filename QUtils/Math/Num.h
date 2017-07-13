#pragma once

#include "Expression.h"
namespace QUtils
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
		
		virtual Expression* expand() const override;
		
		bool multiTerm() const override { return false; }
		
		virtual Exp_type::type type() const { return exp_type.Num; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
	};
	
	
}
}