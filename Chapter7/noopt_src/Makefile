## This is a makefile for chapter 7 no optimization examples. 
##

IDIR = ../src
CXX = icpc

## -g: generate debug information
## -inline-level=1: disables inlining (=0 disables all inlineing)

CXXFLAGS = -I$(IDIR) -std=c++11  -g -inline-level=1

LIBS = -lm

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = funct.o linkl.o pipel.o recur.o

all: funct linkl pipel recur

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

funct: funct.o
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

help:
	echo "loopprofileviewer.sh loop_prof_*.xml"

#	echo "cat log_run* |grep \"Time_to_calc\" |awk -F: \'{sum+=\\$2} END {print sum}\'"
