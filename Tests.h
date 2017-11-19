#ifndef INCLUDED_UTIL_TESTS_H
#define INCLUDED_UTIL_TESTS_H

#include "Tests_Helpers.h"

#define DEC_TEST(x) bool Test_##x()

namespace QUtils
{
namespace GUI
{
namespace SDL
{
	class SDLAppWindow;
}
}
}

class Testing
{
	public:
	
	static void run();
	
	/*static bool Func();
	static bool NNST();
	static bool CustomException();
	static bool Markov();
	static bool Stopwatch();
	static bool String();
	static bool Math();
	static bool Matrix();
	static bool Lazy();
	static bool Sleep();
	static bool Neural();
  	static bool CSV_Test();
  	static bool nth_Poly();
	static bool Tuple_Test();
	static bool Tensor_T();
	static bool Matrix_Algs();
	static bool Raytrace();
	static bool RulesEngine();
	static bool CLIPS();
	static bool English();*/
};

DEC_TEST(Func);
DEC_TEST(NNST);
DEC_TEST(CustomException);
DEC_TEST(Markov);
DEC_TEST(Stopwatch);
DEC_TEST(String);
DEC_TEST(Math);
DEC_TEST(Matrix);
DEC_TEST(Lazy);
DEC_TEST(Sleep);
DEC_TEST(Neural);
DEC_TEST(CSV);
DEC_TEST(nth_Poly);
DEC_TEST(Tuple);
DEC_TEST(Tensor_T);
DEC_TEST(Matrix_Algs);
DEC_TEST(Raytrace);
DEC_TEST(RulesEngine);
DEC_TEST(CLIPS);
DEC_TEST(English);
DEC_TEST(SQL);
DEC_TEST(Multi);
DEC_TEST(TravellingSalesman);
DEC_TEST(RucksackProblem);
DEC_TEST(GameOfLifeExtended);
DEC_TEST(Types);
DEC_TEST(SymbolicList);
DEC_TEST(English_Analysis);
DEC_TEST(Network);
DEC_TEST(Network_Sockets);
DEC_TEST(Network_ServiceProtocol);
DEC_TEST(Network_SocketService);
DEC_TEST(GUID);
//DEC_TEST(SDL_GUI);
bool Test_SDL_GUI(std::ostream**, QUtils::GUI::SDL::SDLAppWindow*&);
DEC_TEST(SDL_Drawing);
DEC_TEST(CodeGen_Utility);
DEC_TEST(ASM);
DEC_TEST(BoostBased_Serialization);
DEC_TEST(Graphs_DependencyGraph);
DEC_TEST(Graphs);
DEC_TEST(Multi_ThreadPool);
DEC_TEST(Iterable);
DEC_TEST(World_Physics);


#undef DEC_TEST








#endif