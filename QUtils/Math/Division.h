#pragma once

#include "Operation.h"
#include <vector>
namespace Util
{
namespace Math
{
	class Division : public Operation
	{
		private:
		const Expression* top;
		const Expression* bottom;
		
		protected:
		
		public:
		Division(const Expression*, const Expression*);
		virtual ~Division();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Expression* expand() const override;
		
		virtual Exp_type::type type() const { return exp_type.Division; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
		
		friend class Multiplication;
		
	};
	
	
}
}