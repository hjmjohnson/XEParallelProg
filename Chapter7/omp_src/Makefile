## This is a makefile for chapter 7 openmp examples.
##

IDIR = ../src
CXX = icpc

## -O2: optimize for speed
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -inline-level=1: disables inlining (=0 disables all inlineing)

CXXFLAGS = -I$(IDIR) -std=c++11 -O2 -xHOST -ipo -g -inline-level=1 -openmp

LIBS = -lm

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = funct_b.o funct_c.o linkl.o pipel.o recur.o

all: funct_b funct_c linkl pipel recur

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

funct_b: funct_b.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
funct_c: funct_c.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
linkl: linkl.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
pipel: pipel.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
recur: recur.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~
