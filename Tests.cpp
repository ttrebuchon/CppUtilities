#include <iostream>

#include "QUtils/DebugOut/DebugOut.h"
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
	
	std::ios::sync_with_stdio(false);
	Testing::run();
	return 0;
}
#define TEST_FAILS test_fails


#define tout std::cout
#define testBr "---------------------"
#define LINE_BR "\n\n\n\n\n"




#define RUN(x) try { \
	tout << "Running " << #x << "..." << std::endl; \
	Test_##x; \
	tout << "Test_" << #x << " has completed." << std::endl; \
	} \
catch (std::exception& e) { \
	tout << "\n\nException caught in " << "Test_" << #x << ": \n" << e.what() << std::endl; \
	failures = true; \
	TEST_FAILS .emplace_back(#x, std::current_exception()); \
} \
catch (StringException* ex) { \
	tout << "\n\nStringException* caught in Test_" << #x << ": \n" << ex->what() << std::endl; \
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
	RUN(QT_GUI());
	RUN(Multi());
	RUN(Network());
	RUN(Raytrace());
	RUN(SQL());
	RUN(GUID());
	#ifndef SHORT_TEST
	RUN(TravellingSalesman());
	RUN(GameOfLifeExtended());
	RUN(Types());
	RUN(SymbolicList());
	RUN(English_Analysis());
	//RUN(Network());
	RUN(CLIPS());
	//RUN(SQL());
	RUN(nth_Poly());
	RUN(Tensor_T());
	RUN(Matrix_Algs());
	RUN(Neural());
	RUN(RulesEngine());
	RUN(English());
	//RUN(Raytrace());
	RUN(Tuple());
	RUN(CSV());
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