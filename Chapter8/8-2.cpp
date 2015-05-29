#include <tbb/tbb.h>
#include <stdio.h>
int main()
{
  int a,b;
  tbb::concurrent_queue<int> queue;
  for(int i =0; i< 100; i++)
  queue.push(i);

   tbb::parallel_invoke(
   [&]{
     while(queue.try_pop(a)){
       printf("a%d ",a);
     }
   },
   [&]{
     while(queue.try_pop(b)){
       printf("b%d ",b);
       }
     }
   );
 }