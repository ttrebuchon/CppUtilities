HAS_CURL = TRUE
HAS_BOOST = TRUE
NEEDS_PTHREAD = FALSE
HAS_SDL2 = FALSE #TRUE

HIDE_SDL_UNAVAILABLE = FALSE #TRUE

DEBUG=TRUE


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

Graphics_cpp = $(wildcard $(SRC)/Graphics/**/*.cpp) $(wildcard $(SRC)/Graphics/*.cpp)
Graphics = $(Graphics_cpp:.cpp=.o)
#*/

Guid_cpp = $(wildcard $(SRC)/GUID/**/*.cpp) $(wildcard $(SRC)/GUID/*.cpp)
Guid = $(Guid_cpp:.cpp=.o)
#*/

GUI_cpp = $(wildcard $(SRC)/GUI/**/*.cpp) $(wildcard $(SRC)/GUI/*.cpp)
GUI = $(GUI_cpp:.cpp=.o)
#*/

Output_cpp = $(wildcard $(SRC)/Output/**/*.cpp) $(wildcard $(SRC)/Output/*.cpp)
Output = $(Output_cpp:.cpp=.o)
#*/

Drawing_SDL_cpp = $(wildcard $(SRC)/Drawing/SDL/**/*.cpp) $(wildcard $(SRC)/Drawing/SDL/*.cpp)
Drawing_SDL = $(Drawing_SDL_cpp:.cpp=.o)
#*/

CodeGen_cpp = $(wildcard $(SRC)/CodeGen/**/*.cpp) $(wildcard $(SRC)/CodeGen/**/**/*.cpp) $(wildcard $(SRC)/CodeGen/**/**/**/*.cpp) $(wildcard $(SRC)/CodeGen/*.cpp)
CodeGen = $(CodeGen_cpp:.cpp=.o)
#*/


objects = $(Func) $(NNST) $(DebugOut) $(Markov) $(Stopwatch) $(String) $(Math) $(LazyLoad) $(Sleep) $(NeuralNet) $(CSV) $(Raytracer) $(Rules) $(English) $(CLIPS) $(SQL) $(Multi) $(Network) $(Graphics) $(Guid) $(GUI) $(Output) $(Drawing_SDL) $(CodeGen)


NAMESPACE=QUtils

SQL_FLAGS = -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_DEFAULT_MEMSTATUS=0 -DSQLITE_DEFAULT_WAL_SYNCHRONOUS=1 -DSQLITE_DEFAULT_FOREIGN_KEYS=1


PREPROC_FLAGS = -D__NS__="$(NAMESPACE)"


ifeq ($(DEBUG), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DDEBUG
endif

PREPROC_FLAGS := $(PREPROC_FLAGS) $(SQL_FLAGS)

PREPROC_FLAGS := $(PREPROC_FLAGS) #-DPRINT_SQL_QUERIES

ifeq ($(HIDE_SDL_UNAVAILABLE), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_SDL_HIDE_NOT_AVAILABLE
endif






ifeq ($(HAS_CURL), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_CURL
endif

ifeq ($(HAS_BOOST), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_BOOST
endif

ifeq ($(HAS_SDL2), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_SDL2
endif




WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -ftemplate-backtrace-limit=0

WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-but-set-variable 

WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wfatal-errors 

FLAGS = -I .

Deps_D = Deps

CLIPS_Dep = $(Deps_D)/CLIPS
Curlpp_Dep = -I $(Deps_D)/curlpp/include -L $(Deps_D)/curlpp

DEPS = -I $(Deps_D)/Castor -I ../ -I $(Deps_D)/sqlite3 -I $(Deps_D) -I $(CLIPS_Dep) -L $(CLIPS_Dep)

ifeq ($(HAS_CURL), TRUE)
DEPS := $(DEPS) $(Curlpp_Dep)
endif

LINKING = -lclips++ -lz -ljpeg -ldl

ifeq ($(HAS_CURL), TRUE)
LINKING := $(LINKING) #-lcurlpp
LINKING := $(LINKING) -lcurl
endif

ifeq ($(NEEDS_PTHREAD), TRUE)
LINKING := $(LINKING) -lpthread
endif

ifeq ($(HAS_SDL2), TRUE)
LINKING := $(LINKING) -lSDL2 -ltiff -lSDL2_ttf
endif


INCLUDED_LIBS = ../$(Deps_D)/sqlite3/libsqlite3.a ../$(Deps_D)/CLIPS/libclips++.a

ifeq ($(HAS_CURL), TRUE)
INCLUDED_LIBS := $(INCLUDED_LIBS) ../$(Deps_D)/curlpp/libcurlpp.a
endif

CURLPP_DEP = 

ifeq ($(HAS_CURL), TRUE)
CURLPP_DEP = Deps/curlpp/libcurlpp.a
endif


#CXX = g++
CXXFLAGS = -std=c++14 -MMD -fpic -I . $(PREPROC_FLAGS) $(FLAGS) -Wno-sign-compare $(WARNINGS_ERRORS) -Og
CXXFLAGS := $(CXXFLAGS) -Wall
deps = $(objects:.o=.d)
name = Utility
target = lib$(name).a

buildOC = gcc -std=c99 -c -pie

all: $(target) UtilityTests.out
	(cd Tests ; $(MAKE) $(MAKEFLAGS) HAS_CURL="$(HAS_CURL)" HAS_BOOST="$(HAS_BOOST)" NEEDS_PTHREAD="$(NEEDS_PTHREAD)" HAS_SDL2="$(HAS_SDL2)" DEBUG="$(DEBUG)")
	@cp Tests/UtilityTests.out .
	@echo SUCCESS
	@sleep 0.9


$(target): $(objects) makefile $(CURLPP_DEP)
	@[ -d objs ] || mkdir objs
	@cd objs ; $(foreach lib,$(INCLUDED_LIBS), ar -xv $(lib) ; )
	ar rvs $(target) $(wildcard objs/*.o) $(objects)
	#*/)

ifeq ($(HAS_CURL), TRUE)
$(CURLPP_DEP):
	(cd Deps/curlpp ; $(MAKE) $(MAKEFLAGS))
endif

UtilityTests.out: $(target)
	(cd Tests ; $(MAKE) $(MAKEFLAGS) HAS_CURL="$(HAS_CURL)" HAS_BOOST="$(HAS_BOOST)" NEEDS_PTHREAD="$(NEEDS_PTHREAD)" HAS_SDL2="$(HAS_SDL2)" DEBUG="$(DEBUG)")
	@cp Tests/UtilityTests.out .
	

clean:
	rm -f $(objects)
	rm -f $(objects:.o=.d)
	(cd Tests; make clean)
	@rm UtilityTests.out || echo
	rm $(target)


src/Graphics/Images/JPG_boost.o: src/Graphics/Images/JPG_boost.cpp QUtils/Graphics/Images/JPG_PCH.h QUtils/Graphics/Images/JPG_PCH.h.gch
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(DEPS)

QUtils/Graphics/Images/JPG_PCH.h.gch: QUtils/Graphics/Images/JPG_PCH.h
	$(CXX) $(CXXFLAGS) $^ -I .. -o $@ $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(DEPS)
	

-include $(deps)