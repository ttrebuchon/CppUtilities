#include <iostream>

#include "QUtils/Debug/DebugOut.h"
#include "QUtils/Output/MultiStream.h"
#include "Tests.h"
#include <time.h>
#include <ctime>
#include <fstream>
#include <utility>
#include <vector>
#include "Tests_Helpers.h"

#include <QUtils/Sleep/Sleep.h>
#include <assert.h>

#include <QUtils/GUI/SDL/AppWindow.h>

std::stringstream dout_ss;
QUtils::Output::MultiBuf* multibuf;

std::ostream* GUI_out = NULL;

std::ofstream* log = NULL;

std::streambuf* cerrBuf = NULL;
std::streambuf* coutBuf = NULL;

void on_exit()
{
	std::cerr << "Exiting!\n" << std::flush;
	
	/*if (cerrBuf != NULL)
	{
		std::cerr.rdbuf(cerrBuf);
	}*/
	
	/*if (coutBuf != NULL)
	{
		std::cout.rdbuf(coutBuf);
	}
	
	if (log != NULL)
	{
		log->close();
		delete log;
		log = NULL;
	}*/
	
}

void on_quick_exit()
{
	std::cerr << "Quick Exit!\n" << std::flush;
}

void on_terminate()
{
	std::cerr << "Terminating!\n" << std::flush;
	std::abort();
}


int main(int argc, char**argv)
{
	atexit(on_exit);
	at_quick_exit(on_quick_exit);
	std::set_terminate(on_terminate);
	#ifdef TEST_DEBUG
	DebugOut::enabled() = true;
	#else
	DebugOut::enabled() = false;
	#endif
	
	std::ios::sync_with_stdio(false);
	multibuf = new QUtils::Output::MultiBuf();
	//multibuf->push(std::cerr.rdbuf());
	multibuf->push(std::cout.rdbuf());
	coutBuf = std::cout.rdbuf(multibuf);
	
	
	
	
	log = new std::ofstream("Log.txt");
	*log << "\n\n\n\n\n\n\n\n\n\n\n\n";
	time_t rawTime;
	time(&rawTime);
	auto timeinfo = localtime(&rawTime);
	char timeStr[80];
	strftime(timeStr, 80, "%Y-%m-%d %T", timeinfo);
	*log << timeStr << "\n\n";
	multibuf->push(log->rdbuf());
	
	auto errBuf = new QUtils::Output::MultiBuf();
	errBuf->push(std::cerr.rdbuf());
	errBuf->push(log->rdbuf());
	
	cerrBuf = std::cerr.rdbuf(errBuf);
	
	assert_ex(dynamic_cast<std::stringbuf*>(dout_ss.rdbuf()) != NULL);
	multibuf->push(dout_ss.rdbuf());
	
	#ifdef __GNUC__
	dout << "Using G++\n";
	#endif
	
	
	Testing::run();
	
	return 0;
}
#define TEST_FAILS test_fails


#define tout std::cout
#define testBr "---------------------"
#define LINE_BR "\n\n\n\n\n"




#define RUN(x) try { \
	tout << "Running Test_" << #x << "..." << std::endl; \
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
	//#ifdef QUTILS_HAS_SDL2
	QUtils::GUI::SDL::SDLAppWindow* win = NULL;
	//#endif
	try
	{
	//#ifdef QUTILS_HAS_SDL2
	RUN(SDL_GUI(&GUI_out, win));
	if (GUI_out != NULL)
	{
	multibuf->push(GUI_out->rdbuf());
	dout << "GUI buf added!\n";
	QUtils::sleep(1000);
	dout << "Slept!\n";
	}
	//#endif
	RUN(ASM());
	RUN(Graphs_DependencyGraph());
	RUN(Graphs());
	RUN(Iterable());
	RUN(TravellingSalesman());
	RUN(World_Physics());
	RUN(DBC());
	#ifndef SHORT_TEST
	RUN(Multi_ThreadPool());
	RUN(Network_Sockets());
	RUN(Network_ServiceProtocol());
	RUN(Network_SocketService());
	RUN(BoostBased_Serialization());
	RUN(CodeGen_Utility());
	RUN(SDL_Drawing());
	//RUN(TravellingSalesman());
	RUN(GameOfLifeExtended());
	RUN(RucksackProblem());
	RUN(Types());
	RUN(SymbolicList());
	RUN(English_Analysis());
	//RUN(Network());
	RUN(CLIPS());
	RUN(SQL());
	RUN(GUID());
	RUN(Multi());
	RUN(nth_Poly());
	RUN(Tensor_T());
	RUN(Matrix_Algs());
	RUN(Neural());
	RUN(RulesEngine());
	RUN(English());
	RUN(Raytrace());
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
	
	
	//#ifdef QUTILS_HAS_SDL2
	if (GUI_out != NULL)
	{
	
	if (win != NULL)
	{
		win->handleEvents();
	}
	dout << "Sleeping for GUI!\n";
	QUtils::sleep(10000);
	if (win != NULL)
	{
		win->handleEvents();
	}
	QUtils::sleep(15000);
	if (win != NULL)
	{
		win->handleEvents();
	}
	QUtils::sleep(25000);
	if (win != NULL)
	{
		win->handleEvents();
	}
	QUtils::sleep(50000);
	if (win != NULL)
	{
		win->handleEvents();
	}
	if (win != NULL)
	{
		delete win;
		win = NULL;
	}
	}
	
	//#endif
	}
	catch (std::exception& ex)
	{
		tout << "Exception caught: " << ex.what() << std::endl;
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