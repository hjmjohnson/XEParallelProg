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
##	 $ source compilervars.sh intel64

IDIR = ../src
CXX = icpc

## -O2: optimize for speed
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -inline-level=1: disables inlining (=0 disables all inlineing)

CXXFLAGS = -I$(IDIR) -std=c++11 -O2 -xHOST -ipo -g -inline-level=1 -openmp

PROG=64b.exe

LIBS = -lm

_DEPS = mandelbrot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = mandelbrot.o main.o ppm.o

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~

test: $(PROG)
	./$(PROG) |tee log_run1
	./$(PROG) |tee log_run2
	./$(PROG) |tee log_run3
	./$(PROG) |tee log_run4
	./$(PROG) |tee log_run5
	cat log_run*

help:
	echo "loopprofileviewer.sh loop_prof_*.xml"

#	echo "cat log_run* |grep \"Time_to_calc\" |awk -F: \'{sum+=\\$2} END {print sum}\'"
