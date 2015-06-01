## This is a makefile for activity 6.4 page 173 of text book.
## http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
##
## Add instructions for how to build on Linux with ICXX
##
## http://www.gnu.org/software/make/manual/make.html#Automatic-Variables
##
## Setting up the Intel Compiler:
##  -Find the compilervars.sh script in the composer xe bin
##  -Default location on Medusa is /opt/intel/composer_xe_2015/bin/compilervars.sh
##  -Source this script with intel64 as the argument:
##       $ source compilervars.sh intel64

IDIR = ../src
CXX = icpc

## -O2: optimize for speed
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -inline-level=1: disables inlining (=0 disables all inlineing)

CXXFLAGS = -I$(IDIR) -std=c++11 -O2 -xHOST -ipo -g -inline-level=1

LIBS = -lm

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = funct_b.o funct_c.o linkl.o recur.o

all: funct_b funct_c linkl recur

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

funct_b: funct_b.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
funct_c: funct_c.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
linkl: linkl.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
recur: recur.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~
