## This is a makefile for activity 6.2 page 164 of text book.
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
## -xHost tune code to only run on this host archetecture
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -profile-functions: track time for functions
## -profile-loops:all: track time for inner and outer loops
## -profile-loops-report:2: level of detail in report, 2 reports loop times and iteration counts

CXXFLAGS = -I$(IDIR) -std=c++11 -O2 -xHOST -ipo -g -profile-functions -profile-loops:all -profile-loops-report:2

PROG=62a.exe

LIBS = -lm

_DEPS = mandelbrot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = mandelbrot.o main.o ppm.o wtime.o

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
