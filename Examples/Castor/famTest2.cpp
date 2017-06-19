#include "test.h"
#include <castor.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <assert.h>
#include <sstream>

using namespace castor;

class Person
{
	public:
	Person* mother;
	Person* father;
	vector<Person*> children;
	
	string name;
	string gender;
	
	Person(string name, string gender) :   mother(),
	father(),
	children(),
	name(name),
	gender(gender)
	{
	}
	
	Person(const Person& p) :
	mother(p.mother),
	father(p.father),
	children(p.children),
	name(p.name),
	gender(p.gender)
	{
	}
	
	~Person() {
		//cout << "Deleting" << endl;
	}
	
	Person& operator=(const Person& p)
	{
		name = p.name;
		gender = p.gender;
		mother = p.mother;
		father = p.father;
		return *this;
	}
	
	bool operator==(const Person& p) const
	{
		//cout << "Comparing " << toString() << " to " << p.toString() << endl;
		return (name == p.name && mother == p.mother && father == p.father && gender == p.gender);
	}
	
	string toString() const
	{
		return static_cast<stringstream>(stringstream() << "(" << name << ", " << gender << ", " << mother << ", " << father << ")").str();
	}
};

vector<string> maleNames = { "Bob", "Jim", "Tim", "Bill", "Will", "Tyler", "Scott", "Richard" };

vector<string> femaleNames = { "Mary", "Sue", "Anna", "Natalie", "Carrie", "Sarah", "Cristina", "Sophia" };

vector<string> surnames = { "Smith", "Trebuchon", "Meyer", "Sparrow", "Turner", "Williamson" };

vector<string> maleIDs = {};
vector<string> femaleIDs = {};

string getName(bool male)
{
	string name;
	if (male)
	{
		name = maleIDs[0];
		maleIDs.erase(maleIDs.begin());
		return name;
	}
	else
	{
		name = femaleIDs[0];
		femaleIDs.erase(femaleIDs.begin());
		return name;
	}
}

Person* getPerson(bool male)
{
	if ((male ? maleIDs : femaleIDs).size() <= 0)
	{
		return NULL;
	}
	return new Person(getName(male), male ? "male" : "female");
}

vector<Person*> generatePeople(int count = -1)
{
	if (count < 0)
	{
		count = INT_MAX;
	}
	vector<Person*> vec;
	
	Person* tmp = getPerson(rand() % 2);
	vec.push_back(tmp);
	
	vector<Person*> needsParents = { tmp };
	
	Person *m, *f;
	while (vec.size() < count)
	{
		tmp = needsParents[0];
		
		f = getPerson(1);
		m = getPerson(0);
		tmp->mother = m;
		tmp->father = f;
		
		if (f != NULL)
		{
			vec.push_back(f);
			needsParents.push_back(f);
		}
		if (m != NULL)
		{
			vec.push_back(m);
			needsParents.push_back(m);
		}
		
		if (f == NULL || m == NULL)
		{
			break;
		}
		needsParents.erase(needsParents.begin());
	}
	
	
	
	
	
	return vec;
}

void initNames()
{
	for (auto lname : surnames)
	{
		for (auto fname : maleNames)
		{
			maleIDs.push_back(fname + " " + lname);
		}
		
		for (auto fname : femaleNames)
		{
			femaleIDs.push_back(fname + " " + lname);
		}
	}
	
	shuffle (maleIDs.begin(), maleIDs.end(), std::default_random_engine(1));
	
	shuffle (femaleIDs.begin(), femaleIDs.end(), std::default_random_engine(0));
	
}




























bool isAncestor(Person* A, Person* P)
{
	if (A == NULL || P == NULL)
	{
		return false;
	}
	
	//cout << "Checking is " << A->name << " ancestor of " << P->name << " (" << A << ", " << P << ")" << endl;
	
	if (*A == *P)
	{
		//cout << "Is Ancestor" << endl;
		return true;
	}
	
	
	
	return isAncestor(A, P->mother) || isAncestor(A, P->father);
}



void famTest2()
{
	initNames();
	vector<Person*> people = generatePeople();
	typedef Person P;
	
	
	auto mother = [&] (lref<P> m, lref<P> c) -> relation
	{
		Disjunctions dis;
		for (Person* p : people)
		{
			if (p->mother != NULL)
			{
				lref<Person> pm(p->mother, false), pl(p, false);
				dis.push_back(eq(m, pm) && eq(c, pl));
			}
		}
		return dis;
	};
	
	
	lref<P> p1(people[0], false), m1;
	lref<P> p2, m2;
	relation r1 = mother(m1, p1);
	while(r1())
	{
		cout << m1->name << endl;
	}
	relation r2 = mother(m2, p2);
	
	while (r2())
	{
		cout << m2->name << " is mother of " << p2->name << endl;
	}
	lineBr(cout);
	
	auto father = [&] (lref<P> F, lref<P> C) -> relation {
		Disjunctions dis;
		for (Person* p : people)
		{
			if (p->father != NULL)
			{
			
			lref<P> PF(p->father, false);
			lref<P> P(p, false);
			dis.push_back(eq(F, PF) && eq(C, P));
			}
		}
		return dis;
	};
	
	auto parent = [&](auto P, auto C) -> relation {
		return mother(P, C) || father(P, C);
	};
	
	std::function<relation(lref<P>, lref<P>)> ancestor;
	
	ancestor = std::function<relation(lref<P>, lref<P>)>([&](lref<P> A, lref<P> P) -> relation {
		lref<Person> D;
		return parent(A, P) || (parent(D, P) && recurse(ancestor, A, D));
	});
	
	lref<P> base(people[0], false), ancest;
	relation ar = ancestor(ancest, base);
	
	while (ar())
	{
		cout << ancest->name << " is an ancestor of " << base->name << endl;
		assert(isAncestor(&*ancest, people[0]));
	}
	lineBr(cout);
	
	
	std::function<relation(lref<P>, lref<P>)> descendant;
	descendant = std::function<relation(lref<P>, lref<P>)>([&] (auto D, auto P) -> relation {
		lref<Person> A;
		return (parent(P, D) || (parent(P, A) && recurse(descendant, D, A)));
	});
	
	#define DEFINE_FACT(x) std::function<relation(lref<Person>, lref<Person>)> x; \
	x = (std::function<relation(lref<Person>, lref<Person>)>)[&]
	
	DEFINE_FACT(maternalAnc)
	(lref<Person> A, lref<Person> D) -> relation {
		lref<Person> M;
		return (mother(A, D) || (mother(M, D) && recurse(ancestor, A, M)));
	};
	
	ancest.reset();
	base.set_ptr(people[0], false);
	ar = maternalAnc(ancest, base);
	while (ar())
	{
		cout << ancest->name << " is maternal ancestor of " << base->name << endl;
	}
	lineBr(cout);
	cout << "Checking that..." << endl;
	ancest.reset();
	lref<Person> mA;
	ar = mother(ancest, base);
	while (ar())
	{
		cout << ancest->name << " is mother of " << base->name << endl;
		//cout << ancest->name << "'s parents are " << (ancest->mother != NULL ? ancest->mother->name : "NULL") << " and " << (ancest->father != NULL ? ancest->father->name : "NULL") << endl;
		lref<Person> anc2;
		relation ar_2 = ancestor(anc2, ancest);
		bool mASet = false;
		while (ar_2())
		{
			cout << "\t" << anc2->name << " is ancestor of " << ancest->name << endl;
			mA.set_ptr(&*anc2, false);
			mASet = true;
		}
		if (mASet)
		{
			relation ar_3 = maternalAnc(mA, base);
			//assert(ar_3());
		}
		
	}
	
	
	
	
	
	
	
	
	for (auto p : people)
	{
		delete p;
	}
	people.clear();
	cout << "famTest2 Done." << endl;
}