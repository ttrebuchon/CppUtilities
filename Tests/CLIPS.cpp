#include <iostream>
#include <Clips/clips.h>
#include <vector>
//#include <clips/clips.h>
#include <QUtils/CLIPS/Env.h>
#include <assert.h>
#include "../Tests_Helpers.h"

//using namespace clips;

using namespace std;
using namespace Util;

#define BUFFER_SIZE 1024

bool Test_CLIPS()
{
	
	Clips::Environment env;
	

	

	auto printResult = [] (std::vector<std::string> v) -> void {
		for (auto r : v)
		{
			dout << r << std::endl;
		}
	};

	auto cmd = [&] (std::string command) -> auto {
		dout << command << ": " << std::endl;
		std::vector<std::string> v;
		printResult(v = env.evaluate(command));
		return v;
	};

	assert(env.assert_f("(mother Sue Mary)") != NULL);
	assert(env.build("(deffacts fBillMary (father Bill Mary))"));
	assert(env.build("(defrule parent (or (logical (mother ?x ?y)) (logical (father ?x ?y))) => (assert (parent ?x ?y)))"));
	
	assert(env.build("(defrule ancestor (or (logical (parent ?x ?y)) (and (logical (parent ?z ?y)) (logical (ancestor ?x ?z)))) => (assert (ancestor ?x ?y)))"));
	cmd("(matches ancestor)");
	env.run(-1);
	cmd("(assert (father Bill Tim))");
	cmd("(matches ancestor)");
	auto res = env.evaluate("(run)");
	for (auto v : res)
	{
		dout << v << std::endl;
	}
	
	//env.reset();
	for (auto fact : env.facts())
	{
		dout << fact << std::endl;
	}
	cmd("(assert (father Billy Sue))");
	dout << "Agenda: " << std::endl;
	printResult(env.evaluate("(agenda)"));
	env.evaluate("(run)");
	for (auto fact : env.facts())
	{
		dout << fact << std::endl;
	}
	
	
	cmd("(run)");	//This one should print nothing, as it returns void
	cmd("(retract 1)");
	cmd("(facts)");
	cmd("(agenda)");
	cmd("(run)");
	cmd("(facts)");
	cmd("(reset)");
	cmd("(agenda)");
	cmd("(facts)");
	cmd("(run)");
	cmd("(facts)");
	cmd("(rules)");
	assert(env.build("(deffunction func (?x ?y) (assert (father ?x ?y)))"));
	//cmd("(defrule gender (mother ?x ?y) => (assert (gender ?x female)))");
	cmd("(func Billy Sue)");
	assert(env.build("(deffunction printTest (?a ?b $?c) (printout t ?a \" \" ?b \" and \" (length ?c) \" extras: \" ?c crlf))"));
	cmd("(printTest 1 2 3 4 5)");
	assert(env.build("(defrule goal ?fact <- (ancestor ?x Sue) => (assert (goal ?fact)))"));
	env.run(-1);
	cmd("(facts)");
	cmd("(fact-relation 7)");
	cmd("(find-all-facts ((?f father)) TRUE)");
	cmd("(any-factp ((?f father)) (eq ?f:implied (create$ Billy Sue)))");
	
	env.assert_f("mother", "Jill", "Billy");
	cmd("(facts)");
	cmd("(agenda)");
	cmd("(run)");
	cmd("(facts)");
	cmd("(any-factp ((?f goal)) TRUE)");
	
	cmd("(undeffacts fBillMary)");
	
	env.reset();
	
	cmd("(facts)");
	
	env.assert_f("father", "Jerry", "Mary");
	env.assert_f("mother", "Jill", "Mary");
	env.assert_f("father", "Adam", "Jerry");
	env.assert_f("mother", "Amanda", "Jerry");
	env.assert_f("(parent Jill Sue)");
	env.run(-1);
	cmd("(facts)");
	
	
	assert(env.build("(defrule sibling (logical (parent ?z ?y)) (logical (parent ?z ?x)) (test (neq ?x ?y)) => (assert (sibling ?x ?y)) (assert (sibling ?y ?x)))"));
	cmd("(agenda)");
	
	env.run(-1);
	cmd("(facts)");
	
	assert(env.build("(defrule cousin (logical (parent ?z ?x)) (logical (sibling ?a ?z)) (logical (parent ?a ?y)) => (assert (cousin ?x ?y)))"));
	cmd("(agenda)");
	env.assert_f("mother", "Amanda", "Jack");
	env.assert_f("father", "Jack", "Mallorie");
	cmd("(agenda)");
	env.run(-1);
	cmd("(facts)");
	cmd("(any-factp ( or (?f cousin) TRUE) (eq ?f:implied (create$ Mallorie Mary)))");
	cmd("(reset)");
	cmd("(clear)");
	cmd("(facts)");
	
	dout << "\n\n\n\n\n";
	
	
	
	std::string familyFacts = "(father Jerry Mary) (mother Jill Mary) (father Adam Jerry) (mother Amanda Jerry) (parent Jill Sue) (mother Amanda Jack) (father Jack Mallorie)";
	assert(env.build("(deffacts family " + familyFacts + ")"));
	dout << "Family defined" << std::endl;
	assert(env.build("(defrule parent (or (logical (mother ?x ?y)) (logical (father ?x ?y))) => (assert (parent ?x ?y)))"));
	dout << "parent defined." << std::endl;
	assert(env.build("(defrule ancestor (or (logical (parent ?x ?y)) (and (logical (parent ?z ?y)) (logical (ancestor ?x ?z)))) => (assert (ancestor ?x ?y)))"));
	dout << "ancestor defined." << std::endl;
	assert(env.build("(defrule sibling (logical (parent ?z ?y)) (logical (parent ?z ?x)) (test (neq ?x ?y)) => (assert (sibling ?x ?y)) (assert (sibling ?y ?x)))"));
	dout << "sibling defined." << std::endl;
	assert(env.build("(defrule cousin (logical (parent ?z ?x)) (logical (sibling ?a ?z)) (logical (parent ?a ?y)) => (assert (cousin ?x ?y)))"));
	dout << "cousin defined." << std::endl;
	assert(env.build("(defrule aunt (logical (parent ?z ?P)) (logical (sibling ?A ?z)) (gender ?A Female) => (assert (aunt ?A ?P)))"));
	dout << "aunt defined." << std::endl;
	assert(env.build("(defrule uncle (logical (parent ?z ?P)) (logical (sibling ?U ?z)) (gender ?U Male) => (assert (uncle ?U ?P)))"));
	dout << "uncle defined." << std::endl;
	assert(env.build("(defrule genderMother (mother ?x ?y) => (assert (gender ?x Female)))"));
	dout << "genderMother defined." << std::endl;
	assert(env.build("(defrule genderFather (father ?x ?y) => (assert (gender ?x Male)))"));
	dout << "genderFather defined." << std::endl;
	assert(env.build("(defrule brother (logical (sibling ?B ?P)) (gender ?B Male) => (assert (brother ?B ?P)))"));
	assert(env.build("(defrule sister (logical (sibling ?S ?P)) (gender ?S Female) => (assert (sister ?S ?P)))"));
	
	
	assert(env.build("(defrule related (logical (or (and (ancestor ?A ?P) (ancestor ?A ?P2)) (and (ancestor ?P ?D) (ancestor ?P2 ?D)))) (test (neq ?P ?P2)) => (assert (related ?P ?P2)))"));
	
	assert(env.build("(defrule relatedRecursive (logical (and (related ?P ?M) (related ?M ?P2))) (not (related ?P ?P2)) (test (neq ?P ?P2)) => (assert (related ?P ?P2)))"));
	
	
	env.reset();
	dout << "Reset." << std::endl;
	cmd("(facts)");
	cmd("(agenda)");
	dout << "\n\n";
	env.run(7);
	dout << "Ran" << std::endl;
	cmd("(facts)");
	
	dout << "\n\n\n" << std::endl;
	
	cmd("(run)");
	cmd("(facts)");
	
	cmd("(get-fact-list *)");
	cmd("(facts)");
	dout << "\n\n\n";
	cmd("(rules)");
	
	cmd("(undefrule related)");
	env.reset();
	env.run(-1);
	cmd("(facts)");
	
	
	//assert_ex(env.build("(deffunction min (?x ?y) (if (< ?x ?y) then ?x else ?y))"));
	assert_ex(env.build("(deftemplate DoS (slot Person1) (slot Person2) (slot N))"));
	
	assert_ex(env.build("(deffunction NoDoS (?x ?y) (not (any-factp ((?f DoS)) (and (eq ?f:Person1 ?x) (eq ?f:Person2 ?y)))))"));
	
	assert_ex(env.build("(deffunction isDoS (?x ?y ?z) (not (not (any-factp ((?f DoS)) (and (eq ?f:Person1 ?x) (eq ?f:Person2 ?y) (eq ?f:N ?z))))))"));
	
	assert_ex(env.build("(deffunction SetDoS (?x ?y ?n) (if (not (NoDoS ?x ?y)) then (do-for-all-facts ((?f DoS)) (and (eq ?f:Person1 ?x) (eq ?f:Person2 ?y)) (modify ?f (N ?n))) else (assert (DoS (Person1 ?x) (Person2 ?y) (N ?n)))))"));
	
	
	
	
	
	
	
	
	
	/*assert_ex(env.build("(defrule InitDoSParent (declare (salience -1)) (logical (parent ?x ?y)) (test (not (isDoS ?x ?y 1))) => (assert (DoS (Person1 ?x) (Person2 ?y) (N 1))))"));
	
	assert_ex(env.build("(defrule InitDoSSibling (declare (salience -1)) (logical (sibling ?x ?y)) (test (not (isDoS ?x ?y 1))) => (assert (DoS (Person1 ?x) (Person2 ?y) (N 1))))"));
	
	assert_ex(env.build("(defrule DoSRule (declare (salience -2)) (logical (DoS (Person1 ?x) (Person2 ?y) (N ?D))) (logical (DoS (Person1 ?y) (Person2 ?z) (N ?D2)))  (or (not (DoS (Person1 ?x) (Person2 ?z) (N ?D3))) (and (DoS (Person1 ?x) (Person2 ?z) (N ?D3))   (test (< (+ ?D ?D2) ?D3))   )) (test (not (eq ?x ?z)))  => "
	
	"(do-for-all-facts ((?f DoS)) (and (eq ?f:Person1 ?x) (eq ?f:Person2 ?z)) (retract ?f))"
	
	"(assert (DoS (Person1 ?x) (Person2 ?z) (N (+ ?D ?D2))))   )"));*/
	
	
	
	
	
	
	
	
	
	assert_ex(env.build("(defrule InitDoSParent (logical (parent ?x ?y)) (test (not (isDoS ?x ?y 1))) => (SetDoS ?x ?y 1))"));
	
	assert_ex(env.build("(defrule InitDoSSibling (logical (sibling ?x ?y)) (test (not (isDoS ?x ?y 1))) => (SetDoS ?x ?y 1))"));
	
	assert_ex(env.build("(defrule DoSRule (declare (salience -1)) (logical (DoS (Person1 ?x) (Person2 ?y) (N ?D))) (logical (DoS (Person1 ?y) (Person2 ?z) (N ?D2))) (or (not (DoS (Person1 ?x) (Person2 ?z) (N ?D3))) (and (DoS (Person1 ?x) (Person2 ?z) (N ?D3))   (test (< (+ ?D ?D2) ?D3)) )) (test (not (eq ?x ?z)))  => "
	
	"(SetDoS ?x ?z (+ ?D ?D2)))"));
	
	
	assert_ex(env.build("(defrule DoS_BiDir (declare (salience 1))(DoS (Person1 ?y) (Person2 ?x) (N ?n)) (or (not (DoS (Person1 ?x) (Person2 ?y))) (and (DoS (Person1 ?x) (Person2 ?y) (N ?n2)) (test (< ?n ?n2)))) => (SetDoS ?x ?y ?n))"));
	
	
	
	
	
	cmd("(undeffacts family)");
	dout << "\n\n\n";
	
	std::string manyPeopleFacts = "(deffacts ManyPeople ";
	int pCount = 20;
	int parents[pCount][2];
	for (int i = 0; i < pCount; i++)
	{
		parents[i][0] = (i + 1) + (rand() % (pCount - i));
		parents[i][1] = (i + 1) + (rand() % (pCount - i));
	}
	
	
	
	for (int i = 0; i < pCount; i++)
	{
		manyPeopleFacts += "(parent P" + std::to_string(parents[i][0]) + " P" + std::to_string(i) + ") ";
		
		manyPeopleFacts += "(parent P" + std::to_string(parents[i][1]) + " P" + std::to_string(i) + ") ";
	}
	
	manyPeopleFacts += ")";
	assert_ex(env.build(manyPeopleFacts));
	
	
	
	env.reset();
	dout << "Running..." << std::endl;
	int actCount = 0;
	const int iterCount = -1;
	int iter;
	while((iter = env.run(iterCount)) > 0)
	{
		actCount += iter;
		dout << "\rACount: " << actCount;
	}
	dout << std::endl;
	
	dout << "\n\n";
	
	assert_ex(cmd("(find-all-facts ((?f DoS) (?f2 DoS)) (and (eq ?f:Person1 ?f2:Person1) (eq ?f:Person2 ?f2:Person2) (neq ?f:N ?f2:N)))").size() == 0);
	
	
	
	
	cmd("(undeffacts ManyPeople)");
	assert_ex(env.build("(deffacts family " + familyFacts + ")"));
	env.reset();
	dout << "\n\n\n\n\n\n\n\n";
	env.run(-1);
	
	cmd("(assert (parent Jones Adam))");
	cmd("(agenda)");
	cmd("(run)");
	
	
	
	dout << "\n\n\n\n\n\n\n";
	cmd("(facts)");
	
	
	return true;
}