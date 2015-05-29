#include <stdio.h>
void Delay(){for (int i=0; i < 1000000000; i++);}
void Work(int i)
{
  if(i > 4)
    return;
  printf("S%d\n",i);
  Work(i + 1);
  Delay();
  printf("E %d\n",i);
}

int main()
{
  int i = 0;
  Work(i);
}