## TODO: EDIT next set of lines according to OS

## WINDOWS OS specific vars.
CC=icl 
DEL=del
OBJ=obj
CFLAGS = /Od


# LINUX SPECIFIC, uncomment these for LINUX
# CC=icc 
# DEL=rm -Rf
# OBJ=o
# CFLAGS = -O0


## -------------- DO NOT EDIT BELOW THIS LINE -------------
LD=$(CC)
LFLAGS = 

OBJS = main.$(OBJ) test.$(OBJ)
TARGET = main
.c.$(OBJ):
    $(CC) -c $(CFLAGS) $<

$(TARGET).exe:$(OBJS)  Makefile
    $(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $@

clean:
    $(DEL) $(OBJS)
    $(DEL) $(TARGET).exe

