#include <iostream>

#include "DebugOut/DebugOut.h"
#include "Tests.h"
#include <time.h>
#include <fstream>
#include <utility>
#include <vector>



int main(int argc, char**argv)
{
	#ifdef TEST_DEBUG
	DebugOut::enabled() = true;
	#else
	DebugOut::enabled() = false;
	#endif
	Testing::run();
	return 0;
}
#define TEST_FAILS test_fails


#define tout std::cout
#define testBr "---------------------"
#define LINE_BR "\n\n\n\n\n"




#define RUN(x) try { \
	tout << "Running " << #x << "..." << std::endl; \
	x; \
	tout << #x << " has completed." << std::endl; \
	} \
catch (std::exception& e) { \
	tout << "\n\nException caught in " << #x << ": \n" << e.what() << std::endl; \
	failures = true; \
	TEST_FAILS .emplace_back(#x, std::current_exception()); \
} \
catch (StringException* ex) { \
	tout << "\n\nStringException* caught in " << #x << ": \n" << ex->what() << std::endl; \
	failures = true; \
	TEST_FAILS .emplace_back(#x, std::current_exception()); \
} \
tout << testBr << LINE_BR << testBr << std::endl;



typedef std::pair<std::string, std::exception_ptr> Test_Fail;

void Testing::run()
{
	std::vector<Test_Fail> TEST_FAILS;
	bool failures = false;
	#ifdef SEED
	unsigned int seed = time(NULL);
	srand(seed);
	#endif
	dout << LINE_BR << testBr << std::endl;
	try
	{
	RUN(nth_Poly());
	RUN(Tensor_T());
	RUN(Matrix_Algs());
	RUN(Raytrace());
	RUN(Neural());
	#ifndef SHORT_TEST
	RUN(Tuple_Test());
	RUN(CSV_Test());
	RUN(Matrix());
	RUN(Math());
	
	RUN(Sleep());
	RUN(Lazy());
	RUN(Func());
	RUN(CustomException());
	RUN(Stopwatch());
	RUN(String());
	RUN(Markov());
	RUN(NNST());
	#endif
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
	
	tout << "\n\nTests Completed." << std::endl;
	tout << "Failures? " << (failures ? "Yes\n\n" : "No") << LINE_BR << std::endl;
	
	
	for (Test_Fail f : TEST_FAILS)
	{
		tout << "Exception in test " << f.first << ":\n";
		try
		{
			std::rethrow_exception(f.second);
		}
		catch (const std::exception& e)
		{
			tout << e.what();
		}
		catch (const std::exception* e)
		{
			tout << e->what();
		}
		tout << "\n" << std::endl;
	}
	
	
}