CXX=g++

CXXFLAGS=-g

ListSorter: ItemType.o listDriver.o unsorted.o
	$(CXX) $(CXXFLAGS) -o ListSorter ItemType.o listDriver.o unsorted.o

ItemType.o: ItemType.cpp ItemType.h

listDriver.o: listDriver.cpp unsorted.h

unsorted.o: unsorted.cpp unsorted.h