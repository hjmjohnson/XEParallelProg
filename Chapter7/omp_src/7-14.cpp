#include <stdio.h>
#include <tbb/tbb.h>
void Delay(){for (int i=0; i < 1000000000; i++);}
tbb::task_group g;

void Work(int i)
{
  if(i > 4)
    return;
  g.run(
    [=]{ // spawn a task
      printf("S%d\n",i);
      Work(i + 1);
      Delay();
      printf("E %d\n",i);
    }
  );
}

int main()
{
  int i = 0;
  Work(i);
  g.wait(); // wait for tasks to complete
}