#include <stdio.h>
#include "config.h"
#include "body.h"
#include "hash.h"
#include "print.h"
extern "C" double wtime();

void PrintConfig(int fixn)
{
	printf("Running with %d bodies\n",fixn);

	printf("Running %s %s version\n",

	#ifdef SERIAL
		"Serial ",
	#elif defined(OCTREE)
		"Oct-Tree ",
	#elif defined(HASHTREE)
		"Hashed Oct-Tree ",
	#endif

	#ifdef _DEBUG
		"Debug"
	#else
		"Release"
	#endif
	);
}

int main(int argc, char* argv[])
{

	int fixn = FIXN;
	double start, stop,end_body_creation;
	NumCalcs = 0;

	PrintConfig(fixn);

	start = wtime();

	// initialize bodies with a random value
	startBodies(fixn);

	//	PrintBodies(fixn,"\nBefore\n");
	// TestFill();
	
// construct the tree (notice serial version does not use a tree
  #ifdef OCTREE	
    ConstructTree(fixn,body);
  #endif
	
  #ifdef HASHTREE
	ConstructHash(fixn,body);
  #endif

	end_body_creation = wtime();


  // run the simulation
  #ifdef SERIAL
	runSerialBodies(fixn);
  #endif

 #ifdef OCTREE
	runTreeBodies(fixn); 
  #endif

  #ifdef HASHTREE
	runHashBodies(fixn);
  #endif
	stop = wtime();
//	PrintBodies(fixn,"\nAfter\n");

	printf("Body initialization took  %-5.4f seconds\n", end_body_creation - start);
	printf("Simulation took %-5.3f seconds\n", stop - end_body_creation);
	printf("Number of Calculations: %d\n",NumCalcs);
	return 0;
}


