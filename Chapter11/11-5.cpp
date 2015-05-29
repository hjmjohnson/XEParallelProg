// This code has an ERROR in it which will cause a SEGMENTATION fault!
#include <stdio.h>
long long int fibonacci(int n) {
  if (n > 1) {
    long long int r_1, r_2;
    // create a task to calculate the n-1 number
    #pragma omp task default(none) shared(r_1,n)
    {
      // recursive call
      r_1 = fibonacci(n - 1);
    }
    // create a task to calculate the n-2 number
    #pragma omp task default(none) shared(r_2,n)
    {
      // recursive call
      r_2 = fibonacci(n - 2);
    }
    return r_1 + r_2;
  } else {
    // exit point for the recursion
    // this seeds the first two numbers in the sequence
    // ie 0 and 1
    if (n==0) return 0;
    return 1;
  }
}

int main()
{
  int i = 50;
  long long int t =0 ;
  // create a parallel region
  #pragma omp parallel
  {
    // run as a single thread
    #pragma omp single
    // calculate the 50th number in the fibonacci sequence
    t = fibonacci(i);
  }
  printf("%d\n",t);
  return 0;
}