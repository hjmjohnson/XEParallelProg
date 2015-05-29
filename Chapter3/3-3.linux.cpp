// Example Chapter 3 Cilk Plus Program
#include <stdio.h>
#include <math.h>
#include <sys/time.h> 
#include <sys/resource.h>  
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
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
  double starttime, elapsedtime;
// -----------------------------------------------------------------------
  // Output a start message
 printf( "Cilk Plus Parallel Timings for %ld iterations\n\n", VERYBIG );
  // repeat experiment several times
  for( i=0; i<6; i++ )
  {
    // get starting time
    starttime = timeGetTime();

    // define check sum and total as reduction variables
    cilk::reducer_opadd<long int> sum(0);
    cilk::reducer_opadd<double> total(0.0);

    // Work Loop, do some work by looping VERYBIG times
    cilk_for( int j=0; j<VERYBIG; j++ )
    {
      // define loop local variables
      long int k;
      double sumx, sumy;

      // increment check sum
      sum += 1;

      sumx = 0.0;
      for( k=0; k<j; k++ )
        sumx = sumx + (double)k;

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
                   (int)(elapsedtime * 1000), total.get_value(), sum.get_value() );
  }

  // return integer as required by function header
  return 0;
}
// **********************************************************************
