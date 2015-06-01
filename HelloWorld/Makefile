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

CXX = icpc
## -std=c++11: Enables c++11 conformance
## -O2: optimize for speed
## -xHost tune code to only run on this host archetecture
## -ipo: enable interprocedural optimization
## -g: generate debug information
## -inline-level=1: disables inlining (=0 disables all inlineing)
## -openmp: enables openmp directives
CXXFLAGS = -std=c++11 -O2 -xHOST -ipo -g -inline-level=1 -openmp

all: HelloWorld.exe

%.o: ../src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

HelloWorld.exe: HelloWorld.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	echo "=========== DOING $@"
	./$@

.PHONY: clean
clean:
	rm -f *.o *~ core $(INCDIR)/*~ log_run*
