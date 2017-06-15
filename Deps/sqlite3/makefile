

CXX = g++
CXXFLAGS = -std=c++17 -MMD -fpic -I . $(PREPROC_FLAGS) -Wall $(FLAGS) -O3 -Wno-sign-compare $(WARNINGS_ERRORS)
name = sqlite3
target = lib$(name).a

buildOC = gcc -std=c99 -c -pie

$(target): sqlite3.o
	ar rvs $(target) $<

%.o.c: 
	$(buildOC) $<