#pragma once
#include "body.h"
#define TREE_WIDTH 8

struct NODES;

struct MINMAX
{
	double XMin;
	double XMax;
	double YMin;
	double YMax;
	double ZMin;
	double ZMax;
};
struct NODE
{
	int Id;
	BODYTYPE * pCell;	
	NODES *  pNodes;
	MINMAX MinMax;
	NODE * pNext; // used in linked list to all siblings
	NODE * pChild; // used in linked list to all children
	double CentreOfMass[NUMDIMENSIONS];
	double Mass;
};

struct NODES 
{
	NODE Nodes[TREE_WIDTH];
};   


struct TREE
{
	int NumNodes; // this includes number of leafs 
	int NumLeafs;
	NODE Head;
};

// prototypes
bool ConstructTree(int NumBodies,BODYTYPE body[]);
void runTreeBodies(int n);

