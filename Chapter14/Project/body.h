#pragma once
#include "config.h"
#define ALIGN_BODIES


// 2
#ifdef USE_TWO_WORLD
  #define BODYMAX (4)
  #define FIXN 2
  #define WORLD_DEFINED
#endif

// 16
#ifdef USE_MINISCULE_WORLD
  #define BODYMAX (16)
  #define FIXN 4
  #define WORLD_DEFINED
#endif

//128
#ifdef USE_128_WORLD
  #define BODYMAX (128)
  #define FIXN 128
  #define WORLD_DEFINED
#endif

//256
#ifdef USE_256_WORLD
  #define BODYMAX (256)
  #define FIXN 256
  #define WORLD_DEFINED
#endif

#ifdef USE_512_WORLD
  #define BODYMAX (512)
  #define FIXN 512
  #define WORLD_DEFINED
#endif

#ifdef USE_1024_WORLD
  #define BODYMAX (1024)
  #define FIXN 1024
  #define WORLD_DEFINED
#endif

//2K
#ifdef USE_SMALL_WORLD
  #define BODYMAX (2048)
  #define FIXN 2048
  #define WORLD_DEFINED
#endif

// 16K
#ifdef USE_MEDIUM_WORLD
  #define BODYMAX (1024 * 16)
  #define FIXN (1024 * 16)
  #define WORLD_DEFINED
#endif

// 256K
#ifdef USE_LARGE_WORLD
  #define BODYMAX (1024 * 256)
  #define FIXN (1024 * 256)
  #define WORLD_DEFINED
#endif

// 1MB
#ifdef USE_MASSIVE_WORLD
  #define BODYMAX (1024 * 1024) 
  #define FIXN (1024 * 1024)
  #define WORLD_DEFINED
#endif


#ifndef WORLD_DEFINED  // default
  #define BODYMAX (16) 
  #define FIXN 4
  #define WORLD_DEFINED
#endif

// change from a 2 to a 3d using this
#ifdef USE_3D
#define NUMDIMENSIONS 3
#else
#define NUMDIMENSIONS 2
#endif

#define GFORCE 4.
#define TIMESTEP 0.01
#define MINDIST (0.00001)
// #define STEPLIMIT (1.*TIMESTEP)
#define STEPLIMIT (1000.*TIMESTEP)

#define MAXDIFF 100000 // this must be integer as big as MAXPOS - MINPOS
#define MINPOS -50000.
#define MAXPOS  50000.
#define MINVEL -100.
#define MAXVEL  100.
#define MINMASS 10.
#define MAXMASS 500.


#ifdef ALIGN_BODIES
__declspec(align(128))
#endif

struct BODYTYPE {
    double pos[NUMDIMENSIONS];
    double vel[NUMDIMENSIONS];
    double acc[NUMDIMENSIONS];
    double mass;
#ifdef ALIGN_BODIES
    unsigned char dummy[128-(10*sizeof(double))]; // 10 is the number of doubles as data
#endif
}; 



extern BODYTYPE body[BODYMAX];
extern unsigned int NumCalcs;
// prototypes
void ApplyAccelerationsAndAdvanceBodies(int n);
void startBodies(int n);
void runSerialBodies(int n);
