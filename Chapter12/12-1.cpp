#include <stdio.h>
#define USE_API
#ifdef USE_API
#include "ittnotify.h"
#define ITT_PAUSE __itt_pause()
#define ITT_RESUME __itt_resume()
#else
#define ITT_PAUSE
#define ITT_RESUME
#endif

int LoopTwo(){int i;for (i = 0 ; i < 100000000; i++);return i;}

int LoopOne(int i)
{
  i++;
  if (i > 50)
    return i;
  for (int j = 0 ; j < 10000000; j++);
  return LoopOne(i);
}

int main(int argc, char * argv[])
{
  int a,b;
  ITT_PAUSE; // start paused

  a = LoopOne(0);
  printf("LoopOne Returns %d\n",a);

  ITT_RESUME; // collect data

  b = LoopTwo();
  printf("LoopTwo Returns %d\n",b);
  ITT_PAUSE; // pause data collection

  return a + b;
}