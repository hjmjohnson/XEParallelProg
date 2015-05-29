## TODO: EDIT next set of lines according to OS

## WINDOWS OS specific vars.
CC=icl 
DEL=del
OBJ=obj

# LINUX SPECIFIC, uncomment these for LINUX
# CC=icc 
# DEL=rm -Rf
# OBJ=o


## -------------- DO NOT EDIT BELOW THIS LINE -------------
LD=$(CC)
CFLAGS = 
LFLAGS = 

OBJS = addy.$(OBJ) chapter4.$(OBJ) series.$(OBJ) work.$(OBJ) wtime.$(OBJ) 
TARGET = main
.c.$(OBJ):
	$(CC) -c $(CFLAGS) $<

$(TARGET).exe:$(OBJS) chapter4.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	$(DEL) $(OBJS)
	$(DEL) $(TARGET).exe

reallyclean:
	$(DEL) $(OBJS)
	$(DEL) *.exe
	$(DEL) *.pdb
	$(DEL) *.dyn
	$(DEL) *.dpi
	$(DEL) *.lock
	$(DEL) *.asm
	$(DEL) *.s

