CXX = g++
CXXFLAGS = -g -Wall -std=gnu++11
SHELL = bash

all: mud

mud: mud.o player.o inventory.o rooms.o enemies.o
	$(CXX) $(CXXFLAGS) -o $@ $^

mud.o:	mud.cpp
	$(CXX) $(CXXFLAGS) -c mud.cpp

player.o:  player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

inventory.o:	inventory.cpp inventory.h
	$(CXX) $(CXXFLAGS) -c inventory.cpp

rooms.o:	rooms.cpp rooms.h
	$(CXX) $(CXXFLAGS) -c rooms.cpp

enemies.o: enemies.cpp enemies.h
	$(CXX) $(CXXFLAGS) -c enemies.cpp

clean:
	rm -f *.o mud
