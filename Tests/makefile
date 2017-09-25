#HAS_CURL = TRUE
#HAS_BOOST = TRUE
#NEEDS_PTHREAD = FALSE
#HAS_SDL2 = FALSE #TRUE

HIDE_SDL_UNAVAILABLE = FALSE #TRUE


SRC = ../src


Tests_cpp = $(wildcard *.cpp)
Tests = $(Tests_cpp:.cpp=.o)
#*/
testobjects = ../Tests.o $(Tests)



PREPROC_FLAGS := $(PREPROC_FLAGS) -DSHORT_TEST

PREPROC_FLAGS := $(PREPROC_FLAGS) -DDEBUG

PREPROC_FLAGS := $(PREPROC_FLAGS) -DSEED

PREPROC_FLAGS := $(PREPROC_FLAGS) -DTEST_DEBUG






ifeq ($(HAS_CURL), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_CURL
endif

ifeq ($(HAS_BOOST), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_BOOST
endif

ifeq ($(HAS_SDL2), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_SDL2
endif




WARNINGS_ERRORS = -ftemplate-backtrace-limit=0 -Wno-sign-compare

WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wfatal-errors 

FLAGS = -I ../

Deps_D = ../Deps

CLIPS_Dep = $(Deps_D)/CLIPS

LINKING = -lz -ljpeg -ldl

ifeq ($(HAS_CURL), TRUE)
LINKING := $(LINKING) -lcurl
endif

ifeq ($(NEEDS_PTHREAD), TRUE)
LINKING := $(LINKING) -lpthread
endif

ifeq ($(HAS_SDL2), TRUE)
LINKING := $(LINKING) -lSDL2 -ltiff -lSDL2_ttf
endif


INCLUDES = -I ../Deps/curlpp/include



CXX = g++
CXXFLAGS = -std=c++14 -MMD -fpic -I ../.. $(PREPROC_FLAGS) $(FLAGS) $(WARNINGS_ERRORS) -Og $(INCLUDES)
CXXFLAGS := $(CXXFLAGS) -Wall
testdeps = $(testobjects:.o=.d)
LIB = Utility
LIB_FILE = ../lib$(LIB).a
target = UtilityTests.out


$(target): $(testobjects) makefile ../Output/SrcTest.o ../lib$(LIB).a
	$(CXX) -o $(target) $(CXXFLAGS) $(testobjects) -L../ -l$(LIB) $(PREPROC_FLAGS) $(LINKING)
	

clean:
	rm -f $(testobjects)
	rm -f $(testobjects:.o=.d)


	
Tests.o: makefile ../Tests.cpp
	$(CXX) $(CXXFLAGS) -c Tests.cpp


-include $(testdeps)