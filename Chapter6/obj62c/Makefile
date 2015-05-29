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
## CXX = clang++
CXX = icpc
## TODO use mapopts to convert flags manually from text book
## Add a note here for each flag describing it's use
CXXFLAGS = -I$(IDIR) -O2 -ipo -g -profile-functions -profile-loops:all -profile-loops-report:2 -qopt-report-phase=ipo -opt-report-routine=main 

ODIR61 = obj61
LDIR = obj61

LIBS = -lm

_DEPS = mandelbrot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = mandelbrot.o main.o ppm.o wtime.o

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

62.exe: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~
