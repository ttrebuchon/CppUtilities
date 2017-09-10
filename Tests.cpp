#include <iostream>

#include "QUtils/DebugOut/DebugOut.h"
#include "QUtils/Output/MultiStream.h"
#include "Tests.h"
#include <time.h>
#include <ctime>
#include <fstream>
#include <utility>
#include <vector>
#include "Tests_Helpers.h"

#include <QUtils/Sleep/Sleep.h>

std::stringstream dout_ss;
QUtils::Output::MultiBuf* multibuf;

std::ostream* GUI_out = NULL;


int main(int argc, char**argv)
{
	#ifdef TEST_DEBUG
	DebugOut::enabled() = true;
	#else
	DebugOut::enabled() = false;
	#endif
	
	std::ios::sync_with_stdio(false);
	multibuf = new QUtils::Output::MultiBuf();
	//multibuf->push(std::cerr.rdbuf());
	multibuf->push(std::cout.rdbuf());
	auto coutBuf = std::cout.rdbuf(multibuf);
	
	
	
	
	std::ofstream log("Log.txt");
	log << "\n\n\n\n\n\n\n\n\n\n\n\n";
	time_t rawTime;
	time(&rawTime);
	auto timeinfo = localtime(&rawTime);
	char timeStr[80];
	strftime(timeStr, 80, "%Y-%m-%d %T", timeinfo);
	log << timeStr << "\n\n";
	multibuf->push(log.rdbuf());
	
	auto cerrBuf = std::cerr.rdbuf(log.rdbuf());
	
	assert_ex(dynamic_cast<std::stringbuf*>(dout_ss.rdbuf()) != NULL);
	multibuf->push(dout_ss.rdbuf());
	
	
	
	
	Testing::run();
	std::cerr.rdbuf(cerrBuf);
	std::cout.rdbuf(coutBuf);
	log.close();
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
	#ifdef QUTILS_HAS_SDL2
	RUN(SDL_GUI(&GUI_out));
	//multibuf->push(GUI_out->rdbuf());
	dout << "GUI buf added!\n";
	QUtils::sleep(1000);
	dout << "Slept!\n";
	#endif
	RUN(Multi());
	RUN(Network());
	RUN(Raytrace());
	RUN(SQL());
	RUN(GUID());
	#ifndef SHORT_TEST
	#ifdef QUTILS_HAS_SDL2
	//RUN(SDL_Drawing());
	#endif
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
	
	
	#ifdef QUTILS_HAS_SDL2
	std::string final_str = dout_ss.str();
	*GUI_out << final_str << std::flush;
	//dout << "Screen set to \"" << final_str << "\"" << std::endl;
	dout << "Sleeping for GUI!\n";
	QUtils::sleep(100000);
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