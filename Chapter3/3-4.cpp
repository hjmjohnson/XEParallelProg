// Example Chapter 3 OpenMP Program
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <omp.h>

const long int VERYBIG = 100000;
// ***********************************************************************
int main( void )
{
  int i;
  long int j, k, sum;
  double sumx, sumy, total, z;
  DWORD starttime, elapsedtime;
  // ---------------------------------------------------------------------
  // Output a start message
  printf( "OpenMP Parallel Timings for %ld iterations \n\n", VERYBIG );

  // repeat experiment several times
  for( i=0; i<6; i++ )
  {
    // get starting time
    starttime = timeGetTime();
    // reset check sum and total
    sum = 0;
    total = 0.0;
    
    // Work loop, do some work by looping VERYBIG times
    #pragma omp parallel for     \
      private( sumx, sumy, k )   \
      reduction( +: sum, total ) \
      schedule( dynamic, 1000 )
      for( int j=0; j<VERYBIG; j++ )
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
            (int)elapsedtime, total, sum );
  }

  // return integer as required by function header
  return 0;
}
// **********************************************************************