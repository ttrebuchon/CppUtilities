#pragma once

#include "Expression.h"
namespace Util
{
namespace Math
{
	class Var : public Expression
	{
		private:
		
		protected:
		
		public:
		
		virtual ~Var();
		
		
		virtual Exp_type::type type() const { return exp_type.Var; }
		
		virtual Expression* copy() const override;
		
	};
	
	
}
}