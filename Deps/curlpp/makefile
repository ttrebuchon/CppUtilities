
SRC = $(wildcard src/curlpp/*.cpp) $(wildcard src/curlpp/internal/*.cpp)
#*/

SRCDEPS = $(SRC:.cpp=.d)

CXXFLAGS = -MMD -fpic -I include

OBJS = $(SRC:.cpp=.o)

libcurlpp.a: $(OBJS)
	ar rvs libcurlpp.a $(OBJS)

#.cpp.o:
#	$(CXX) $(CXXFLAGS) -I include -c $<

-include $(SRCDEPS)