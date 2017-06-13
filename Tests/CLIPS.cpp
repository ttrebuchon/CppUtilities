#include <iostream>
#include <Clips/clips.h>
#include <vector>
//#include <clips/clips.h>
#include <CLIPS/Env.h>
#include <assert.h>
#include "../Tests.h"

//using namespace clips;

using  namespace std;

#define BUFFER_SIZE 1024

bool Testing::CLIPS()
{
	
	Clips::Environment env;

	

	auto printResult = [] (std::vector<std::string> v) -> void {
		for (auto r : v)
		{
			std::cout << r << std::endl;
		}
	};

	auto cmd = [&] (std::string command) -> void {
		std::cout << command << ": " << std::endl;
		printResult(env.evaluate(command));
	};

	assert(env.assert_f("(mother Sue Mary)") != NULL);
	assert(env.build("(deffacts fBillMary (father Bill Mary))"));
	assert(env.build("(defrule parent (or (mother ?x ?y) (father ?x ?y)) => (assert (parent ?x ?y)))"));
	assert(env.build("(defrule ancestor (or (parent ?x ?y) (and (parent ?z ?y) (ancestor ?x ?z))) => (assert (ancestor ?x ?y)))"));
	cmd("(matches ancestor)");
	env.run(-1);
	cmd("(assert (father Bill Tim))");
	cmd("(matches ancestor)");
	auto res = env.evaluate("(run)");
	for (auto v : res)
	{
		std::cout << v << std::endl;
	}
	
	//env.reset();
	for (auto fact : env.facts())
	{
		std::cout << fact << std::endl;
	}
	cmd("(assert (father Billy Sue))");
	std::cout << "Agenda: " << std::endl;
	printResult(env.evaluate("(agenda)"));
	env.evaluate("(run)");
	for (auto fact : env.facts())
	{
		std::cout << fact << std::endl;
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
	std::cout << "Main Done." << std::endl;
	return true;
}