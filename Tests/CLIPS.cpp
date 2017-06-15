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

	auto cmd = [&] (std::string command) -> void {
		dout << command << ": " << std::endl;
		printResult(env.evaluate(command));
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
	
	
	
	
	assert(env.build("(deffacts family (father Jerry Mary) (mother Jill Mary) (father Adam Jerry) (mother Amanda Jerry) (parent Jill Sue) (mother Amanda Jack) (father Jack Mallorie))"));
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
	
	
	
	
	
	
	
	return true;
}