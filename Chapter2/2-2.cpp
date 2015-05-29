#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <stdio.h>

int main()
{
  cilk::reducer_opadd<int> j;

  cilk_for(int i = 0; i < 100; i++)
  {
    j += i;
  }
  printf("J is %d",j.get_value());
}