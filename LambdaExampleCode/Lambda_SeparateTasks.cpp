#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
  constexpr size_t VECTOR_SIZE=100;
  float x[VECTOR_SIZE];

  size_t i=0;
  std::for_each(x, x+VECTOR_SIZE,
       [&i] (float &in) ->void { in = i; ++i; } );

  // Solve x=m*x+b
  const float m=2.0F;
  const float b=10.0F;

   constexpr size_t MAXTHREADS=4;
   constexpr size_t CHUNKSIZE=VECTOR_SIZE/MAXTHREADS;

   size_t tid;        //The thread number
   size_t startIndex; //Processing start point
   size_t stopIndex;  //Processing end point

   //Now process as separate tasks in serial
    {
      {
      // TASK#0
      tid=0;
      startIndex=tid*(CHUNKSIZE);
      stopIndex=( tid == ( MAXTHREADS-1) ) ? VECTOR_SIZE : (tid+1)*(CHUNKSIZE);
      std::for_each(x+startIndex, x+stopIndex,
        [m,b,tid](float &in) -> void { in = m*in+b ; } );
      }
      {
      // TASK#1
      tid=1;
      startIndex=tid*(CHUNKSIZE);
      stopIndex=( tid == ( MAXTHREADS-1) ) ? VECTOR_SIZE : (tid+1)*(CHUNKSIZE);
      std::for_each(x+startIndex, x+stopIndex,
        [m,b,tid](float &in) -> void { in = m*in+b ; } );
      }
      {
      // TASK#2
      tid=2;
      startIndex=tid*(CHUNKSIZE);
      stopIndex=( tid == ( MAXTHREADS-1) ) ? VECTOR_SIZE : (tid+1)*(CHUNKSIZE);
      std::for_each(x+startIndex, x+stopIndex,
        [m,b,tid](float &in) -> void { in = m*in+b ; } );
      }
      {
      // TASK#3
      tid=3;
      startIndex=tid*(CHUNKSIZE);
      stopIndex=( tid == ( MAXTHREADS-1) ) ? VECTOR_SIZE : (tid+1)*(CHUNKSIZE);
      std::for_each(x+startIndex, x+stopIndex,
        [m,b,tid](float &in) -> void { in = m*in+b ; } );
      }
    }

    std::cout << "\n\n" << std::endl;
    // Now print
    startIndex=0;
    stopIndex=VECTOR_SIZE;
    std::for_each(x+startIndex, x+stopIndex,
        [m,b](const float in) -> void { std::cout <<  in << " "; } );

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
