#include <stdio.h>
#include <math.h>
extern "C" double wtime();
#define FIRST 1
#define LAST 300000
#define CursorBack "\b\b\b\b"
// globals
int gProgress = 0;
int gNumPrimes = 0;
int gPrimes[10000000];

// Display progress
void PrintProgress(int Range )
{
  int Percent = 0;
  #pragma omp critical
  {
    gProgress++;
    Percent = (int)((float)gProgress/(float)Range *200.0f + 0.5f);
  }
  if( Percent % 10 == 0 )
  printf("%s%3d%%", CursorBack,Percent);
}

// Test to see if a number is a prime
bool IsPrime(int CurrentValue)
{
  int Limit, Factor = 3;

  if( CurrentValue == 1 )
    return false;
  else if( CurrentValue == 2 )
    return true;

  Limit = (long)(sqrtf((float)CurrentValue)+0.5f);
  while( (Factor <= Limit) && (CurrentValue % Factor))
    Factor ++;

  return (Factor > Limit);
}

// Go through all numbers in range and see which are primes
 void GetPrimes(int Start, int End)
{
  // Make Start to always be an even number
  Start += Start %2;

  // If start is 2 or less, then just record it
  if(Start<=2) gPrimes[gNumPrimes++]=2;

  #pragma omp parallel for
  for( int i = Start; i <= End; i += 2 )
  {
    if( IsPrime(i) )
    {
      #pragma omp critical
      gPrimes[gNumPrimes++] = i;
    }
    PrintProgress(End-Start);
  }
}

int main()
{
  double StartTime = wtime();
  GetPrimes(FIRST, LAST);
  double EndTime = wtime();

  printf("\nFound %8d primes in %7.4lf secs\n",
  gNumPrimes,EndTime - StartTime);
}