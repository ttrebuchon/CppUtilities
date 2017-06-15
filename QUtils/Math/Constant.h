#pragma once

#include "Expression.h"
namespace Util
{
namespace Math
{
	class Constant : public Expression
	{
		private:
		
		protected:
		
		public:
		
		virtual ~Constant();
		
		virtual Exp_type::type type() const { return exp_type.Constant; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
	};
	
	
}
}