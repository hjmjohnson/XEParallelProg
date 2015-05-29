// This code should be used to replace the function main()
// from Listing 12-3.
// NOTE: this is not the BEST solution! The best solution is
// simply to build the original code with the Intel Compiler.

// We need some additional headers
#ifdef _WIN32
  #include <intrin.h>
#else
  #ifndef __INTEL_COMPILER
    #include <pmmintrin.h>
  #else
    #include <xmmintrin.h>
  #endif
#endif

int main(int argc, char* argv[])
{
  clock_t start, stop;
  int i, j,k;
  if(argc == 2)
  {
    N = atoi(argv[1]);
  }
  else
    N = DEFAULT_SIZE;
 
  // printf("Using Size %d\n", N);
  a = (double *)_mm_malloc(sizeof (double) * N * N,16);
  if(!a) {printf("malloc a failed!\n");exit(999);}

  b = (double *)_mm_malloc(sizeof (double) * N * N,16);
  if(!b) {printf("malloc b failed!\n");exit(999);}

  c = (double *)_mm_malloc(sizeof (double) * N * N,16);
  if(!c) {printf("malloc c failed!\n");exit(999);}

  init_arr(a);
  init_arr(b);
  zero_arr(c);

  __m128d *pA;
  __m128d *pB;
  start = clock();

  for (i = 0; i < N; i++) {
    for (k=0; k<N; k+=2) {
      pA=(__m128d *)&a[N*i+k];
      pB =(__m128d *)&b[N*k];
      __m128d res = _mm_setzero_pd();
      for (j=0; j<N; j++) {
        res = _mm_mul_pd(*pA,pB[j]);
        res = _mm_hadd_pd ( res , res);
        _mm_store_sd(&c[N*i+j],res);
      }
    }
  }
  stop = clock();
  printf("%-6g ",((double)(stop - start)) / CLOCKS_PER_SEC);

  _mm_free(a);
  _mm_free(b);
  _mm_free(c);
}