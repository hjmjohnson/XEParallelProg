# LINUX SPECIFIC, uncomment these for LINUX
VTUNEDIR = /opt/intel/vtune_amplifier_xe_2011
INCLUDES = -I $(VTUNEDIR)/include
VTUNELIB=$(VTUNEDIR)/lib64/libittnotify.a
CC=icc 
DEL=rm -Rf
OBJ=o
NOINLINE= -fno-inline-functions
DBINFO=-g
NOOPT=-O0
OPENMP=-openmp
THREADLIB=-lpthread
