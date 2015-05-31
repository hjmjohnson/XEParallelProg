#include "mandelbrot.h"

//Global variables

float zr[maxI][maxJ];
float zi[maxI][maxJ];
float zcolor[maxI][maxJ];

static float CalcMandelbrot(const float r, const float i)
{
  float lzi = 0.0F;
  float lzr = 0.0F;
  int   itercount = 0;
  const float maxit = (float)maxIteration;

  while( itercount <= maxIteration )
    {
    ++itercount;
    const float temp = lzr * lzi;
    const float zr2 = lzr * lzr;
    const float zi2 = lzi * lzi;
    if( zi2 + zr2 > maxThreshold )
      {
      return (float)256.0F * itercount / maxit;
      }
    lzr = zr2 - zi2 + r;
    lzi = temp + temp + i;
    }

  return 1.0F;
}

static void SetZ( const int i, const int j, const float xinc, const float yinc )
{
  zr[i][j] = (float) -1.0F * deltaX / 2.0F + xinc * i;
  zi[i][j] = (float) 1.0F * deltaY / 2.0F - yinc * j;
  zcolor[i][j] = CalcMandelbrot(zr[i][j], zi[i][j] ) / 1.0001F;
}

void Mandelbrot()
{
  const float xinc = (float)deltaX / (maxI - 1);
  const float yinc = (float)deltaY / (maxJ - 1);

    {
//#pragma omp parallel for
#pragma omp parallel for collapse(2)
    for( int i = 0; i < maxI; ++i )
      {
      for( int j = 0; j < maxJ; ++j )
        {
        SetZ(i, j, xinc, yinc);
        }
      }
    }
}
