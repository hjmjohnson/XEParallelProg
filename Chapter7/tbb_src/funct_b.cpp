#include <tbb/tbb.h>
#include <stdio.h>
void Delay(){for (int i=0; i < 1000000000; i++);}
void Work1(){printf("Start 1\n");Delay();printf("End 1\n");}
void Work2(){printf("Start 2\n");Delay();printf("End 2\n");}
void Work3(){printf("Start 3\n");Delay();printf("End 3\n");}
int main()
{
  tbb::parallel_invoke(
  []{Work1();},
  []{Work2();},
  []{Work3();}
  );
}