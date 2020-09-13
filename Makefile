CXX=g++

CXXFLAGS=-g

ListSorting: ItemType.o listDriver.o unsorted.o
	$(CXX) $(CXXFLAGS) -o ListSorting ItemType.o listDriver.o unsorted.o

ItemType.o: ItemType.cpp ItemType.h

listDriver.o: listDriver.cpp unsorted.h

unsorted.o: unsorted.cpp unsorted.h
