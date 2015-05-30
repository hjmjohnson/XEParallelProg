#include "mandelbrot.h"

static float CalcMandelbrot(float r, float i)
{
  float zi = 0.0F;
  float zr = 0.0F;
  int   itercount = 0;
  const float maxit = (float)maxIteration;

  while( itercount <= maxIteration )
    {
    itercount++;
    const float temp = zr * zi;
    const float zr2 = zr * zr;
    const float zi2 = zi * zi;
    zr = zr2 - zi2 + r;
    zi = temp + temp + i;
    if( zi2 + zr2 > maxThreshold )
      {
      return (float)256.0F * itercount / maxit;
      }
    }

  return 1.0F;
}

static void SetZ( int i, int j, float xinc, float yinc )
{
  zr[i][j] = (float) -1.0F * deltaX / 2.0F + xinc * i;
  zi[i][j] = (float) 1.0F * deltaY / 2.0F - yinc * j;
  zcolor[i][j] = CalcMandelbrot(zr[i][j], zi[i][j] ) / 1.0001F;
}

void Mandelbrot()
{
  const float xinc = (float)deltaX / (maxI - 1);
  const float yinc = (float)deltaY / (maxJ - 1);

  for( int i = 0; i < maxI; ++i )
    {
    for( int j = 0; j < maxJ; ++j )
      {
      SetZ(i, j, xinc, yinc);
      }
    }
}
