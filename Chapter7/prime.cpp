#include <math.h>
long gPrimes[1000000];

bool isPrimeRecurse(int p, int i=2)
{
  if (i==p) return 1;//or better if (i*i>p) return 1;
  if (p%i == 0 || p == 1) return 0;
  return isPrimeRecurse (p, i+1);
}

bool isPrime(int val)
{
  int limit, factor = 3;
  limit = (long)(sqrtf((float)val)+0.5f);
  while( (factor <= limit) && (val % factor))
    factor ++;
  return (factor > limit);
}

int Prime(int Num)
{
  int NumPrimes = 0;
  for( int i = 3; i <= Num; i += 2 )
  {
    if( isPrime(i) )
    gPrimes[NumPrimes++] = i;
  }
  return NumPrimes;
}

int PrimeRecursive(int Num)
{
  int NumPrimes = 0;
  for( int i = 3; i <= Num; i += 2 )
  {
    if( isPrimeRecurse(i) )
    gPrimes[NumPrimes++] = i;
  }
  return NumPrimes;
}