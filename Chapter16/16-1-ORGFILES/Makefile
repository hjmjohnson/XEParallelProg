## TODO: EDIT next set of lines according to OS

include ../CONFIG/windows.inc
#include ../CONFIG/linux.inc


## -------------- APPLICATION CONFIG -------------
LOOPCOUNT = 100000000
LOOPCOUNTDATARACE = 1000


## -------------- DO NOT EDIT BELOW THIS LINE -------------
LD=$(CC)
DEFINES = -DTIME 
DEFAULT_CFLAGS = -O2 $(DBINFO)
LFLAGS = 
OBJS = dhry_1.$(OBJ) dhry_2.$(OBJ)
LIBS = $(VTUNELIB)
TARGET = main
.cpp.$(OBJ):
	$(CC) -c $(DEFINES) $(INCLUDES) $(DEFAULT_CFLAGS) $(CFLAGS) $<

.c.$(OBJ):
	$(CC) -c $(DEFINES) $(INCLUDES) $(DEFAULT_CFLAGS) $(CFLAGS) $<

$(TARGET).exe:$(OBJS) dhry.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $@

$(TARGET).debug.exe:$(OBJS) dhry.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -O0 $(NOINLINE) -o $@

$(TARGET).idb.exe:$(OBJS) dhry.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -O0 $(NOINLINE) -o $@

#---------------------------------------------------------------------------
idbx:$(TARGET).idb.exe
	idb $(TARGET).idb.exe $(LOOPCOUNT) &

idb:
	$(MAKE) idbx CFLAGS="$(NOOPT) $(DBINFO)"


#---------------------------------------------------------------------------
benchmark:$(TARGET).exe
	$(TARGET).exe $(LOOPCOUNT)


#---------------------------------------------------------------------------
hotspot:$(TARGET).exe
	amplxe-cl -collect hotspots -follow-child -mrte-mode=auto \
	-target-duration-type=short -no-allow-multiple-runs -no-analyze-system \
	-data-limit=100 -slow-frames-threshold=40 -fast-frames-threshold=100 -- \
	./$(TARGET).exe $(LOOPCOUNT)
	amplxe-cl -R hotspots -group-by task 

#---------------------------------------------------------------------------
concurrency:$(TARGET).exe
	amplxe-cl -collect concurrency -knob collect-signals=true -follow-child \
	-mrte-mode=auto -target-duration-type=short -no-allow-multiple-runs -no-analyze-system \
	-data-limit=100 -slow-frames-threshold=40 -fast-frames-threshold=100 -- \
	./$(TARGET).exe $(LOOPCOUNT)

#---------------------------------------------------------------------------
dataracex:$(TARGET).debug.exe
	inspxe-cl -collect ti2 -knob terminate-on-deadlock=false -knob stack-depth=1 \
	-knob appdebug=off -suppressions=delete -module-filter-mode=include -- \
	./$(TARGET).debug.exe $(LOOPCOUNTDATARACE)
	inspxe-cl -R problems &

datarace:
	$(MAKE) dataracex CFLAGS="$(NOOPT) $(DBINFO)"

#---------------------------------------------------------------------------
clean:
	$(DEL) $(OBJS)
	$(DEL) $(TARGET).debug.exe
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
	$(DEL) *.$(OBJ)

cleanhs:
	$(RM) r???hs

cleancc:
	$(RM) r*cc

cleanti:
	$(RM) r???ti?

nuke:
	$(MAKE) reallyclean
	$(MAKE) cleanhs
	$(MAKE) cleanti
	$(MAKE) cleancc
	$(DEL) *~

