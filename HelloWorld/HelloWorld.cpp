#include <stdlib.h>
#include <iostream>
#include <omp.h>

int main()
{
// Add first
//#pragma omp parallel default(none) shared(std::cout)
  {
// Add second
//#pragma omp critical
   {
#if defined(_OPENMP)
   int id = omp_get_thread_num();
#else
   int id = 0;
#endif
   std::cout << "HelloWorld(" << id << ")"
             << std::flush << std::endl;
   }
  }
  return EXIT_SUCCESS;
}



