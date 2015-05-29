#include "wtime.h"

#ifdef _WIN32
#include <windows.h>
double wtime()
{
  LARGE_INTEGER ticks;
  LARGE_INTEGER frequency;

  QueryPerformanceCounter(&ticks);
  QueryPerformanceFrequency(&frequency);
  return (double)(ticks.QuadPart / (double)frequency.QuadPart);
}

#else

#include <sys/time.h>
#include <sys/resource.h>
double wtime()
{
  struct timeval  time;
  struct timezone zone;

  gettimeofday(&time, &zone);
  return time.tv_sec + time.tv_usec * 1e-6;
}

#endif
