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
  std::for_each(x, x+VECTOR_SIZE,
        [m,b](float & in) -> void { in = m*in+b; } );

  std::for_each(x, x+VECTOR_SIZE,
        [](float in) -> void { std::cout <<  in << " "; } );

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
