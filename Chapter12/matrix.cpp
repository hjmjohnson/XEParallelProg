//Naive matrix multiply
//Warning, this implementation is SLOW!
#include <stdio.h>
#include <time.h>
#include <stdlib.h>	

#define DEFAULT_SIZE 1000

// pointers for matrices
double *a, *b, *c;
int N;  // stores width of matrix(if N = 2, then matrix will be 2 * 2)

// function prototypes
void init_arr(double a[]);
void print_arr(char * name, double array[]);
void zero_arr(double a[]);

int main(int argc, char* argv[])
{
  clock_t start, stop;
  int i, j,k;

  // if user does not input matrix size, DEFAULT_SIZE is used
  if(argc == 2)
  {
    N = atoi(argv[1]);
  }
  else
  N = DEFAULT_SIZE;

  // allocate memory for the matrices
  a = (double *)malloc(sizeof (double) * N * N);
  if(!a) {printf("malloc a failed!\n");exit(999);}

  b = (double *)malloc(sizeof (double) * N * N);
  if(!b) {printf("malloc b failed!\n");exit(999);}

  c = (double *)malloc(sizeof (double) * N * N);
  if(!c) {printf("malloc c failed!\n");exit(999);}

  init_arr(a);
  init_arr(b);
  zero_arr(c);

  start = clock();

  // do the matrix calculation c = a * b  
  for (i = 0; i < N; i++) {
    for (j=0; j<N; j++) {
       for (k=0; k<N; k++) {
         c[N*i+j] += a[N*i+k] * b[N*k+j];
       }
    }
  }
  stop = clock();

  // print how long program took.
  printf("%-6g  ",((double)(stop - start)) / CLOCKS_PER_SEC);

  // free dynamically allocated memory
  free(a);
  free(b);
  free(c);
}

// print out a matrix
void print_arr(char * name, double array[])
{
  int i,j;
  printf("\n%s\n",name);
  for (i=0;i<N;i++){
    for (j=0;j<N;j++) {
       printf("%g\t",array[N*i+j]);
    }
    printf("\n");
  }
}
 
// initialize aray to values between 0 and 9
// this is just to make the printout look better
void init_arr(double a[])
{
  int i,j;
  for (i=0; i< N;i++) {
    for (j=0; j<N;j++) {
      a[i*N+j] = (i+j+1)%10;
    }
  }
}
// initialize array entries to zero
void zero_arr(double a[])
{
  int i,j;
  for (i=0; i< N;i++) {
    for (j=0; j<N;j++) {
      a[i*N+j] = 0;
    }
  }
}
