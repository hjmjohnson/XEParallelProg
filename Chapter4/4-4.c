#include <stdio.h>
// need to create specific function versions
__declspec(cpu_dispatch(generic, future_cpu_16))
void dispatch_func() {};

__declspec(cpu_specific(generic))
void dispatch_func() { printf("Generic \n");}

__declspec(cpu_specific(future_cpu_16))
 void dispatch_func(){ printf("AVX!\n");}

int main()
{
  dispatch_func();
  return 0;
}
