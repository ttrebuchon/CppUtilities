#pragma once

#include "Operation.h"

#include <vector>
#include <tuple>
namespace QUtils
{
namespace Math
{
	class Subtraction : public Operation
	{
		private:
		const Expression* left;
		std::vector<const Expression*> right;
		
		protected:
		
		public:
		Subtraction(const Expression*, const Expression*);
		virtual ~Subtraction();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Expression* expand() const override;
		
		virtual Exp_type::type type() const { return exp_type.Subtraction; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
	};
	
	
}
}