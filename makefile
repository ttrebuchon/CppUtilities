Func_cpp = $(wildcard Utility/src/Func/*.cpp)
Func = $(Func_cpp:.cpp=.o)
#*/

NNST_cpp = $(wildcard Utility/src/NearestNeighborTree/*.cpp)
NNST = $(NNST_cpp:.cpp=.o)
#*/

DebugOut_cpp = $(wildcard Utility/src/DebugOut/*.cpp)
DebugOut = $(DebugOut_cpp:.cpp=.o)
#*/

Markov_cpp = $(wildcard Utility/src/Markov/*.cpp)
Markov = $(Markov_cpp:.cpp=.o)
#*/

Stopwatch_cpp = $(wildcard Utility/src/Stopwatch/*.cpp)
Stopwatch = $(Stopwatch_cpp:.cpp=.o)
#*/

String_cpp = $(wildcard Utility/src/String/*.cpp)
String = $(String_cpp:.cpp=.o)
#*/

Math_cpp = $(wildcard Utility/src/Math/*.cpp)
Math = $(Math_cpp:.cpp=.o)
#*/

LazyLoad_cpp = $(wildcard Utility/src/LazyLoad/*.cpp)
LazyLoad = $(LazyLoad_cpp:.cpp=.o)
#*/

Sleep_cpp = $(wildcard Utility/src/Sleep/*.cpp)
Sleep = $(Sleep_cpp:.cpp=.o)
#*/

NeuralNet_cpp = $(wildcard Utility/src/NeuralNet/*.cpp)
NeuralNet = $(NeuralNet_cpp:.cpp=.o)
#*/

CSV_cpp = $(wildcard Utility/src/CSV/*.cpp)
CSV = $(CSV_cpp:.cpp=.o)
#*/


libobjects = $(Func) $(NNST) $(DebugOut) $(Markov) $(Stopwatch) $(String) $(Math) $(LazyLoad) $(Sleep) $(NeuralNet) $(CSV)


Tests_cpp = $(wildcard Tests/*.cpp)
Tests = $(Tests_cpp:.cpp=.o)
#*/
testobjects = Tests.o $(Tests)

NAMESPACE=Utils

PREPROC_FLAGS = -DUtil=$(NAMESPACE) -D__NS__="$(NAMESPACE)"

PREPROC_FLAGS := $(PREPROC_FLAGS) #-DSHORT_TEST

PREPROC_FLAGS := $(PREPROC_FLAGS) -DDEBUG

PREPROC_FLAGS := $(PREPROC_FLAGS) -DSEED

PREPROC_FLAGS := $(PREPROC_FLAGS) -DTEST_DEBUG



WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -Wfatal-errors

FLAGS = -I Utility/include

CXX = g++
CXXFLAGS = -std=c++17 -MMD -fpic -I . $(PREPROC_FLAGS) -Wall $(FLAGS) -Wno-sign-compare $(WARNINGS_ERRORS) -O0 -I ../
libdeps = $(libobjects:.o=.d)
testdeps = $(testobjects:.o=.d)
name = Utility
stLibTarget = lib$(name)
target = $(name)Tests.out

buildOC = gcc -std=c99 -c -pie


$(target): $(stLibTarget).a $(libobjects) $(testobjects) makefile
	$(CXX) -o $(target) $(CXXFLAGS) -std=c++11 $(testobjects) -L. -l$(name) $(PREPROC_FLAGS)

clean: 
	rm $(libobjects)


$(stLibTarget).a: $(libobjects)
	ar rvs $(stLibTarget).a $(libobjects)
	
Tests.o: makefile Tests.cpp
	$(CXX) $(CXXFLAGS) -c Tests.cpp

-include $(libdeps)
-include $(testdeps)