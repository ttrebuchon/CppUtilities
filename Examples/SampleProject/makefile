#Project-Specific

QUTILS_PATH = ../../
QUTILS_LIB = Utility

objects_cpp = $(wildcard *.cpp)
objects = $(objects_cpp:.cpp=.o)


#General
#HAS_CURL = TRUE
#HAS_BOOST = TRUE
#NEEDS_PTHREAD = FALSE
#HAS_SDL2 = TRUE



#ifeq ($(HAS_CURL), TRUE)
#PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_CURL
#endif

#ifeq ($(HAS_BOOST), TRUE)
#PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_BOOST
#endif

#ifeq ($(HAS_SDL2), TRUE)
#PREPROC_FLAGS := $(PREPROC_FLAGS) -DQUTILS_HAS_SDL2
#endif




#WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -ftemplate-backtrace-limit=0

#WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-but-set-variable 

#WARNINGS_ERRORS := $(WARNINGS_ERRORS) -Wfatal-errors 

QUTILS_FLAGS = -I $(QUTILS_PATH) -L $(QUTILS_PATH)

#Deps_D = Deps

#CLIPS_Dep = $(Deps_D)/CLIPS
#Curlpp_Dep = -I $(Deps_D)/curlpp/include -L $(Deps_D)/curlpp

#DEPS = -I $(Deps_D)/Castor -I ../ -I $(Deps_D)/sqlite3 -I $(Deps_D) -I $(CLIPS_Dep) -L $(Deps_D)/sqlite3 -L $(CLIPS_Dep)

#ifeq ($(HAS_CURL), TRUE)
#DEPS := $(DEPS) $(Curlpp_Dep)
#endif

#LINKING = -lclips++ -lsqlite3 -lz -ljpeg -ldl

#ifeq ($(HAS_CURL), TRUE)
#LINKING := $(LINKING) -lcurlpp -lcurl
#endif

#ifeq ($(NEEDS_PTHREAD), TRUE)
#LINKING := $(LINKING) -lpthread
#endif

#ifeq ($(HAS_SDL2), TRUE)
#LINKING := $(LINKING) -lSDL2
#endif



CXX = g++
#CXXFLAGS = -std=c++17 -MMD -fpic -I . $(PREPROC_FLAGS) $(FLAGS) -Wno-sign-compare $(WARNINGS_ERRORS) -O0 $(DEPS)
CXXFLAGS = -std=c++17 -MMD -fpic -O0 $(QUTILS_FLAGS)
CXXFLAGS := $(CXXFLAGS) -Wall 
deps = $(objects:.o=.d)
target = SampleName.out

buildOC = gcc -std=c99 -c -pie


$(target): $(objects) makefile
	$(CXX) -o $(target) $(CXXFLAGS) $(objects) $(LINKING) -l$(QUTILS_LIB) -lcurl -lz 




-include $(deps)