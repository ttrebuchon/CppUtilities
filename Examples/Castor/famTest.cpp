#include "test.h"
#include <castor.h>
#include <vector>
#include <functional>

using namespace castor;

class Person
{
  public:
	Person * mother;
	Person *father;

	  vector < Person * >children;
	string name;
	string gender;

	  Person(string name, string gender):mother(NULL), father(NULL), children(), name(name),
		gender(gender)
	{
	}

	Person(const Person & p):mother(p.mother), father(p.father), children(p.children),
		name(p.name), gender(p.name)
	{
	}
	
};



void famTest()
{
	Person *tom, *mary, *jill, *bob, *tim, *jim;
	// Grandparents
	tom = new Person("Tom", "male");
	mary = new Person("Mary", "female");
	// Parents
	jill = new Person("Jill", "female");
	bob = new Person("Bob", "male");
	// Child
	tim = new Person("Tim", "male");
	// Unrelated
	jim = new Person("Jim", "male");


	jill->mother = mary;
	jill->father = tom;

	tim->mother = jill;
	tim->father = bob;

	tom->children.push_back(jill);
	mary->children.push_back(jill);

	jill->children.push_back(tim);
	bob->children.push_back(tim);


	std::function<relation(lref<string>, lref<string>)> mother = [](lref<string> m, lref<string> c) -> relation {
		return eq("", " ");
	};

	std::function<relation(lref<string>, lref<string>)> father = [](lref<string> f, lref<string> c) -> relation {
		return eq("", " ");
	};

	auto child =[&](lref<string> c, lref<string> p) -> relation {
		return father(p, c) || mother(p, c);
	};

	auto parent =[&](lref<string> p, lref<string> c) -> relation {
		return father(p, c) || mother(p, c);
	};

	vector<Person*> parsed;
	std::function<void(Person*)> parsePerson;
	parsePerson = std::function<void(Person*)>([&](Person* p) {
		if (p == NULL)
		{
			return;
		}
		 if (find(parsed.begin(), parsed.end(), p) != parsed.end())
		 {
		 	return;
		 }

		 parsed.push_back(p);
		 auto name = p->name;
		 if (p->mother != NULL)
		 {
		 	auto oldM = mother;
		 	auto mName = p->mother->name;
		 	mother = [oldM, mName, name] (lref<string> m, lref<string> c)
		 	{
		 		return oldM(m, c) || eq(m, mName) && eq(c, name);
		 	};
		 	parsePerson(p->mother);
		 }
		 
		 if (p->father != NULL)
		 {
		 	auto oldF = father;
		 	auto fName = p->father->name;
		 	father = [oldF, fName, name] (lref<string> f, lref<string> c)
		 	{
		 		return oldF(f, c) || eq(f, fName) && eq(c, name);
		 	};
		 	parsePerson(p->father);
		 }
		 
		 for (auto child : p->children)
		 {
		 	parsePerson(child);
		 }
		 
		 
	});
	
	parsePerson(tom);
	lref<string> jillL;
	auto maryMotherJ = mother("Mary", jillL);
	
	maryMotherJ();
	cout << "Mary is mother of " <<  *jillL << endl;
	lineBr(cout);
	
	
	
	std::function<relation(lref<string>, lref<string>)> descendant;
	descendant = [&](lref<string> desc, lref<string> person) -> relation
	{
		lref<string> ancestor;
		
		return child(desc, person) || child(ancestor, person) && recurse(descendant, desc, ancestor);
	};
	
	
	
	
	lineBr(cout);
	lref<string> timAncest;
	auto desc = descendant("Tim", timAncest);
	while (desc())
	{
		cout << *timAncest << endl;
	}
	lineBr(cout);
	lref<string> jimAncest;
	desc = descendant("Jim", jimAncest);
	while (desc())
	{
		cout << *jimAncest << endl;
	}
	lineBr(cout);
	
	
	lref<string> descendants, ancestors;
	desc = descendant(descendants, ancestors);
	
	while (desc())
	{
		cout << *descendants << " is descendant of " << *ancestors << endl;
	}
	
	
}