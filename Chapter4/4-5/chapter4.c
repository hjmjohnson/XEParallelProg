// Example Chapter 4 example Program
#include <stdio.h>
#include <stdlib.h>
#include "chapter4.h"

void MatrixMul(double a[N][N], double b[N][N], double c[N][N])
{
  int i,j,k;
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      for (k=0; k<N; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

// ***********************************************************************
int main( int argc, char * argv[] )
{
  int i,j,k,l,m;
  long int sum;
  double ret, total;
  int denominator = 2;
  double starttime, elapsedtime;
  double *a,*b,*c;

// -----------------------------------------------------------------------
  m = 2;

  if(argc == 2)
    denominator = atoi(argv[1]);

  // allocate memory for the matrices
  a = (double *)malloc(sizeof (double) * N * N);
  if(!a) {printf("malloc a failed!\n");exit(999);}

  b = (double *)malloc(sizeof (double) * N * N);
  if(!b) {printf("malloc b failed!\n");exit(999);}

  c = (double *)malloc(sizeof (double) * N * N);
  if(!c) {printf("malloc c failed!\n");exit(999);}

  // repeat experiment six times
  for( l=0; l<6; l++ )
  {
    // get starting time
    starttime = wtime();

    // initialize matrix a
    sum = Work(&total,a);

    // initialize matrix b;
    for (i = 0; i < N; i++) {
      for (j=0; j<N; j++) {
        for (k=0;k<DENOM_LOOP;k++) {
          sum += m/denominator;
        }
        b[N*i + j] = sum; 
      }
    }

    // do the matrix manipulation
    MatrixMul( (double (*)[N])a, (double (*)[N])b, (double (*)[N])c);

     // get ending time and use it to determine elapsed time
    elapsedtime = wtime() - starttime;

    // report elapsed time
    printf("Time Elapsed %03f Secs  Total=%lf   Check Sum = %ld\n",
                  elapsedtime, total, sum );
  }
  // return a value from matrix c
  // just here to make sure matrix calc doesn't get optimized away.
  return (int)c[100];
}
// **********************************************************************
