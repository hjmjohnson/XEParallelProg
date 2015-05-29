#pragma once
#include <limits.h>
#include "octree.h"
#include "body.h"
typedef  unsigned int HASHKEY;

//#define NUMBITS_PER_XYX 8
#define NUMBITS_PER_XYX 5 
//#define NUMBITS_PER_XYX 3 
//#define NUMBITS_PER_XYX 2 
//#define NUMBITS_PER_XYX 1 

// work out number of bits needed to store max value
#define NUM_BITS_NEEDED(x) (1 \
+ ((x) > 0x2-1) \
+ ((x) > 0x4-1) \
+ ((x) > 0x8-1) \
+ ((x) > 0x10-1) \
+ ((x) > 0x20-1) \
+ ((x) > 0x40-1) \
+ ((x) > 0x80-1) \
+ ((x) > 0x100-1) \
+ ((x) > 0x200-1) \
+ ((x) > 0x400-1) \
+ ((x) > 0x800-1) \
+ ((x) > 0x1000-1) \
+ ((x) > 0x2000-1) \
+ ((x) > 0x4000-1) \
+ ((x) > 0x8000-1) \
+ ((x) > 0x10000-1) \
+ ((x) > 0x20000-1) \
+ ((x) > 0x40000-1) \
+ ((x) > 0x80000-1) \
+ ((x) > 0x100000-1) \
+ ((x) > 0x200000-1) \
+ ((x) > 0x400000-1) \
+ ((x) > 0x800000-1) \
+ ((x) > 0x1000000-1) \
+ ((x) > 0x2000000-1) \
+ ((x) > 0x4000000-1) \
+ ((x) > 0x8000000-1) \
+ ((x) > 0x10000000-1) \
+ ((x) > 0x20000000-1) \
+ ((x) > 0x40000000-1) \
+ ((x) > 0x80000000-1)) 



#define HASHMASK ((0x1 << (NUMBITS_PER_XYX * 3)) - 1)

#define MAXKEYS HASHMASK + 1

struct QUEUE
{
	unsigned int List[BODYMAX];
	unsigned int Cursor;
	unsigned int Deleted;
};

struct HASHTABLE
{
	unsigned int NumNodes;
	unsigned int NumLeafs;
	unsigned int NumChainedLeafs;
	QUEUE SortedList;
	
	NODE Data[MAXKEYS];

};


// prototypes
bool ConstructHash(int NumBodies, BODYTYPE body[]);
void runHashBodies(int n);
void HashInsertBody(BODYTYPE *pBody,bool bMove);


