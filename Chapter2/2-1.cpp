#include <stdio.h>
#include <cilk/cilk.h>

long fibonacci(long n)
{
  long x, y;
  if (n < 2) return n;

  // find the n-1 number
  x = cilk_spawn fibonacci(n-1);

  // find the n-2 number
  y = fibonacci(n-2);

  // workers wait here until all have finished
  cilk_sync;
  
  return (x+y);
}

int main()
{
  // work out the 40th value in fibonacci series
  long fib = fibonacci(40);

  // display the results
  printf("Fibonacci 40: %d\n",fib);
}