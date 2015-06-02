#include <iostream>
#include <algorithm>
#include <vector>

#include <omp.h>

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
  //size_t tid;        //The thread number
  //size_t startIndex; //Processing start point
  //size_t stopIndex;  //Processing end point

#pragma omp parallel for default(none) firstprivate(m,b) shared(x)
  for(size_t i=0; i< VECTOR_SIZE; ++i) {            x[i]=m*x[i]+b;}

  std::cout << "\n\n" << std::endl;
  // Now print
  std::for_each(x, x+VECTOR_SIZE,
        [m,b](const float in) -> void { std::cout <<  in << " "; } );

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
