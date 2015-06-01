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

LIBS = -lm

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = Lambda.o


all: 01NoLambda.exe 02Lambda.exe 03Lambda_SeparateTasks.exe 04Lambda_MultiProcessor.exe

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

01NoLambda.exe: 01NoLambda.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	echo "=========== DOING $@"
	./$@

02Lambda.exe: 02Lambda.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	echo "=========== DOING $@"
	./$@

03Lambda_SeparateTasks.exe: 03Lambda_SeparateTasks.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	echo "=========== DOING $@"
	./$@

04Lambda_MultiProcessor.exe: 04Lambda_MultiProcessor.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)
	echo "=========== DOING $@"
	./$@

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~ log_run*

run: $(PROG)
	./$(PROG)
log_run1: $(PROG)
	./$(PROG) |tee log_run1
log_run2: $(PROG) log_run1
	./$(PROG) |tee log_run2

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
