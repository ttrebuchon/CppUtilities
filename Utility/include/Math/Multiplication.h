#pragma once

#include "Operation.h"

#include <vector>

namespace Util
{
namespace Math
{
	class Multiplication : public Operation
	{
		private:
		
		protected:
		std::vector<Expression*> operands;
		
		public:
		Multiplication(const Expression*, const Expression*);
		virtual ~Multiplication();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Exp_type::type type() const { return exp_type.Multiplication; }
		
		virtual Expression* copy() const override;
		
	};
	
	
}
}