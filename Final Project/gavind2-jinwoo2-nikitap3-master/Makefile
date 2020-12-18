EXENAME = safecovid
OBJS = safecovid.o person.o airportGraph.o main.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean

all : $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp safecovid.h person.h airportGraph.h
	$(CXX) $(CXXFLAGS) main.cpp

safecovid.o: safecovid.cpp safecovid.h
	$(CXX) $(CXXFLAGS) safecovid.cpp

person.o: person.cpp person.h
	$(CXX) $(CXXFLAGS) person.cpp

airportGraph.o: airportGraph.cpp airportGraph.h
	$(CXX) $(CXXFLAGS) airportGraph.cpp

test: tests.o safecovid.o person.o airportGraph.o
	$(LD) tests.o safecovid.o person.o airportGraph.o $(LDFLAGS) -o test

tests.o: tests/tests.cpp catch/catchmain.cpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp

clean:
	-rm -f *.o $(EXENAME) test
