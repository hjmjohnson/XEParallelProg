#include <cilk/cilk.h>
#include <tbb/mutex.h>
#include <stdio.h>
int main()
{
  int a = 0;
  tbb::atomic<int> b;
  b = 0;
  int c = 0;
  tbb::mutex m;

  cilk_for(int i =0; i< 10000; i++)
  {
    m.lock();
    a++;
    m.unlock();
    b++;
    c++;
  }
  printf("a:%d, b:%d, c:%d\n",a,b,c);
}