#include <stdio.h>
#include "print.h"
#include "body.h"
#include "config.h"


void PrintBodies(unsigned int Num,char * Message)
{
	printf("%s",Message);
	for(unsigned int i = 0; i < Num; i++)
	{
		BODYTYPE *pBody = &body[i];
		printf("   Mass: %-5.12f; \n   Pos: [%-5.12f %-5.12f %-5.12f] \n   Vel: [%-5.12f %-5.12f %-5.12f] \n   Accel: [%-5.12f %-5.12f %-5.12f] \n\n",
			pBody->mass,
			pBody->pos[0], pBody->pos[1], pBody->pos[2],
			pBody->vel[0], pBody->vel[1], pBody->vel[2],
			pBody->acc[0], pBody->acc[1], pBody->acc[2]
			);

	}
}