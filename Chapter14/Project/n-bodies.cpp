#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"

#include "body.h"
#include "octree.h"
#include "hash.h"
#include "test.h"
#include "print.h"
BODYTYPE body[BODYMAX];
unsigned int NumCalcs;


double
rrange(double low, double high)
{
    return (double)rand()*(high - low)/(double)RAND_MAX + low;
}

void
startBodies(int n)
{
    for (int i = 0; i < n; ++i) {
	int j;

	for (j = 0; j < NUMDIMENSIONS; ++j)
	    body[i].pos[j] = rrange(MINPOS, MAXPOS);

	for (j = 0; j < NUMDIMENSIONS; ++j)
	    body[i].vel[j] = rrange(MINVEL, MAXVEL);

	for (j = 0; j < NUMDIMENSIONS; ++j)
	    body[i].acc[j] = 0.;

	body[i].mass = rrange(MINMASS, MAXMASS);
    }
}

void
addAcc(int i, int j) {
    
 	#ifdef PRINT_PARTICLE_PROGRESSION
		printf("Applying %d to %d\n",i, j);	  
	#endif

	
	// Compute the force between bodies and apply to each as an acceleration
	// printf("Comparing %d with %d\n",i,j);
    // compute the distance between them
    double dx = body[i].pos[0]-body[j].pos[0];
    double dy = body[i].pos[1]-body[j].pos[1];
    double dz = body[i].pos[2]-body[j].pos[2];

    double distsq = dx*dx + dy*dy + dz*dz;
    if (distsq < MINDIST) distsq = MINDIST;
    double dist = sqrt(distsq);

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
    double ai = Gdivd*body[j].mass;
    double aj = Gdivd*body[i].mass;

	NumCalcs++;
	
    // apply acceleration components using unit vectors
    for (int k = 0; k < NUMDIMENSIONS; ++k) {
		body[j].acc[k] += aj*ud[k];
		body[i].acc[k] -= ai*ud[k];
    }
}



void ApplyAccelerationsAndAdvanceBodies(int n)
{
	// apply accelerations and advance the bodies
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			body[i].vel[j] += body[i].acc[j] * TIMESTEP;
			body[i].pos[j] += body[i].vel[j] * TIMESTEP;
			body[i].acc[j] = 0.;
		}
	}
}

void
runSerialBodies(int n)
{
    // Run the simulation over a fixed range of time steps
    for (double s = 0.; s < STEPLIMIT; s += TIMESTEP) {
	int i, j;
	
		// Compute the accelerations of the bodies
		for (i = 0; i < n - 1; ++i) 
			for (j = i + 1; j < n; ++j) 
				addAcc(i, j);

//	PrintBodies(n,"In SERIAL ACC\n");

	ApplyAccelerationsAndAdvanceBodies(n);
    }
}









