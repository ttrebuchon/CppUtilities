#pragma once

#include "Expression.h"
namespace Util
{
namespace Math
{
	class Var : public Expression
	{
		private:
		String name;
		
		protected:
		
		public:
		Var(String);
		virtual ~Var();
		
		
		virtual String toString() const override;
		
		virtual Exp_type::type type() const { return exp_type.Var; }
		
		virtual Expression* eval() const;
		
		virtual Expression* expand() const override;
		
		bool multiTerm() const override { return false; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
	};
	
	
}
}