#include <stdio.h>
#include <time.h>
#include <cilk/cilk.h>
#include <stdlib.h>

#define MALLOC_SIZE 1
#define ARRAY_SIZE 10000000
#include "tbb/scalable_allocator.h"

char * array[ARRAY_SIZE];

int main(int argc, char* argv[])
{
  clock_t start, stop;

  // get the start time
  start = clock();

  // load balance scalable malloc between available workers
  cilk_for(int i = 0; i < ARRAY_SIZE; i++)
  {
    array[i] = (char *)scalable_malloc(MALLOC_SIZE);
  }

    // free the blocks of memory
  cilk_for(int i = 0; i < ARRAY_SIZE; i++)
  {
    scalable_free(array[i]);
  }

  // get the stop time
  stop = clock();

  // display the time taken
  printf("The time was %f seconds\n",((double)(stop - start)/1000.0));
  return 0;
}