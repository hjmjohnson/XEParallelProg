#include <iostream>
#include <algorithm>
#include <vector>

size_t global_var_i; //
static void global_set_values(float & in)
{
  in = global_var_i;
  global_var_i++;
}

float global_slope;
float global_intercept;
static void global_line(float & in)
{
  in=in*global_slope+global_intercept;
}

static void print( const float in )
{
  std::cout << in << " ";
}

int main()
{
  constexpr size_t VECTOR_SIZE=100;
  float x[VECTOR_SIZE];

  global_var_i=0;
  std::for_each(x, x+VECTOR_SIZE,
                global_set_values );

  global_slope=2.0;
  global_intercept=10.0;
  std::for_each(x, x+VECTOR_SIZE,
                global_line );

  std::for_each(x, x+VECTOR_SIZE,
                print );
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
