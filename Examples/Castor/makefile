WORKSPACE = ../../../..
LIBDIR = ../../Deps

CASTOR = -I $(LIBDIR)/Castor

CXXFLAGS = $(CASTOR) -std=c++17

OBJS = test.o famTest.o opTest.o famTest2.o tTest.o

test.out: $(OBJS) $(EO_D) makefile 
	$(CXX) -o test.out $(OBJS) $(CXXFLAGS)

.cpp.o:
	$(CXX) -std=c++17 -c $< $(CXXFLAGS)
	



#-include $(EODIR)/makefile
#-include $(LIBDIR)/tinyxml2/makefile