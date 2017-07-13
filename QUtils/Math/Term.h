#pragma once


namespace QUtils
{
class String;
namespace Math
{
	class Expression;
	
	
	class Term
	{
		private:
		Expression* exp;
		
		protected:
		
		public:
		Term(Expression*);
		Term(long double);
		Term(int);
		Term(String vname);
		Term(const char*);
		Term(const char);
		Term(const Term&);
		~Term();
		
		
		String toString() const;
		Term eval() const;
		
		Term& operator=(const Term&);
		Term& operator=(const String);
		Term& operator=(const char*);
		
		
		Term operator*(Term) const;
		Term operator^(Term) const;
		Term operator/(Term) const;
		Term operator+(Term) const;
		Term operator-(Term) const;
		
	};
	
	Term operator*(long double, const Term&);
	Term operator^(long double, const Term&);
	Term operator/(long double, const Term&);
	Term operator+(long double, const Term&);
	Term operator-(long double, const Term&);
	
	
}
}