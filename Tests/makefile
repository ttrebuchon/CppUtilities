#HAS_CURL = TRUE
#HAS_BOOST = TRUE
#NEEDS_PTHREAD = FALSE
#HAS_SDL2 = FALSE #TRUE

HIDE_SDL_UNAVAILABLE = FALSE #TRUE


SRC = ../src


Tests_cpp = $(wildcard *.cpp)
Tests = $(Tests_cpp:.cpp=.o)
#*/
objects = ../Tests.o $(Tests)



PREPROC_FLAGS := $(PREPROC_FLAGS) -DSHORT_TEST

ifeq ($(DEBUG), TRUE)
PREPROC_FLAGS := $(PREPROC_FLAGS) -DDEBUG
endif

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

ifeq ($(HAS_BOOST), TRUE)
FLAGS += -I ../$(BOOST_DIR)
endif

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

ifeq ($(HAS_BOOST), TRUE)
LINKING += -L../$(BOOST_DIR)/libs/serialization -lboost_serialization
endif


INCLUDES = -I ../Deps/curlpp/include



#CXX = g++
CXXFLAGS = -std=c++14 -MMD -fpic $(PREPROC_FLAGS) $(FLAGS) $(WARNINGS_ERRORS) -Og $(INCLUDES)
testdeps = $(objects:.o=.d)
LIB = Utility
LIB_FILE = ../lib$(LIB).a
target = UtilityTests.out


$(target): $(objects) makefile ../Output/SrcTest.o ../lib$(LIB).a
	$(CXX) -o $(target) $(CXXFLAGS) $(objects) -L../ -l$(LIB) $(PREPROC_FLAGS) $(LINKING)
	

clean:
	rm -f $(objects)
	rm -f $(objects:.o=.d)


	
../Tests.o: ../Tests.cpp makefile 
	$(CXX) $(CXXFLAGS) -c -o $@ $<


-include $(testdeps)