#include <cilk/cilk.h>
#include <stdio.h>
void Delay(){for (int i=0; i < 1000000000; i++);}
void Work1(){printf("Start 1\n");Delay();printf("End 1\n");}
void Work2(){printf("Start 2\n");Delay();printf("End 2\n");}
void Work3(){printf("Start 3\n");Delay();printf("End 3\n");}
int main()
{
  cilk_spawn Work1();
  cilk_spawn Work2();
  Work3();
  cilk_sync;// not really needed, because there is an implicit sync here
}