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

CXXFLAGS = -I$(IDIR) -O2 -ipo -g -profile-functions -profile-loops:all -profile-loops-report:2 -qopt-report-phase=ipo -opt-report-routine=main 
## -O2: optimize for speed
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -profile-functions: track time for functions
## -profile-loops:all: track time for inner and outer loops
## -profile-loops-report:2: level of detail in report, 2 reports loop times and iteration counts
## -qopt-report-phase=ipo: specifies which optimization phase to generate reports for
## -opt-report-routine=main: specifies which routime to geneerate an optimization report for (if it contains substring "main")

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
