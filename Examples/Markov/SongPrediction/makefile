objects_cpp = $(wildcard *.cpp)

objects = $(objects_cpp:.cpp=.o)




PREPROC_FLAGS = -DDEBUG -DSEED -DTEST_DEBUG

WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -Wfatal-errors

FLAGS = -I ../../../ -L../../../ -I tinyxml2 -L tinyxml2

CXX = g++
CXXFLAGS = -std=c++11 -MMD -fpic -I . $(PREPROC_FLAGS) -Wall $(FLAGS) -O3 -Wno-sign-compare $(WARNINGS_ERRORS) -DQUtils="Util"
deps = $(objects:.o=.d)
name = SongPrediction
target = $(name).out

buildOC = gcc -std=c99 -c -pie


$(target): ../../../libUtility.a $(objects) makefile
	$(CXX) -o $(target) $(CXXFLAGS) -std=c++11 $(objects) -ltinyxml2 #-lUtility
	

-include $(deps)