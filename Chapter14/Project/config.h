#pragma once

#define USE_3D

// The initial serial code
#ifdef STEP_1
#define SERIAL
#define USE_1024_WORLD
#endif

// The oct tree
#ifdef STEP_2
#define OCTREE
#define USE_1024_WORLD
#endif

// The hashed oct tree
#ifdef STEP_3
#define HASHTREE
#define USE_1024_WORLD
#endif


// optimize the division
#ifdef STEP_4
#define HASHTREE
#define USE_1024_WORLD
#define USE_RECIPROCAL_DIVIDE 
#endif


// First parallel implementation 
#ifdef STEP_5
#define HASHTREE
#define USE_1024_WORLD
#define USE_RECIPROCAL_DIVIDE 
#define USE_CILK
#endif


//  Reduced count for checking dataraces
#ifdef STEP_6
#define HASHTREE
#define USE_128_WORLD
#define USE_RECIPROCAL_DIVIDE 
#define USE_CILK
#endif


//  Fix the data race 
#ifdef STEP_7
#define HASHTREE
#define USE_128_WORLD
#define USE_RECIPROCAL_DIVIDE 
#define USE_CILK
#define USE_CILK_REDUCER
#endif

//  Final version
#ifdef STEP_8
#define HASHTREE
#define USE_1024_WORLD
#define USE_RECIPROCAL_DIVIDE 
#define USE_CILK
#define USE_CILK_REDUCER
#endif




/*

// use this to debug a small example
// #define USE_TWO_WORLD
// #define USE_MINISCULE_WORLD
// #define USE_128_WORLD
// #define USE_256_WORLD
// #define USE_512_WORLD
// #define USE_1024_WORLD
// #define USE_SMALL_WORLD
// #define USE_MEDIUM_WORLD
// #define USE_LARGE_WORLD
//#define USE_MASSIVE_WORLD


// #define PRINT_CELL_CREATION
// #define PRINT_PARTICLE_PROGRESSION


//define the dimesions
#define USE_3D
// #define USE_2D 



// this controls the type of run
// #define SERIAL_RUN
// #define TREE_RUN
 #define HASH_TREE_RUN



// type of parallelism
// #define USE_OPENMP
// #define USE_OPENMP_APPLY_ACCEL
// #define USE_OPENMP_STEP


*/

