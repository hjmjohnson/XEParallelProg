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

CXX = icpc

## -O2: optimize for speed
## -ipo: enable interprocedural optimization
## -xHost tune code to only run on this host archetecture

CXXFLAGS = -std=c++11 -O2 -xHost -ipo

PROG=pi.exe

OBJ = main.o

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(PROG): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~
