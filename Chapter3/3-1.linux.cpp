// Example Chapter 3 Serial Program
#include <stdio.h>
#include <math.h>
#include <sys/time.h> 
#include <sys/resource.h>  
double timeGetTime() 
{     
	struct timeval time;     
	struct timezone zone;     
	gettimeofday(&time, &zone);     
	return time.tv_sec + time.tv_usec*1e-6; 
}  


const long int VERYBIG = 100000;
// ***********************************************************************
int main( void )
{
  int i;
  long int j, k, sum;
  double sumx, sumy, total;
  double starttime, elapsedtime;
  // -----------------------------------------------------------------------
    // Output a start message
  printf( "None Parallel Timings for %ld iterations\n\n", VERYBIG );

  // repeat experiment several times
  for( i=0; i<6; i++ )
  {
    // get starting time
    starttime = timeGetTime();

    // reset check sum & running total
    sum = 0;
    total = 0.0;
    // Work Loop, do some work by looping VERYBIG times
    for( j=0; j<VERYBIG; j++ )
    {
      // increment check sum
      sum += 1;

      // Calculate first arithmetic series
      sumx = 0.0;
      for( k=0; k<j; k++ )
        sumx = sumx + (double)k;

      // Calculate second arithmetic series
      sumy = 0.0;
      for( k=j; k>0; k-- )
        sumy = sumy + (double)k;

      if( sumx > 0.0 )total = total + 1.0 / sqrt( sumx );
      if( sumy > 0.0 )total = total + 1.0 / sqrt( sumy );
    }

    // get ending time and use it to determine elapsed time
    elapsedtime = timeGetTime() - starttime;

    // report elapsed time
    printf("Time Elapsed %10d mSecs Total=%lf Check Sum = %ld\n",
                   (int)(elapsedtime * 1000), total, sum );
  }

  // return integer as required by function header
  return 0;
}
// **********************************************************************
