
SRC = src

Func_cpp = $(wildcard $(SRC)/Func/*.cpp)
Func = $(Func_cpp:.cpp=.o)
#*/

NNST_cpp = $(wildcard $(SRC)/NearestNeighborTree/*.cpp)
NNST = $(NNST_cpp:.cpp=.o)
#*/

DebugOut_cpp = $(wildcard $(SRC)/DebugOut/*.cpp)
DebugOut = $(DebugOut_cpp:.cpp=.o)
#*/

Markov_cpp = $(wildcard $(SRC)/Markov/*.cpp)
Markov = $(Markov_cpp:.cpp=.o)
#*/

Stopwatch_cpp = $(wildcard $(SRC)/Stopwatch/*.cpp)
Stopwatch = $(Stopwatch_cpp:.cpp=.o)
#*/

String_cpp = $(wildcard $(SRC)/String/*.cpp)
String = $(String_cpp:.cpp=.o)
#*/

Math_cpp = $(wildcard $(SRC)/Math/*.cpp)
Math = $(Math_cpp:.cpp=.o)
#*/

LazyLoad_cpp = $(wildcard $(SRC)/LazyLoad/*.cpp)
LazyLoad = $(LazyLoad_cpp:.cpp=.o)
#*/

Sleep_cpp = $(wildcard $(SRC)/Sleep/*.cpp)
Sleep = $(Sleep_cpp:.cpp=.o)
#*/

NeuralNet_cpp = $(wildcard $(SRC)/NeuralNet/*.cpp) $(wildcard $(SRC)/NeuralNet/**/*.cpp)
NeuralNet = $(NeuralNet_cpp:.cpp=.o)
#*/

CSV_cpp = $(wildcard $(SRC)/CSV/*.cpp)
CSV = $(CSV_cpp:.cpp=.o)
#*/

Raytracer_cpp = $(wildcard $(SRC)/Raytracer/*.cpp) $(wildcard $(SRC)/Raytracer/**/*.cpp)
Raytracer = $(Raytracer_cpp:.cpp=.o)
#*/

Rules_cpp = $(wildcard $(SRC)/Rules/*.cpp)
Rules = $(Rules_cpp:.cpp=.o)
#*/

English_cpp = $(wildcard $(SRC)/English/**/*.cpp) $(wildcard $(SRC)/English/*.cpp)
English = $(English_cpp:.cpp=.o)
#*/

CLIPS_cpp = $(wildcard $(SRC)/CLIPS/*.cpp)
CLIPS = $(CLIPS_cpp:.cpp=.o)
#*/

SQL_cpp = $(wildcard $(SRC)/SQL/**/*.cpp) $(wildcard $(SRC)/SQL/*.cpp)
SQL = $(SQL_cpp:.cpp=.o)
#*/

Multi_cpp = $(wildcard $(SRC)/Multi/**/*.cpp) $(wildcard $(SRC)/Multi/*.cpp)
Multi = $(Multi_cpp:.cpp=.o)
#*/

Network_cpp = $(wildcard $(SRC)/Network/**/*.cpp) $(wildcard $(SRC)/Network/*.cpp)
Network = $(Network_cpp:.cpp=.o)
#*/


libobjects = $(Func) $(NNST) $(DebugOut) $(Markov) $(Stopwatch) $(String) $(Math) $(LazyLoad) $(Sleep) $(NeuralNet) $(CSV) $(Raytracer) $(Rules) $(English) $(CLIPS) $(SQL) $(Multi) $(Network)


Tests_cpp = $(wildcard Tests/*.cpp)
Tests = $(Tests_cpp:.cpp=.o)
#*/
testobjects = Tests.o $(Tests)

NAMESPACE=QUtils

SQL_FLAGS = -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_DEFAULT_MEMSTATUS=0 -DSQLITE_DEFAULT_WAL_SYNCHRONOUS=1 -DSQLITE_DEFAULT_FOREIGN_KEYS=1


PREPROC_FLAGS = -D__NS__="$(NAMESPACE)"

PREPROC_FLAGS := $(PREPROC_FLAGS) -DSHORT_TEST

PREPROC_FLAGS := $(PREPROC_FLAGS) -DDEBUG

PREPROC_FLAGS := $(PREPROC_FLAGS) -DSEED

PREPROC_FLAGS := $(PREPROC_FLAGS) -DTEST_DEBUG

PREPROC_FLAGS := $(PREPROC_FLAGS) $(SQL_FLAGS)




WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -ftemplate-backtrace-limit=0

WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wno-unused-local-typedefs #-Wno-unused-variable -Wno-unused-but-set-variable 

WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wfatal-errors 

FLAGS = -I .

Deps_D = Deps

CLIPS_Dep = $(Deps_D)/Clips
Curlpp_Dep = -I $(Deps_D)/curlpp/include -L $(Deps_D)/curlpp

DEPS = -I $(Deps_D)/Castor -I ../ -I $(Deps_D)/sqlite3 -I $(Deps_D) -I $(CLIPS_Dep) -L $(Deps_D)/sqlite3 -L $(CLIPS_Dep) $(Curlpp_Dep)


LINKING = -lclips++ -lsqlite3 -lcurlpp -lcurl -lz -ljpeg






CXX = g++
CXXFLAGS = -std=c++17 -MMD -fpic -I . $(PREPROC_FLAGS) $(FLAGS) -Wno-sign-compare $(WARNINGS_ERRORS) -O0 $(DEPS)
CXXFLAGS := $(CXXFLAGS) -Wall
libdeps = $(libobjects:.o=.d)
testdeps = $(testobjects:.o=.d)
name = Utility
stLibTarget = lib$(name)
target = $(name)Tests.out

buildOC = gcc -std=c99 -c -pie


$(target): $(stLibTarget).a $(testobjects) makefile $(libobjects)
	$(CXX) -o $(target) $(CXXFLAGS) -std=c++11 $(testobjects) -L. -l$(name) $(PREPROC_FLAGS) $(LINKING)
	$(NM) -C Tests/Nth_Poly.o >> tests.obj.txt
	

clean: 
	rm $(libobjects)


$(stLibTarget).a: $(libobjects)
	ar rvs $(stLibTarget).a $(libobjects)
	
Tests.o: makefile Tests.cpp
	$(CXX) $(CXXFLAGS) -c Tests.cpp

-include $(libdeps)
-include $(testdeps)