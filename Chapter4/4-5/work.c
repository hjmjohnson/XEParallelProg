#include "chapter4.h"
#include <math.h>

long int Work(double *total,double a[]) 
{
  long int i,j,sum;
  double sumx, sumy;
  sum = 0;
  *total = 0.0;

  for (i=0;i<N;i++){
    for (j=0;j<N;j++) {
      sum += 1;
    	// Calculate first Arithmetic series
      sumx= Series1(j);

      // Calculate second Arithmetic series
      sumy= Series2(j);
 	
      // initialize the array
      if( sumx > 0.0 )*total = *total + 1.0 / sqrt( sumx );
      if( sumy > 0.0 )*total = *total + 1.0 / sqrt( sumy );
      a[N*i+j] = *total;
    }
  } 
  return sum;
}
