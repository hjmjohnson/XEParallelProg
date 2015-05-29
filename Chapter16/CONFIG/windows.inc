## WINDOWS OS specific vars.
CC=icl 
DEL=del
RM=rmdir /s /q
OBJ=obj
NOINLINE=/Ob0
DBINFO=/Zi
NOOPT=/Od
OPENMP=/Qopenmp
INCLUDES= -I "$(VTUNE_AMPLIFIER_XE_2011_DIR)\include"
VTUNELIB="$(VTUNE_AMPLIFIER_XE_2011_DIR)\lib64\libittnotify.lib"
