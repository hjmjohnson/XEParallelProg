#include <stdio.h>
#include <omp.h>
int main()
{
  int j = 0;
  // create a parallel region
  #pragma omp parallel
  {
    // this task will run on just one thread
    #pragma omp single nowait
    {
      for (int i = 0; i < 10; i++)
      {
        // every time loop iteration hits this next line
        // an omp task will be created and will
        // be run the moment a thread is available
        #pragma omp task firstprivate(i)
        {
          #pragma omp atomic
          j++;
          printf("i: %d thread:%d\n",i,omp_get_thread_num());
        } // end #pragma omp task
      } // end for …
    } //end #pragma omp single nowait
  } // end #pragma omp parallel
  return 0;
}