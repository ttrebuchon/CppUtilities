#ifndef INCLUDED_UTIL_TESTS_H
#define INCLUDED_UTIL_TESTS_H

#include "Tests_Helpers.h"

#define DEF_TEST(x) bool Test_##x()

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

DEF_TEST(Func);
DEF_TEST(NNST);
DEF_TEST(CustomException);
DEF_TEST(Markov);
DEF_TEST(Stopwatch);
DEF_TEST(String);
DEF_TEST(Math);
DEF_TEST(Matrix);
DEF_TEST(Lazy);
DEF_TEST(Sleep);
DEF_TEST(Neural);
DEF_TEST(CSV);
DEF_TEST(nth_Poly);
DEF_TEST(Tuple);
DEF_TEST(Tensor_T);
DEF_TEST(Matrix_Algs);
DEF_TEST(Raytrace);
DEF_TEST(RulesEngine);
DEF_TEST(CLIPS);
DEF_TEST(English);
DEF_TEST(SQL);
DEF_TEST(Multi);
DEF_TEST(TravellingSalesman);
DEF_TEST(GameOfLifeExtended);
DEF_TEST(Types);
DEF_TEST(SymbolicList);
DEF_TEST(English_Analysis);
DEF_TEST(Network);









#endif