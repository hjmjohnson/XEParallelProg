#include <stdio.h>
#include <iostream>
#include "StopWatch.h"
void Delay(){for (int i=0; i < 1000000000; i++);}
void Work1(){printf("Start 1\n");Delay();printf("End 1\n");}
void Work2(){printf("Start 2\n");Delay();printf("End 2\n");}
void Work3(){printf("Start 3\n");Delay();printf("End 3\n");}
int main()
{
  StopWatch TotalTimer;
  TotalTimer.StartTimer();
  #pragma omp parallel sections default(none)
  {
    #pragma omp section
    {
      Work1();
      Work2();
    }
    #pragma omp section
    Work3();
  }
  TotalTimer.StopTimer();
  std::cout << "Time_Total: " << TotalTimer.GetElapsedSeconds() << std::flush << std::endl;
}
