SOURCEDIR = src
INCLUDEDIR = includes
LIBDIR = libs
SOURCES = $(shell find $(SOURCEDIR) -name '*.cc')
OBJECTS = $(SOURCES:.cc=.o)
LIB = $(subst .a,,$(subst $(LIBDIR)/lib,-l ,$(shell find $(LIBDIR) -name '*.a')))

AR = ar
CXX = g++
CFLAGS = -Wall -g -std=c++17 -I $(INCLUDEDIR)

all: main

%.o: %.cc # Create Object Files
	$(CXX) $(CFLAGS) -c $< -o $@

main: main.cc $(OBJECTS)
	$(CXX) $(CFLAGS) -c $< -o $@.o
	$(CXX) $(CFLAGS) $(OBJECTS) $@.o -o $@ -L $(LIBDIR) $(LIB)
	rm -f $(OBJECTS) $@.o

clean: 
	rm -f main