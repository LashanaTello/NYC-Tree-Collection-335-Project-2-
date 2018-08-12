# Makefile for Project2
# Written by Stewart Weiss 
# This is designed for the second project in CSci 335, Spring 2018
# It assumes that the source files in the project are exactly those specified
# in the assignment: 
# main.cpp, tree_collection.cpp, tree_collection.h, tree.cpp, tree.h, avl.h
# avl.cpp, tree_species.h
# and that the dependencies are that main includes all header files and
# otherwise the remaining cpp files are independent (do not include any 
# header files other than there own.)
#
# Instructions:
# If you create other files, you need to modify this makefile.
#
# Type make to build the executable, which is named project2
# Type make clean to remove all .o files
# Type make cleanall to remove all .o files and the project2 executable.

# If you want to force a recompile, type "touch *.cpp" and then "make"

CXX       := /usr/bin/g++
CXXFLAGS  += -Wall -g -std=c++11

all: project2 

.PHONY: clean  cleanall
clean:
	rm -f main.o tree_collection.o tree.o avl.o 

cleanall:
	rm -f main.o tree_collection.o tree.o avl.o project2  
	
project2:  tree_collection.o tree.o main.o avl.o tree_species.o
	$(CXX) $(CXXFLAGS) -o project2  tree_collection.o tree.o main.o avl.o tree_species.o command.o

main.o: main.cpp tree_collection.h tree.h tree_species.h  command.h
	$(CXX) $(CXXFLAGS)  -c main.cpp

tree_collection.o: tree_collection.cpp tree_collection.h tree.h tree_species.h
	$(CXX) $(CXXFLAGS)  -c tree_collection.cpp

tree.o: tree.cpp tree.h
	$(CXX) $(CXXFLAGS) -c tree.cpp

avl.o: avl.cpp avl.h tree.h
	$(CXX) $(CXXFLAGS) -c avl.cpp
