#User Preference/Build Options
HAS_CURL = TRUE
HAS_BOOST = TRUE
NEEDS_PTHREAD = FALSE
HAS_SDL2 = FALSE #TRUE

HIDE_SDL_UNAVAILABLE = FALSE #TRUE
BOOST_DIR = ../boostLib

DEBUG=TRUE


SRC = src

#Custom Functions
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

getobjs = $(patsubst %.cpp,%.o,$(call rwildcard,$1,*.cpp))



#Module Object Variables
Func = $(call getobjs,$(SRC)/Func/)

NNST = $(call getobjs,$(SRC)/NearestNeighborTree/)

DebugOut = $(call getobjs,$(SRC)/DebugOut/)

Markov = $(call getobjs,$(SRC)/Markov/)

Stopwatch = $(call getobjs,$(SRC)/Stopwatch/)

String = $(call getobjs,$(SRC)/String/)

Math = $(call getobjs,$(SRC)/Math/)

LazyLoad = $(call getobjs,$(SRC)/LazyLoad/)

Sleep = $(call getobjs,$(SRC)/Sleep/)

NeuralNet = $(call getobjs,$(SRC)/NeuralNet/)

CSV = $(call getobjs,$(SRC)/CSV/)

Raytracer = $(call getobjs,$(SRC)/Raytracer/)

Rules = $(call getobjs,$(SRC)/Rules/)

English = $(call getobjs,$(SRC)/English/)

CLIPS = $(call getobjs,$(SRC)/CLIPS/)

SQL = $(call getobjs,$(SRC)/SQL/)

Multi = $(call getobjs,$(SRC)/Multi/)

Network = $(call getobjs,$(SRC)/Network/)

Graphics = $(call getobjs,$(SRC)/Graphics/)

Guid = $(call getobjs,$(SRC)/GUID/)

GUI = $(call getobjs,$(SRC)/GUI/)

Output = $(call getobjs,$(SRC)/Output/)

Drawing_SDL = $(call getobjs,$(SRC)/Drawing/SDL/)

CodeGen = $(call getobjs,$(SRC)/CodeGen/)

Genetic = $(call getobjs,$(SRC)/Genetic/)

Serialization = $(call getobjs,$(SRC)/Serialization/)


objects = $(Func) $(NNST) $(DebugOut) $(Markov) $(Stopwatch) $(String) $(Math) $(LazyLoad) $(Sleep) $(NeuralNet) $(CSV) $(Raytracer) $(Rules) $(English) $(CLIPS) $(SQL) $(Multi) $(Network) $(Graphics) $(Guid) $(GUI) $(Output) $(Drawing_SDL) $(CodeGen) $(Genetic) $(Serialization)


#Namespace name, used once (Not important)
NAMESPACE=QUtils

#Flags for SQLite
SQL_FLAGS = -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_DEFAULT_MEMSTATUS=0 -DSQLITE_DEFAULT_WAL_SYNCHRONOUS=1 -DSQLITE_DEFAULT_FOREIGN_KEYS=1


PREPROC_FLAGS = -D__NS__="$(NAMESPACE)"


ifeq ($(DEBUG), TRUE)
PREPROC_FLAGS += -DDEBUG
endif

PREPROC_FLAGS += $(SQL_FLAGS)

PREPROC_FLAGS += #-DPRINT_SQL_QUERIES

ifeq ($(HIDE_SDL_UNAVAILABLE), TRUE)
PREPROC_FLAGS += -DQUTILS_SDL_HIDE_NOT_AVAILABLE
endif






ifeq ($(HAS_CURL), TRUE)
PREPROC_FLAGS += -DQUTILS_HAS_CURL
endif

ifeq ($(HAS_BOOST), TRUE)
PREPROC_FLAGS += -DQUTILS_HAS_BOOST
endif

ifeq ($(HAS_SDL2), TRUE)
PREPROC_FLAGS += -DQUTILS_HAS_SDL2
endif


#Defined on separate lines to make it easier
# to comment out specific options for debugging

WARNINGS_ERRORS = -Werror -Wno-error=sign-compare -ftemplate-backtrace-limit=0

WARNINGS_ERRORS += -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-but-set-variable 

WARNINGS_ERRORS += -Wfatal-errors 

FLAGS = -I .

Deps_D = Deps

CLIPS_Dep = $(Deps_D)/CLIPS
Curlpp_Dep = -I $(Deps_D)/curlpp/include -L $(Deps_D)/curlpp

DEPS = -I $(Deps_D)/Castor -I $(BOOST_DIR) -I $(Deps_D)/sqlite3 -I $(Deps_D) -I $(CLIPS_Dep) -L $(CLIPS_Dep)

ifeq ($(HAS_CURL), TRUE)
DEPS += $(Curlpp_Dep)
endif

LINKING = -lclips++ -lz -ljpeg -ldl

ifeq ($(HAS_CURL), TRUE)
LINKING += -lcurl
endif

ifeq ($(NEEDS_PTHREAD), TRUE)
LINKING += -lpthread
endif

ifeq ($(HAS_SDL2), TRUE)
LINKING += -lSDL2 -ltiff -lSDL2_ttf
endif

SQLITE3_LIB = $(Deps_D)/sqlite3/libsqlite3.a

CLIPS_LIB = $(Deps_D)/CLIPS/libclips++.a


ifeq ($(HAS_CURL), TRUE)
CURLPP_LIB = $(Deps_D)/curlpp/libcurlpp.a
endif


INCLUDED_LIBS = $(SQLITE3_LIB) $(Deps_D)/CLIPS/libclips++.a $(CURLPP_LIB)

TESTS_MAKE_FLAGS = $(MAKEFLAGS) HAS_CURL="$(HAS_CURL)" HAS_BOOST="$(HAS_BOOST)" NEEDS_PTHREAD="$(NEEDS_PTHREAD)" HAS_SDL2="$(HAS_SDL2)" DEBUG="$(DEBUG)" BOOST_DIR="$(BOOST_DIR)"



CXXFLAGS = -std=c++14 -MMD -fpic -I . $(PREPROC_FLAGS) $(FLAGS) -Wno-sign-compare $(WARNINGS_ERRORS) -Og
CXXFLAGS += -Wall
deps = $(objects:.o=.d)
name = Utility
target = lib$(name).a

buildOC = gcc -std=c99 -c -pie

all: $(target) UtilityTests.out
	@cp Tests/UtilityTests.out .
	@echo SUCCESS
	@sleep 0.9

$(target): $(objects) makefile $(CURLPP_LIB) $(SQLITE3_LIB) $(CLIPS_LIB)
	echo BUILDING TARGET!
	-mkdir objs
	cd objs ; $(foreach lib,$(INCLUDED_LIBS), ar -xv ../$(lib) ; )
	$(eval TMP := objs/*.o)
	ar rvs $(target) $(TMP) $(objects)
	#*/)

ifeq ($(HAS_CURL), TRUE)
$(CURLPP_LIB):
	(cd $(Deps_D)/curlpp ; $(MAKE) $(MAKEFLAGS))
endif

$(SQLITE3_LIB): 
	(cd Deps/sqlite3 ; $(MAKE) $(MAKEFLAGS))

$(CLIPS_LIB):
	(cd $(Deps_D)/CLIPS ; $(MAKE) $(MAKEFLAGS))

UtilityTests.out: $(target) makefile Tests/makefile FORCE
	(cd Tests ; $(MAKE) $(TESTS_MAKE_FLAGS))
	@cp Tests/UtilityTests.out .

FORCE: 
	

clean:
	-@rm -f $(objects)
	-@rm -f $(objects:.o=.d)
	(cd Tests; make clean)
	-@rm UtilityTests.out
	-@rm $(target)


src/Graphics/Images/JPG_boost.o: src/Graphics/Images/JPG_boost.cpp QUtils/Graphics/Images/JPG_PCH.h QUtils/Graphics/Images/JPG_PCH.h.gch
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(DEPS)

QUtils/Graphics/Images/JPG_PCH.h.gch: QUtils/Graphics/Images/JPG_PCH.h
	$(CXX) $(CXXFLAGS) $^ -I .. -o $@ $(DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(DEPS)
	

-include $(deps)