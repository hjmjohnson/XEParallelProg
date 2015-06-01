#include <stdio.h>
#include <iostream>
#include "StopWatch.h"
void Delay(){for (int i=0; i < 1000000000; i++);}
void Work(int i)
{
  if(i > 4)
    return;
  #pragma omp task firstprivate(i)
  {
    printf("S%d\n",i);
    Work(i + 1);
    Delay();
    printf("E %d\n",i);
  }
}

int main()
{
  StopWatch TotalTimer;
  TotalTimer.StartTimer();
  int i = 0;
  #pragma omp parallel
  #pragma omp single
  {
    Work(i);
  }
  TotalTimer.StopTimer();
  std::cout << "Time_Total: " << TotalTimer.GetElapsedSeconds() << std::flush << std::endl;
}
