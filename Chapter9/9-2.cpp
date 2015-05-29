void GetPrimes(int Start, int End)
{
  // Make Start to always be an even number
  Start += Start %2;

  // If Start is 2 or less, then just record it
  if(Start<=2) gPrimes[gNumPrimes++]=2;
  #pragma omp parallel for schedule(guided,512) num_threads(12)
  for( int i = Start; i <= End; i += 2 )
  {
    if( IsPrime(i) )
    {
      #pragma omp atomic
      gNumPrimes++;
      gPrimes[gNumPrimes] = i;
    }
    PrintProgress(End-Start);
  }
}