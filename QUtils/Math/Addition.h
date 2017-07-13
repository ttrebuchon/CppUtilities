#pragma once

#include "Operation.h"
#include <vector>
namespace QUtils
{
namespace Math
{
	class Addition : public Operation
	{
		private:
		std::vector<const Expression*> operands;
		
		
		protected:
		
		public:
		Addition(const Expression*, const Expression*);
		virtual ~Addition();
		
		virtual String toString() const override;
		virtual Expression* eval() const override;
		
		virtual Expression* expand() const override;
		
		virtual Exp_type::type type() const { return exp_type.Addition; }
		
		virtual Expression* copy() const override;
		
		virtual bool equals(const Expression*) const override;
		
		virtual bool contains(const Expression*) const override;
		
		friend class Subtraction;
		
	};
	
	
}
}