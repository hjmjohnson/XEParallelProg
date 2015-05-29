## WINDOWS OS specific vars.
VTUNEDIR=$(VTUNE_AMPLIFIER_XE_2011_DIR)
CC=icl 
DEL=del
RM=rmdir /s /q
OBJ=obj
NOINLINE=/Ob0
DBINFO=/Zi
NOOPT=/Od
OPENMP=/Qopenmp
INCLUDES= -I "$(VTUNEDIR)\include"
VTUNELIB="$(VTUNEDIR)\lib64\libittnotify.lib"
