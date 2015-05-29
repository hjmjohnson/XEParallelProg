#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
float ParallelSum( float array[], size_t n )
{
  return parallel_reduce(
    // range
    blocked_range<float*>( array, array+n ),
    // identity
    0.f,
    // lambda function
    [](const blocked_range<float*>& r, float init)->float
    {
      for( float* a=r.begin(); a!=r.end(); ++a )
      init += *a;
      return init;
    },
    //lambda function providing the reduction operator
    []( float x, float y )->float
    {
      return x+y;
    }
  );
}