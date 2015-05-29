#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <memory.h>
#include <math.h>
#include "hash.h"
#include "body.h"
#include "print.h"

#ifdef USE_CILK
#include <cilk/cilk.h>
#endif
#ifdef USE_CILK_REDUCER
#include <cilk/reducer_opadd.h>
#endif

#ifdef USE_CILK_REDUCER
cilk::reducer_opadd<unsigned int> NumCalcsReducer(0);
#endif


// construct key by changing xyz to ints, and then bit interleaving

HASHTABLE theTable;
//--------------------------------------- DESCRIPTION -------------------
/* attempt at constructing hash

key is 1.xyz.xyz.xyz.xyz.xyz.xyz.xyz

Hash algorithm takes the bottom most significant bits and creates a hash

Key:	1.xyz.xyz.xyz.xyz.xyz.xyz.xyz
Mask:	0.000.000.000.xyz.xyz.xyz.xyz
HaskKey:0.000.000.000.xyz.xyz.xyz.xyz

Where two or more Keys map to the same HashKey, the collisions
are maintained in a linked list


The Keys are stored in numerical order, the larger values being traversed first
ie leaf first.
// ------------------------------------------------------------------------
*/


/******************************************
*
*
*
*******************************************
*/
void ListInit()
{
	// Create a sorted list of hash
	memset(theTable.SortedList.List,'\0',sizeof(theTable.SortedList.List));
	theTable.SortedList.Cursor = 0;
	theTable.SortedList.Deleted = 0;
}

/******************************************
*
*
*
*******************************************
*/
int ListCompare (const void * int1, const void * int2)
{
		return ( *(int*)int1 - *(int*)int2 );
}


/******************************************
*
*
*
*******************************************
*/
void ListAdd(unsigned int Key)
{
	// Create a sorted list of hash
	theTable.SortedList.List[theTable.SortedList.Cursor] = Key;
	theTable.SortedList.Cursor++;
}

/******************************************
*
*
*
*******************************************
*/
void ListSort()
{
	// Create a sorted list of hash
	qsort(theTable.SortedList.List, theTable.SortedList.Cursor, sizeof(unsigned int), ListCompare);
}

/******************************************
*
*
*
*******************************************
*/
void ListRemove(unsigned int Key)
{
	for(int i = 0; i < theTable.SortedList.Cursor;i++)
	{
		if(theTable.SortedList.List[i] == Key)
		{
			theTable.SortedList.List[i] = 0;
			theTable.SortedList.Deleted++;
			return;
		}
	}
}



// functions that deal with key and hash generation

/******************************************
*
*
*
*******************************************
*/
unsigned int KeyToHash(unsigned int Key)
{
	return (Key & HASHMASK) + 1;
}



/******************************************
*
*
*
*******************************************
*/
unsigned int KeyToIndex(unsigned int Key)
{
	if(Key == 1)
	{
		return 0;	
	}
	return Key;
}

/******************************************
*
*
*
*******************************************
*/
NODE * GetNode(unsigned int Key)
{
	unsigned int ArrayIndex = KeyToIndex(Key);
	NODE *pNode = &theTable.Data[ArrayIndex]; 
	return pNode;;
}


/******************************************
*
*
*
*******************************************
*/
NODE * GetParentNode(HASHKEY &Key )
{
	NODE *pParentNode = NULL;
	
	if(Key > 1)
	{
		unsigned int ParentKey = Key >> 3;
		pParentNode = GetNode(ParentKey);
	}
	return pParentNode;
}

/******************************************
*
*
*
*******************************************
*/
NODE * GetParentNode(NODE *pNode )
{
	NODE *pParentNode = NULL;
	
	if(pNode->Id > 1)
	{
		unsigned int ParentKey = pNode->Id >> 3;
		pParentNode = GetNode(ParentKey);
	}
	return pParentNode;
}


/******************************************
*
*
*
*******************************************
*/
// convert xyz coords into a key in 1.xyz.xyz.xyz ... format
HASHKEY GenerateKey(BODYTYPE *pCell)
{
	unsigned int Id = 0;
	unsigned int Mask = 0x1;
	unsigned int x = (unsigned int)(pCell->pos[0] - MINPOS);
	unsigned int y = (unsigned int)(pCell->pos[1] - MINPOS);
	unsigned int z = (unsigned int)(pCell->pos[2] - MINPOS);
	
	// reduce the keys to 9 bits
#if (NUM_BITS_NEEDED(MAXDIFF) > NUMBITS_PER_XYX)
	x = x >> (NUM_BITS_NEEDED(MAXDIFF) - NUMBITS_PER_XYX) ;
	y = y >> (NUM_BITS_NEEDED(MAXDIFF) - NUMBITS_PER_XYX);
	z = z >> (NUM_BITS_NEEDED(MAXDIFF) - NUMBITS_PER_XYX);
#endif
	// rotate through key width
	for(int i = 0; i < NUMBITS_PER_XYX; i++)
	{
		Id = Id | ((z & Mask) << ((i*2)));
		Id = Id | (((y & Mask) << 1) << (i*2));
		Id = Id | (((z & Mask) << 2) << (i*2));
		Mask = Mask << 1;
	}
	// now add the sentinal bit 
	Id = Id | (1 << (NUMBITS_PER_XYX * 3));
	return Id;
}



/******************************************
*
*
*
*******************************************
*/
void InitHashHead()
{
	GetNode(0)->MinMax.XMin = MINPOS;
	GetNode(0)->MinMax.XMax = MAXPOS;
	GetNode(0)->MinMax.YMin = MINPOS;
	GetNode(0)->MinMax.YMax = MAXPOS;
	GetNode(0)->MinMax.ZMin = MINPOS;
	GetNode(0)->MinMax.ZMax = MAXPOS;

	ListInit();
}

/******************************************
*
*
*
*******************************************
*/
void SetMinMax(unsigned int Key, MINMAX &MinMax, NODE *pNode)
{
	// calculate all the mid 
	double XMid = MinMax.XMin + (MinMax.XMax - MinMax.XMin) / 2;
	double YMid = MinMax.YMin + (MinMax.YMax - MinMax.YMin) / 2;
	double ZMid = MinMax.ZMin + (MinMax.ZMax - MinMax.ZMin) / 2;

	// if x bit is not set
	if(! (Key & 0x1))
	{
		MinMax.XMin = MinMax.XMin;
		MinMax.XMax = XMid;
	}
	else
	{
		MinMax.XMin = XMid;
		MinMax.XMax = MinMax.XMax;
	}

	// if y bit is not set
	if(! (Key & 0x2))
	{
		MinMax.YMin = MinMax.YMin;
		MinMax.YMax = YMid;
	}
	else
	{
		MinMax.YMin = YMid;
		MinMax.YMax = MinMax.YMax;
	}
 	
	// if z bit is not set
	if(! (Key & 0x4))
	{
		MinMax.ZMin = MinMax.ZMin;
		MinMax.ZMax = ZMid;
	}
	else
	{
		MinMax.ZMin = ZMid;
		MinMax.ZMax = MinMax.ZMax;
	}
	pNode->MinMax = MinMax;
}

/******************************************
*
*
*
*******************************************
*/
void SetParentInfo(HASHKEY &CurrentChildKey,MINMAX &MinMax)
{
	unsigned int ParentKey;
	unsigned int Index = KeyToIndex(CurrentChildKey);

	NODE *pNode = GetNode(Index);
	NODE *pParentNode = NULL;

	// store the id
	pNode->Id = CurrentChildKey;

	unsigned int Bit = 0x1 << (CurrentChildKey & 0x7);
	// Key will be equal to 1 when we have reached the sentinal bit
	if (CurrentChildKey > 1)
	{
		// work out the parent Id
		ParentKey = CurrentChildKey >> 3;
		pParentNode = GetNode(ParentKey); 
	
		// recursive call
		SetParentInfo(ParentKey,MinMax);

		// at this point MinMax holds the values of the parent
		// we are at the top of the parent list (because of recursive call)
		// so we just need to modify it and store
		SetMinMax(CurrentChildKey, MinMax, pNode);
	}		
	
	if(pParentNode)
	{
		pParentNode->pNodes = (NODES *)((unsigned int)pParentNode->pNodes | Bit);
	}
	
	theTable.NumNodes++;
	
	if (CurrentChildKey == 1)
	{
		MinMax = pNode->MinMax;	
	}
}



/******************************************
*
*
*
*******************************************
*/
void Chain(NODE *pNode, BODYTYPE *pBody, unsigned int Key, unsigned int Hash)
{
	// TODO: should really be an ordered list.
	theTable.NumChainedLeafs++;

	NODE *pPtr = (NODE *)malloc(sizeof(NODE));
	memset(pPtr,'\0',sizeof(NODE));
	pPtr->pCell = pBody;
	pPtr->Id = Key;
	pPtr->pChild=(NODE *)Hash;

	while(pNode->pNext != NULL)
	{
		pNode = pNode->pNext;
	}

	#ifdef PRINT_CELL_CREATION
	printf("Chaining 0x%x at  %d\n", pPtr->Id, Hash);
	#endif
	pNode->pNext = pPtr;
}


/******************************************
*
*
*
*******************************************
*/
void InsertHash(NODE *pNode, BODYTYPE *pBody, unsigned int Key, unsigned int Hash,bool bMove)
{

	
	if(!pNode->pCell)
	{
		pNode->pCell = pBody;
		pNode->Id = Key;
		pNode->pChild=(NODE *)Hash; // just using up a redundant field to store hash value
		if(!bMove)
		{
			theTable.NumLeafs++;
			#ifdef PRINT_CELL_CREATION
			printf("Inserting 0x%x into theTable[0x%08x, %d]\n", Key,Hash,Hash);
			#endif
		}
		else
		{
			#ifdef PRINT_CELL_CREATION
			printf("Moving 0x%x into theTable[0x%08x, %d]\n", Key,Hash,Hash);
			#endif

		}
		// add the ID to list.
		// NB we don't store chained ones
		ListAdd(Hash);
	}
	else
	{
		Chain(pNode,pBody,Key,Hash);
	}

	unsigned int NewKey = Hash;
	MINMAX MinMax;
	SetParentInfo(NewKey,MinMax);




}

/******************************************
*
*
*
*******************************************
*/
void HashMoveBody(unsigned int Hash)
{
	BODYTYPE *pBody = theTable.Data[Hash].pCell;
	theTable.Data[Hash].pCell = NULL;
	ListRemove(Hash);
	HashInsertBody(pBody , true);
	#ifdef PRINT_CELL_CREATION
	printf("Moving 0x%x at  %d\n", theTable.Data[Hash].Id, Hash);
	#endif

}

/******************************************
*
*
*
*******************************************
*/
// insert a node into the tree.
void HashInsertBody(BODYTYPE *pBody,bool bMove = false)
{

	// Create the KEY
	HASHKEY Key = GenerateKey(pBody);
	unsigned int ParentHash;
	unsigned int Hash = Key;	
#if 0
	// create a hash index 
	unsigned int Hash = KeyToHash(Key);
#endif

	ParentHash = Hash >> 3;

	// make sure the hash is within the range of the hash table
	while ( Hash >= MAXKEYS)
	{
		Hash = ParentHash;
		ParentHash = ParentHash >> 3;
	}


	// rotate up the tree to the first occupied parent node
	while(ParentHash > 1 && 
		theTable.Data[Hash].pCell == 0 &&
		theTable.Data[Hash].pNodes == 0  && 
		theTable.Data[ParentHash].pCell == 0  && 
		theTable.Data[ParentHash].pNodes == 0)
	{
		Hash = ParentHash;
		ParentHash = ParentHash >> 3;
	}


	// insert in hash table
	NODE * pNode = &theTable.Data[Hash];
	
	InsertHash(pNode,pBody,Key,Hash,bMove);

	/* it could that the parent is a pCell and not a node, 
	in which case we need to relocate the pCell */
	if(theTable.Data[ParentHash].pCell)
	{
		HashMoveBody(ParentHash);
	}

}

/******************************************
*
*
*
*******************************************
*/
void HashInsertBodies(int NumBodies, BODYTYPE body[])
{
	// iterate through each element of the array and place contents in the three
	for(int i = 0; i < NumBodies;i++)
	{
	#ifdef PRINT_CELL_CREATION
		printf("\nAbout to insert Body, %-5.2f,%-5.2f,%-5.2f \n",
			body[i].pos[0], body[i].pos[1], body[i].pos[2]);
	#endif

		HashInsertBody(&body[i]);
	}
}


/******************************************
*
*
*
*******************************************
*/
void AddCOMAndMassToItsParent(NODE *pParent, NODE *pNode)
{
	// Add COM and Mass to its parent
	if(pParent)
	{
		pParent->Mass += pNode->Mass;
		pParent->CentreOfMass[0] += pNode->CentreOfMass[0]*pNode->Mass;
		pParent->CentreOfMass[1] += pNode->CentreOfMass[1]*pNode->Mass;
		pParent->CentreOfMass[2] += pNode->CentreOfMass[2]*pNode->Mass;
	}
}
/******************************************
*
*
*
*******************************************
*/
void CopyPCellToNode( NODE *pNode,NODE *pParent)
{
	if(pNode->pCell)
	{
		pNode->Mass = pNode->pCell->mass;
		pNode->CentreOfMass[0] = pNode->pCell->pos[0];
		pNode->CentreOfMass[1] = pNode->pCell->pos[1];
		pNode->CentreOfMass[2] = pNode->pCell->pos[2];
	}
 // 	AddCOMAndMassToItsParent(pParent, pNode);
}


/******************************************
*
*
*
*******************************************
*/
void FinalizeNode(NODE *pNode)
{
	if(pNode)
	{
		pNode->CentreOfMass[0] = pNode->CentreOfMass[0]/pNode->Mass;
		pNode->CentreOfMass[1] = pNode->CentreOfMass[1]/pNode->Mass;
		pNode->CentreOfMass[2] = pNode->CentreOfMass[2]/pNode->Mass;
	}
}

/******************************************
*
*
*
*******************************************
*/
// calculate mass and com of each node
void HashCalculateMass(NODE *pNode, NODE * pParent = NULL)
{
	// we start from top node and recurse downwards
	// on the way back up we deal with the COM and Mass of all nodes
	if(!pNode->pCell)
	{
		// now do each child
		if(pNode->pNodes)
		{
			for(int i = 0; i < 8; i++)
			{
				if((unsigned int )pNode->pNodes & (0x1 << i))
				{
					NODE * pChild = GetNode((pNode->Id << 3) + i);
					HashCalculateMass(pChild,pNode);
					AddCOMAndMassToItsParent(pNode, pChild);				
				}
			}
		}	
		// at this point we have dealt with all the children so finalize the node
		FinalizeNode(pNode);
	}
	else
	{
		// must be a leaf!
		// copy pCell to the node
		CopyPCellToNode(pNode,pParent);
		
		// also deal with chains
		NODE *pChain = pNode->pNext;
		while(pChain)
		{
			CopyPCellToNode(pChain,pParent);
			pChain = pChain->pNext;	
		}
	}
}

/******************************************
*
*
*
*******************************************
*/
void PrintLeaves()
{
	for(unsigned int i = 0; i < theTable.SortedList.Cursor; i++)
	{
		unsigned int Hash = theTable.SortedList.List[i];
		if(Hash == 0)
			continue;
		
		NODE *pNode = GetNode(Hash);

		printf("LEAF:%d\n",pNode->Id);
		NODE *pChain = pNode->pNext;
		while(pChain)
		{
			printf("CHAINED LEAF:%d\n",pChain->Id);
	
			pChain = pChain->pNext;	
		}

	}
}


/******************************************
*
*
*
*******************************************
*/
bool ConstructHash(int NumBodies, BODYTYPE body[])
{
	InitHashHead();

	HashInsertBodies(NumBodies, body);

	ListSort();

	// iterate through the hash table and set Max and Min values
	HashCalculateMass(GetNode(0));

// 	PrintLeaves();
	
	printf("\nNum Leaves:%d, Num Nodes %d, Num Chains %d \n\n",theTable.NumLeafs,theTable.NumNodes,theTable.NumChainedLeafs);

	return true;
}


/******************************************
*
*
*
*******************************************
*/
void ApplyAccel(NODE *pFirstNode, NODE *pSecondNode, double dx, double dy, double dz, double distsq, double dist)
{

	#ifdef PRINT_PARTICLE_PROGRESSION
		printf("Applying %d to %d\n",pSecondNode->Id, pFirstNode->Id);	  
	#endif

	// compute the unit vector from j to i
	double ud[3];
#ifndef USE_RECIPROCAL_DIVIDE 
	ud[0] = dx/dist;
	ud[1] = dy/dist;
	ud[2] = dz/dist;
#else
	double dd=1.0/dist;
	ud[0] = dx * dd;
	ud[1] = dy * dd;
	ud[2] = dz * dd;
#endif

	// F = G*mi*mj/distsq, but F = ma, so ai = G*mj/distsq
	double Gdivd = GFORCE/distsq;
	double ai = Gdivd*pSecondNode->Mass;

#ifndef USE_CILK_REDUCER
	NumCalcs++;
#else
	NumCalcsReducer++;
#endif

	
	// apply acceleration components using unit vectors
	for (int k = 0; k < NUMDIMENSIONS; ++k) {
		pFirstNode->pCell->acc[k] -= ai*ud[k];
	}
}
/******************************************
*
*
*
*******************************************
*/
void ComputeDistance(NODE *pFirstNode, NODE *pSecondNode, double &dx, double &dy, double &dz, double &distsq, double &dist, double &width)
{
	// compute the distance between them
	dx = pFirstNode->pCell->pos[0]-pSecondNode->CentreOfMass[0];
	dy = pFirstNode->pCell->pos[1]-pSecondNode->CentreOfMass[1];
	dz = pFirstNode->pCell->pos[2]-pSecondNode->CentreOfMass[2];

	distsq = dx*dx + dy*dy + dz*dz;
	if (distsq < MINDIST) distsq = MINDIST;
	dist = sqrt(distsq);

	width = pSecondNode->MinMax.XMax - pSecondNode->MinMax.XMin;
}
/******************************************
*
*
*
*******************************************
*/
void HashAdvance(NODE *pFirstNode, NODE *pSecondNode)
{
	// for the current node we calc the impact of every other node
	// work out the factor

	if(pFirstNode == pSecondNode)
	{
		return;
	}

	double dx;
	double dy;
	double dz;
	double distsq;
	double dist;
	double width;
	
	ComputeDistance(pFirstNode, pSecondNode, dx, dy, dz, distsq, dist, width);

	// if the distance betwee the two nodes is significant, or we are dealing with a root 
	// then just use current values

	#ifdef PRINT_PARTICLE_PROGRESSION
			printf("Width %-5.2f Distance %-5.2f\n",width,dist);	  
	#endif

	if(width/dist < 0.5)
	{
	#ifdef PRINT_PARTICLE_PROGRESSION
		printf("About to Apply %d %d \n",pFirstNode->Id, pSecondNode->Id);	  
	#endif

		ApplyAccel(pFirstNode, pSecondNode, dx, dy, dz, distsq, dist);
//		PrintBodies(FIXN,"In HASH ACC\n");
		return;
	}

	if(pSecondNode->pNodes)
	{
		for(int i = 0; i < 8; i++)
		{
			if((unsigned int )pSecondNode->pNodes & (0x1 << i))
			{
				unsigned int ChildIdx = (pSecondNode->Id << 3) + i;
				NODE * pChild = GetNode(ChildIdx);
				HashAdvance(pFirstNode,pChild);
			
				NODE *pChain = pSecondNode->pNext;
				while(pChain)
				{
					HashAdvance(pFirstNode,pChain);
					pChain = pChain->pNext;		
				}	
			}	
		}
	}
}


/******************************************
*
*
*
*******************************************
*/

#ifndef USE_CILK_REDUCER
unsigned int stepcount;
#else
cilk::reducer_opadd<unsigned int> stepcount(0);
#endif
void Step()
{
#ifdef USE_CILK
#ifdef MIN_GRAIN_SIZE
#pragma cilk grainsize = 1
#endif
	cilk_for
#else
	for
#endif
	(int i = 0; i < theTable.SortedList.Cursor; i++)
	{
		unsigned int Hash = theTable.SortedList.List[i];
		if(Hash != 0)
		{
			NODE *pNode = GetNode(Hash);
			HashAdvance(pNode,GetNode(0));		
			NODE *pChain = pNode->pNext;

			stepcount++;
			while(pChain)
			{
				HashAdvance(pChain, GetNode(0));
				pChain = pChain->pNext;	
				stepcount++;
			}
		}
	}

// copy num calcs from reducer back to global
#ifdef USE_CILK_REDUCER
	NumCalcs = NumCalcsReducer.get_value();
#endif

}

/******************************************
*
*
*
*******************************************
*/
void runHashBodies(int n)
{
	#ifndef USE_CILK_REDUCER
	stepcount= 0;
	#endif
	// Run the simulation over a fixed range of time steps
    for (double s = 0.; s < STEPLIMIT; s += TIMESTEP) 
	{
			// simulation step
		Step();
		ApplyAccelerationsAndAdvanceBodies(n);
    }
}


