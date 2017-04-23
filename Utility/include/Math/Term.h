#pragma once


namespace Util
{
class String;
namespace Math
{
	class Expression;
	
	
	class Term
	{
		private:
		public:
		Expression* exp;
		
		protected:
		
		public:
		Term(Expression*);
		Term(long double);
		Term(const Term&);
		~Term();
		
		
		String toString() const;
		Term eval() const;
		
		
		//Term operator*(Term) const;
		//Term operator^(Term) const;
		//Term operator/(Term) const;
		Term operator+(Term) const;
		//Term operator-(Term) const;
		
	};
	
	
}
}