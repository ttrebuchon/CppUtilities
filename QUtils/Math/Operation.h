#pragma once

#include "Expression.h"
namespace QUtils
{
namespace Math
{
	class Operation : public Expression
	{
		private:
		
		protected:
		
		public:
		virtual ~Operation() {}
		
		
		bool multiTerm() const override { return true; }
		
		friend class Expression;
		
	};
	
	
}
}