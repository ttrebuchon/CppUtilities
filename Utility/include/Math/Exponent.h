#pragma once

#include "Operation.h"
namespace Util
{
namespace Math
{
	class Exponent : public Operation
	{
		private:
		const Expression* b;
		const Expression* e;
		
		protected:
		
		public:
		Exponent(const Expression*, const Expression*);
		virtual ~Exponent();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Expression* expand() const override;
		
		virtual Exp_type::type type() const { return exp_type.Exponent; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
	};
	
	
}
}