CXX = g++
CXXFLAGS = -g -Wall -std=gnu++11
SHELL = bash

all: mud

mud: mud.o player.o bag.o room.o enemies.o
	$(CXX) $(CXXFLAGS) -o $@ $^

mud.o:	mud.cpp
	$(CXX) $(CXXFLAGS) -c mud.cpp

player.o:  player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

bag.o:	bag.cpp bag.h
	$(CXX) $(CXXFLAGS) -c bag.cpp

room.o:	room.cpp room.h
	$(CXX) $(CXXFLAGS) -c room.cpp

enemies.o: enemies.cpp enemies.h
	$(CXX) $(CXXFLAGS) -c enemies.cpp

clean:
	rm -f *.o mud
