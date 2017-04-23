#include <iostream>

#include "DebugOut/DebugOut.h"
#include "Tests.h"
#include <time.h>
#include <fstream>


std::ostream* DebugOut::out(&std::cerr);
DebugOut DebugOut::inst;
bool DebugOut::disabled = false;

DebugOut::DebugOut()
{
	#ifndef TEST_DEBUG
	Disable();
	#endif
}


int main(int argc, char**argv)
{
	Testing::run();
	return 0;
}

#define tout std::cout
#define testBr "---------------------"

#define RUN(x) try { tout << "Running " << #x << "..." << std::endl; x; tout << #x << " has completed." << std::endl; } catch (std::exception& e) { tout << "\n\nException caught in " << #x << ": \n" << e.what() << std::endl; failures = true; } catch (StringException* ex) { tout << "\n\nStringException* caught in " << #x << ": \n" << ex->what() << std::endl; failures = true; }tout << testBr << "\n\n\n\n\n" << testBr << std::endl;

void Testing::run()
{
	bool failures = false;
	#ifdef SEED
	unsigned int seed = time(NULL);
	srand(seed);
	#endif
	try
	{
	RUN(Func());
	RUN(NNST());
	RUN(CustomException());
	RUN(Markov());
	RUN(Stopwatch());
	RUN(String());
	RUN(Math());
	}
	catch (std::string& s)
	{
		tout << "std::string exception: \"" << s << "\"" << std::endl;
	}
	
	
	#ifdef SEED
	if (failures)
	{
		std::ofstream file;
		file.open("Seeds.txt", std::ofstream::out | std::ofstream::app);
		file << seed << std::endl;
		file.close();
	}
	#endif
	
	tout << "Tests Completed." << std::endl;
	#ifndef SEED
	tout << "Failures? " << (failures ? "Yes" : "No") << std::endl;
	#endif
}