# LINUX SPECIFIC, uncomment these for LINUX
INCLUDES = -I /opt/vtune_amplifier_xe_2011/include
VTUNELIB=/opt/vtune_amplifier_xe_2011/lib64/libittnotify.a
CC=icc 
DEL=rm -Rf
OBJ=o
NOINLINE= -fno-inline-functions
DBINFO=-g
NOOPT=-O0
OPENMP=-openmp
THREADLIB=-lpthread

