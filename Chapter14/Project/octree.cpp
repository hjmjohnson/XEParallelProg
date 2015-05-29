#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "octree.h"
#include "print.h"

// the head of the tree
TREE  theTree;



void Split(NODE *pNode)
{
	int NodeIdx = 0;
	double XMid = pNode->MinMax.XMin + (pNode->MinMax.XMax - pNode->MinMax.XMin) / 2;
	double YMid = pNode->MinMax.YMin + (pNode->MinMax.YMax - pNode->MinMax.YMin) / 2;
	double ZMid = pNode->MinMax.ZMin + (pNode->MinMax.ZMax - pNode->MinMax.ZMin) / 2;
	
	int x;
	int y;
	int z;
	double XMin;
	double XMax;
	double YMin;
	double YMax;
	double ZMin;
	double ZMax;

	for (x=0; x < 2; x++)
	{
		x ? XMin = XMid : XMin = pNode->MinMax.XMin;
		x ? XMax = pNode->MinMax.XMax: XMax = XMid;
		for (y=0; y < 2; y++)
		{
			y ? YMin = YMid : YMin = pNode->MinMax.YMin;
			y ? YMax = pNode->MinMax.YMax: YMax = YMid;
			for (z=0; z < 2; z++)
			{
				z ? ZMin = ZMid : ZMin = pNode->MinMax.ZMin;
				z ? ZMax = pNode->MinMax.ZMax: ZMax = ZMid;
				
				NODE *pCurrNode= &pNode->pNodes->Nodes[NodeIdx];
				pCurrNode->MinMax.XMin = XMin;				
				pCurrNode->MinMax.XMax = XMax;				
				pCurrNode->MinMax.YMin = YMin;				
				pCurrNode->MinMax.YMax = YMax;				
				pCurrNode->MinMax.ZMin = ZMin;				
				pCurrNode->MinMax.ZMax = ZMax;	
				NodeIdx++;
			}
		}
	}
}


bool BodyWithinCoordinates(NODE *pNode, double x, double y, double z)
{
	return (	x >= pNode->MinMax.XMin && x <= pNode->MinMax.XMax &&
				y >= pNode->MinMax.YMin && y <= pNode->MinMax.YMax &&
				z >= pNode->MinMax.ZMin && z <= pNode->MinMax.ZMax);

}


NODE * CreateNode(NODE * pNode)
{

	// add empty nodes to arrays
	pNode->pNodes = (NODES *)malloc(sizeof(NODES));
	// TODO: error checking!

	memset(pNode->pNodes,0,sizeof(NODES));
	for(int i =0; i < TREE_WIDTH; i++)
	{
		theTree.NumNodes++;
		pNode->pNodes->Nodes[i].Id = (pNode->Id * 8)+ i + 1;
	}


	Split(pNode);
	// now insert the old body into the new nodes
	for(int i = 0; i < TREE_WIDTH; i++)
	{
		if(BodyWithinCoordinates(&pNode->pNodes->Nodes[i],
								pNode->pCell->pos[0],
								pNode->pCell->pos[1],
								pNode->pCell->pos[2]))
		{
			pNode->pNodes->Nodes[i].pCell = pNode->pCell;
			pNode->pCell = NULL;
			// NB: no need to increment leaf count as we are just moving an exiting leaf
			#ifdef PRINT_CELL_CREATION
			printf("Moving Leaf (Node : %d) to Node %d\n",pNode->Id,pNode->pNodes->Nodes[i].Id);	
			#endif
			break;
		}
	}
	
	return pNode;
}


// recursive traversal based on xyz co-ordinates
NODE * Traverse(NODE *pNode, BODYTYPE *pBody)
{
	// the node is either a leaf or a node
	// we 
	
	
	// if the current node is a leaf, and the range is correct
	if(!pNode->pNodes)
	{
		if (BodyWithinCoordinates(pNode,pBody->pos[0],pBody->pos[1],pBody->pos[2]))
		{
			return pNode;
		}
	}	

	if(pNode->pNodes)
	{
		for(int i = 0; i < TREE_WIDTH; i++)
		{
			NODE * pCurrNode = Traverse(&pNode->pNodes->Nodes[i],pBody);
			if(pCurrNode)
				return pCurrNode;
		
		}
	}
	return NULL;
}

void InsertLeaf(BODYTYPE *pBody, NODE *pNode)
{
	// insert the body.
	pNode->pCell = pBody;
	theTree.NumLeafs++;
	#ifdef PRINT_CELL_CREATION
	printf("inserting leaf in node %d\n",pNode->Id);
	#endif
}

// insert a node into the tree.
void InsertBody(BODYTYPE *pBody)
{
	// start from the top of the tree,
	NODE *pNode = &theTree.Head;
	
	// recursive traverse
	// traverse until the xyz coords fall within the min\max
	pNode = Traverse(pNode,pBody);	
	
	
	// if the node already has a body, 
	// then split the node
	// and traverse to the correct location
	while(pNode->pCell)
	{
		CreateNode(pNode);
		pNode = Traverse(pNode,pBody);	
	}

	InsertLeaf(pBody, pNode);	
}


void PrintNodes(NODE *pNode)
{
	printf("%d ",pNode->Id);

	if(pNode->pNodes)
	{
		for(int i = 0; i < TREE_WIDTH; i++)
		{
			PrintNodes(&pNode->pNodes->Nodes[i]);
		}
	}
}


void PrintLeafs(NODE *pNode)
{
	if(pNode->pCell)
		printf("%d ",pNode->Id);

	if(pNode->pNodes)
	{
		for(int i = 0; i < TREE_WIDTH; i++)
		{
			PrintLeafs(&pNode->pNodes->Nodes[i]);
		}
	}
}

bool IsLive(NODE *pNode)
{
	return pNode->pCell || pNode->pNodes;
}


void SetChild(NODE *pNode, bool &bSet, NODE *pChildNode)
{
	if(IsLive(pChildNode) && !bSet)
	{
		bSet = true;
		pNode->pChild = pChildNode;
	}
}
void SetNext(NODES *pNodes,NODE *pCurrNode, int i)
{
	for(int j = i + 1; j < TREE_WIDTH; j++)
	{
		NODE *pNextNode = &pNodes->Nodes[j];
		if(IsLive(pNextNode))
		{
			 pCurrNode->pNext=pNextNode;
			break;
		}
	}
}

void SetChildAndNext(NODE *pNode)
{
	bool bSet = false;
	if(pNode->pNodes)
	{
		for(int i = 0; i < TREE_WIDTH; i++)
		{
			NODE * pCurrNode = &pNode->pNodes->Nodes[i];
			if(pCurrNode)
			{
				SetChild(pNode, bSet, pCurrNode);
				SetNext(pNode->pNodes,pCurrNode,i);
				
				SetChildAndNext(pCurrNode);
			}
		}
	}
}


void PrintRelationship(NODE *pNode)
{
	if(pNode->pChild)
	{
		printf("Parent %d : Child %d\n",pNode->Id,pNode->pChild->Id);
		PrintRelationship(pNode->pChild);
	}

	if(pNode->pNext)
	{
		printf("Node %d : Sibling %d\n",pNode->Id,pNode->pNext->Id);
		PrintRelationship(pNode->pNext);
	}
}


// calculate mass and com of each node
void CalculateMass(NODE *pNode,NODE *pParent = NULL)
{
	if(pNode->pChild)
	{
		CalculateMass(pNode->pChild,pNode);
		
	}
	else
	{
		// no children, so this must be a leaf!
		// copy pCell to the node
		pNode->Mass = pNode->pCell->mass;
		pNode->CentreOfMass[0] = pNode->pCell->pos[0];
		pNode->CentreOfMass[1] = pNode->pCell->pos[1];
		pNode->CentreOfMass[2] = pNode->pCell->pos[2];
	
		// Add COM and Mass to its parent
		if(pParent)
		{
			pParent->Mass += pNode->Mass;
			pParent->CentreOfMass[0] += pNode->CentreOfMass[0]*pNode->Mass;
			pParent->CentreOfMass[1] += pNode->CentreOfMass[1]*pNode->Mass;
			pParent->CentreOfMass[2] += pNode->CentreOfMass[2]*pNode->Mass;
		}
	}

	// and do all the siblings

	if(pNode->pNext)
	{
			CalculateMass(pNode->pNext,pParent);
	}
	else
	{
		if(pParent)
		{
			pParent->CentreOfMass[0] = pParent->CentreOfMass[0]/pParent->Mass;
			pParent->CentreOfMass[1] = pParent->CentreOfMass[1]/pParent->Mass;
			pParent->CentreOfMass[2] = pParent->CentreOfMass[2]/pParent->Mass;
		}
	}
}


void Advance(NODE *pFirstNode, NODE * pSecondNode)
{
	// for the current node we calc the impact of every other node
	// work out the factor

	// compute the distance between them
	double dx = pFirstNode->pCell->pos[0]-pSecondNode->CentreOfMass[0];
    double dy = pFirstNode->pCell->pos[1]-pSecondNode->CentreOfMass[1];
    double dz = pFirstNode->pCell->pos[2]-pSecondNode->CentreOfMass[2];

    double distsq = dx*dx + dy*dy + dz*dz;
    if (distsq < MINDIST) distsq = MINDIST;
    double dist = sqrt(distsq);

	double width = pSecondNode->MinMax.XMax - pSecondNode->MinMax.XMin;

	// if the distance betwee the two nodes is significant
	// then just use current values

	#ifdef PRINT_PARTICLE_PROGRESSION
			printf("Width %-5.2f Distance %-5.2f\n",width,dist);	  
	#endif

	if(width/dist < 0.5)
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

		NumCalcs++;
	
		// apply acceleration components using unit vectors
		for (int k = 0; k < NUMDIMENSIONS; ++k) {
			pFirstNode->pCell->acc[k] -= ai*ud[k];
		
//		PrintBodies(FIXN,"In OCT-TREE ACC\n");
		}
		return;
	}

	// traveserse each node
	if(pSecondNode->pChild)
	{
		Advance(pFirstNode,pSecondNode->pChild);
	}

	if(pSecondNode->pNext)
	{
		Advance(pFirstNode,pSecondNode->pNext);
	}
 }

void CalculateAcceleration(NODE *pNode)
{
	// traveserse each node
	if(pNode->pChild)
	{
		CalculateAcceleration(pNode->pChild);
	}
	else
	{
		Advance(pNode,&theTree.Head);
	}

	if(pNode->pNext)
	{
		CalculateAcceleration(pNode->pNext);
	}
 }


// takes an array of bodies and creates the tree
// return true if constructed OK
bool ConstructTree(int NumBodies, BODYTYPE body[])
{
	// init the head node
	memset(&theTree.Head,0,sizeof(NODE));

	theTree.Head.MinMax.XMin = MINPOS;
	theTree.Head.MinMax.XMax = MAXPOS;
	theTree.Head.MinMax.YMin = MINPOS;
	theTree.Head.MinMax.YMax = MAXPOS;
	theTree.Head.MinMax.ZMin = MINPOS;
	theTree.Head.MinMax.ZMax = MAXPOS;
	theTree.NumLeafs = 0;
	theTree.NumNodes = 0;

	// insert the first body straight in the cell.
	theTree.Head.Id = theTree.NumNodes;
	InsertLeaf(&body[0], &theTree.Head);

	#ifdef PRINT_CELL_CREATION
	printf("About to insert Body, %-5.2f,%-5.2f,%-5.2f \n",
			body[0].pos[0], body[0].pos[1], body[0].pos[2]);
	#endif


	// iterate through each element of the array and place contents in the three
	for(int i = 1; i < NumBodies;i++)
	{
		
		#ifdef PRINT_CELL_CREATION
		printf("\nAbout to insert Body, %-5.2f,%-5.2f,%-5.2f \n",
			body[i].pos[0], body[i].pos[1], body[i].pos[2]);
		#endif

		InsertBody(&body[i]);
	}

	SetChildAndNext(&theTree.Head);

//	PrintRelationship(&theTree.Head);
	//PrintNodes(&theTree.Head);

	CalculateMass(&theTree.Head);

//	PrintLeafs(&theTree.Head);

	printf("\nNum Leafs:%d, Num Nodes %d\n\n",theTree.NumLeafs,theTree.NumNodes);

	

	return true;
}



void runTreeBodies(int n)
{
    // Run the simulation over a fixed range of time steps
    for (double s = 0.; s < STEPLIMIT; s += TIMESTEP) 
	{
	
		// simulation step
		CalculateAcceleration(&theTree.Head);
		
		ApplyAccelerationsAndAdvanceBodies(n);
	
    }
}

		

