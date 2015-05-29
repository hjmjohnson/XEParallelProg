// this is our new main that calls the orginal dhrystone code
#include <omp.h>
extern "C" double wtime();
#include "dhry_1.cpp"
#define MAX_NUM_CALLS 100
#include "ittnotify.h"


int main(int argc, char * argv[])
{
	int NumCalls = omp_get_max_threads();
	int NumDhystoneLoops = 1000001;
	bool bSilent = false;

	if(argc >= 2)
	  NumDhystoneLoops = atoi(argv[1]);

	if(argc >= 3)
		if(strcmp(argv[2],"SILENT")==0)
		{
			bSilent=true;
		}
		else
		{
			NumCalls = atoi(argv[2]);
		}
	
	if(argc == 4)
	  NumCalls = atoi(argv[3]);

	double start = wtime();
	
	// what ever strategy is employed, it will use a divide and conquer approach
	#pragma omp parallel for schedule(static,1)
	for(int i = 1; i <= NumCalls; i++)
	{

		int num = NumDhystoneLoops/NumCalls;
		if (i ==NumCalls)
			num += NumDhystoneLoops % NumCalls ;
		dhrystone MyTest;
		// printf("running with %d\n",num);
		MyTest.main(num,bSilent);	
	}
	double stop = wtime();

	printf("%4.4f Elasped Secs\n",stop - start);

}


