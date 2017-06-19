//#include <eo>
#include <castor.h>
#include "test.h"

//using namespace std;
using namespace castor;

relation child(lref<string> c, lref<string> p)
	{
		return eq(c,"Sam") &&
		eq(p,"Mary") //fact 1
		|| eq(c,"Denise") && eq(p,"Mary") //fact 2

		|| eq(c,"Sam") && eq(p,"Frank")//fact 3

		|| eq(c,"Denise") && eq(p,"Frank")//fact 4

		|| eq(c,"Frank") && eq(p,"Gary") //fact 5
		;
	}


// p’s gender is g

relation gender(lref<string> p, lref<string> g)

{

 return eq(p,"Frank") && eq(g,"male") //fact 6

 || eq(p,"Sam") && eq(g,"male") //fact 7

 || eq(p,"Mary") && eq(g,"female")//fact 8

 || eq(p,"Denise")&& eq(g,"female")//fact 9

 ;

}

// f is the father of c

relation father(lref<string> f, lref<string> c) 

{

 //... if f is male and c is child of f

 return gender(f,"male") && child(c,f);//rule2

}

ostream& lineBr(ostream& os, int count)
{
	while (count-- > 0)
	{
		os << "-";
	}
	return os << endl;
	
}

int main()
{
	cout << "Start:\n\n" << endl;
	
	auto br = []() -> ostream& { return lineBr(cout); };
	
	auto _father = [](lref<string> f, lref<string> c) -> relation {
		
		return gender(f,"male") && child(c,f); //rule2

		
	};
	
	relation samsDadFrank = _father("Frank","Sam");

	if (samsDadFrank())

	{
		cout << "Frank is Sam's father\n";

	}
	else
	{
		cout << "Frank is not Sam's father\n";
	}
	
	lref<string> sg;
	relation samsGender = gender("Sam", sg);
	if (samsGender())
	{
		cout << "Sam's gender is " << *sg << endl;
	}
	else
	{
		cout << "Sam's gender is not known" << endl;
	}
	
	br();
	lref<string> p, g;
	relation anyGender = gender(p, g);
	while (anyGender())
	{
		cout << *p << "'s gender is " << *g << endl;
	}
	
	famTest();
	br();
	opTest();
	br();
	famTest2();
	br();
	tTest();
	br();
	
	
	cout << "\n\n\nDone." << endl;
}