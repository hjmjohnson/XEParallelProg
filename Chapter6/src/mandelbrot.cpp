#include "mandelbrot.h"

float CalcMandelbrot(float r, float i)
{
  float zi = 0.0;
  float zr = 0.0;
  int   itercount = 0;
  float maxit = (float)maxIteration;

  while( 1 )
    {
    itercount++;
    float temp = zr * zi;
    float zr2 = zr * zr;
    float zi2 = zi * zi;
    zr = zr2 - zi2 + r;
    zi = temp + temp + i;
    if( zi2 + zr2 > maxThreshold )
      {
      return (float)256 * itercount / maxit;
      }
    if( itercount > maxIteration )
      {
      return (float)1.0;
      }
    }

  return 1;
}

void SetZ( int i, int j, float xinc, float yinc )
{
  zr[i][j] = (float) -1.0 * deltaX / 2.0 + xinc * i;
  zi[i][j] = (float) 1.0 * deltaY / 2.0 - yinc * j;
  zcolor[i][j] = CalcMandelbrot(zr[i][j], zi[i][j] ) / 1.0001;
}

void Mandelbrot()
{
  float xinc = (float)deltaX / (maxI - 1);
  float yinc = (float)deltaY / (maxJ - 1);

  for( int i = 0; i < maxI; i++ )
    {
    for( int j = 0; j < maxJ; j++ )
      {
      SetZ(i, j, xinc, yinc);
      }
    }
}
