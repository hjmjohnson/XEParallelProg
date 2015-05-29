#include <stdio.h>
#include <omp.h>
static long num_steps = 10000 * 4;
double step;
double gsum1;
double gsum2;

void SafeAdd(double sum1, double sum2, omp_lock_t &lock1,omp_lock_t &lock2 )
{
  // lock gsum1 and update
  omp_set_lock( &lock1 );
  gsum1 += sum1;
  // lock gsum2 and update
  omp_set_lock( &lock2 );
  gsum2 += sum2;
  omp_unset_lock( &lock2 );
  omp_unset_lock( &lock1 );
}

int main()
{
  int i;
  double x1,x2;
  omp_lock_t lock1, lock2;
  gsum1=0.0;
  gsum2=0.0;

  omp_init_lock(&lock1);
  omp_init_lock(&lock2);
  printf("Calculating Pi ...\n");
  step = 1.0/(double) num_steps;
  for (i=0;i< num_steps; i+=4)
  {
    double sum1,sum2;
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        // calculate first bar
        x1 = (i+ 0.5)*step;
        x1*=x1;
        sum1 = 4.0/(1.0+x1);

        // calculate second bar
        x2 = (i+ 1.5)*step;
        x2*=x2;
        sum2 = 4.0/(1.0+x2);
        SafeAdd(sum1,sum2,lock1,lock2);
      }
      #pragma omp section
      {
        // calculate third bar
        x1 = (i+ 2.5)*step;
        x1*=x1;
        sum1 = 4.0/(1.0+x1);

        // calculate fourth bar
        x2 = (i+ 3.5)*step;
        x2*=x2;
        sum2 = 4.0/(1.0+x2);
        SafeAdd(sum1,sum2,lock2,lock1);
      }
    }
  }

  // calc value of pi
  double pi = step * (gsum1+gsum2);
  printf("pi: %2.21f\n",pi);
  omp_destroy_lock( &lock1 );
  omp_destroy_lock( &lock2 );
}