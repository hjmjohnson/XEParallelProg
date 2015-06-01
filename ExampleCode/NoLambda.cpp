#include <iostream>
#include <algorithm>
#include <vector>

size_t global_var_i; //
static void global_set_values(float & in )
{
  in = global_var_i;
  global_var_i++;
}

float global_slope;
float global_intercept;
static void global_print_line(float in)
{
  std::cout << in*global_slope+global_intercept << " ";
}

int main()
{
  constexpr size_t VECTOR_SIZE=100;
  float x[VECTOR_SIZE];

  global_var_i=0;
  std::for_each(x, x+VECTOR_SIZE, global_set_values );

  global_slope=2.0;
  global_intercept=10.0;
  std::for_each(x, x+VECTOR_SIZE, global_print_line );

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
