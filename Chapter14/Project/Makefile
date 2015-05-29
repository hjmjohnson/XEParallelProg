## TODO: EDIT next set of lines according to OS

include windows.inc
#include linux.inc

## -------------- DO NOT EDIT BELOW THIS LINE -------------
LD=$(CC)
DEFINES =
DEFAULT_CFLAGS = -O2 $(DBINFO) $(NOINLINE)
LFLAGS = $(DBINFO)
OBJS = hash.$(OBJ) main.$(OBJ) n-bodies.$(OBJ) print.$(OBJ) octree.$(OBJ) wtime.$(OBJ)
LIBS =
TARGET = main
.cpp.$(OBJ):
	$(CC) -c $(DEFINES) $(INCLUDES) $(DEFAULT_CFLAGS) $(CFLAGS) $<

.c.$(OBJ):
	$(CC) -c $(DEFINES) $(INCLUDES) $(DEFAULT_CFLAGS) $(CFLAGS) $<

$(TARGET).exe:$(OBJS) body.h config.h hash.h octree.h print.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -o $@

$(TARGET).debug.exe:$(OBJS) body.h config.h hash.h octree.h print.h Makefile
	$(LD) $(LFLAGS) $(OBJS) $(LIBS) -O0 $(NOINLINE) -o $@




# The initial serial code
#---------------------------------------------------------------------------
14-1:
	$(MAKE) TARGET=14-1 CFLAGS="-DSERIAL -DUSE_1024_WORLD"
	
# The octree
#---------------------------------------------------------------------------
14-2: 
	$(MAKE) TARGET=14-2 CFLAGS="-DOCTREE -DUSE_1024_WORLD"
	
# The hashed octree
#---------------------------------------------------------------------------
14-3:
	$(MAKE) TARGET=14-3 CFLAGS="-DHASHTREE -DUSE_1024_WORLD"
	
# Optimize the division
#---------------------------------------------------------------------------
14-4:
	$(MAKE) TARGET=14-4 CFLAGS="-DHASHTREE -DUSE_1024_WORLD -DUSE_RECIPROCAL_DIVIDE"

# First parallel implementation 
#---------------------------------------------------------------------------
14-5:
	$(MAKE) TARGET=14-5 CFLAGS="-DHASHTREE -DUSE_1024_WORLD -DUSE_RECIPROCAL_DIVIDE -DUSE_CILK"

# Reduced count for checking dataraces
#---------------------------------------------------------------------------
14-6a:
	$(MAKE) TARGET=14-6a.debug CFLAGS="$(NOOPT) -DHASHTREE -DUSE_256_WORLD -DUSE_RECIPROCAL_DIVIDE -DUSE_CILK"
#	$(MAKE) TARGET=14-6a.debug CFLAGS="$(NOOPT) -DHASHTREE -DUSE_256_WORLD -DUSE_RECIPROCAL_DIVIDE -DUSE_CILK -DMIN_GRAIN_SIZE"

# Fix the data race using cilk reducers
#---------------------------------------------------------------------------
14-6b:
	$(MAKE) TARGET=14-6b.debug CFLAGS="$(NOOPT)  -DHASHTREE -DUSE_256_WORLD -DUSE_RECIPROCAL_DIVIDE -DUSE_CILK -DUSE_CILK_REDUCER"


# Final version
#---------------------------------------------------------------------------
14-7: 	
	$(MAKE) TARGET=14-7 CFLAGS="-DHASHTREE -DUSE_1024_WORLD -DUSE_RECIPROCAL_DIVIDE -DUSE_CILK -DUSE_CILK_REDUCER"

#---------------------------------------------------------------------------
clean:
	$(DEL) $(OBJS)
	$(DEL) $(TARGET).debug.exe
	$(DEL) $(TARGET).exe

nuke:
	$(DEL) $(OBJS)
	$(DEL) *.exe
	$(DEL) *.pdb
	$(DEL) *.dyn
	$(DEL) *.dpi
	$(DEL) *.lock
	$(DEL) *.asm
	$(DEL) *.s
	$(DEL) *.$(OBJ)
