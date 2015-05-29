// NOTE: this pragma is written on ONE line
#pragma isat tuning scope(M_begin, M_end) measure(M_begin, M_end)
variable(@omp_schedule_type, [static,dynamic,guided])
variable(@omp_schedule_chunk, range(5, 10, 1, pow2))
variable(@omp_num_threads, range(1, $NUM_CPU_THREADS, 1)) search(dependent)

// go through all numbers in range and see which are primes
void GetPrimes(int Start, int End)
{
  // Make Start to always be an even number
  Start += Start %2;
  int Range = End - Start;

  // if start is 2 or less, then just record it
  if(Start<=2) gPrimes[gNumPrimes++]=2;
  #pragma isat marker M_begin
  #pragma omp parallel for
  for( int i = Start; i <= End; i += 2 )
  {
    if( IsPrime(i) )
    {
      #pragma omp atomic
      gNumPrimes++;
      gPrimes[gNumPrimes] = i;
    }
    PrintProgress(Range);
  }
  #pragma isat marker M_end
}