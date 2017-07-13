#pragma once

#include "Operation.h"

#include <vector>
#include <tuple>

namespace QUtils
{
namespace Math
{
	class Multiplication : public Operation
	{
		private:
		
		protected:
		std::vector<const Expression*> operands;
		
		public:
		Multiplication(const Expression*, const Expression*);
		virtual ~Multiplication();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Expression* expand() const override;
		
		virtual Exp_type::type type() const { return exp_type.Multiplication; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
		friend class Division;
		friend class Exponent;
		
	};
	
	
}
}