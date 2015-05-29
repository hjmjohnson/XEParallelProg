## This is a makefile for activity 6.1 page 158 of text book.
## http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
##
## Add instructions for how to build on Linux with ICXX
##
## http://www.gnu.org/software/make/manual/make.html#Automatic-Variables

IDIR = ../src
CXX = clang++
## TODO use mapopts to convert flags manually from text book
## Add a note here for each flag describing it's use
CXXFLAGS = -I$(IDIR) -O0

ODIR61 = obj61
LDIR = obj61

LIBS = -lm

_DEPS = mandelbrot.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = mandelbrot.o main.o ppm.o wtime.o

%.o: ../src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

61.exe: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR61)/*.o *~ core $(INCDIR)/*~
