## This is a makefile for activity 6.1 page 158 of text book.
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

CXXFLAGS = -I$(IDIR) -O2 -xHost -ipo
## -02: optimize for speed
## -ipo: enable interprocedural optimization
## -xHost tune code to only run on this host archetecture

PROG=61.exe

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

test: 62.exe
	./$(PROG) |tee log_run1
	./$(PROG) |tee log_run2
	./$(PROG) |tee log_run3
	./$(PROG) |tee log_run4
	./$(PROG) |tee log_run5
	cat log_run*
