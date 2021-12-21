SOURCEDIR = src
INCLUDEDIR = includes
SOURCES = $(shell find $(SOURCEDIR) -name '*.cc')
OBJECTS = $(SOURCES:.cc=.o)

AR = ar
CXX = g++
CFLAGS = -Wall -g -std=c++17 -I $(INCLUDEDIR)

all: main

%.o: %.cc # Create Object Files
	$(CXX) $(CFLAGS) -c $< -o $@

main: main.cc $(OBJECTS)
	$(CXX) $(CFLAGS) -c $< -o $@.o
	$(CXX) $(CFLAGS) -o $@ $@.o $(OBJECTS)
	rm -f $(OBJECTS) $@.o

clean: 
	rm -f main