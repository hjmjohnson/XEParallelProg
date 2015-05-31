#include "mandelbrot.h"
#include <cmath>

//Global variables

float zr[maxI][maxJ];
float zi[maxI][maxJ];
float zcolor[maxI][maxJ];


/*
* http://www.cplusplus.com/forum/beginner/10076/
*/
/*
static size_t VerySlowLargestPrime(const size_t TheNum)
{
  size_t FactorCount = 0;
  for (size_t i=TheNum; i>=2; --i)
    {
    for (size_t j=2; j<i; ++j)
      {
      if (i % j == 0)
        {
        ++FactorCount;
        }
      }
    if (FactorCount == 0)
      {
      return i;
      break;
      }
    FactorCount = 0;
    }
  return 0;
}
*/

static size_t LargestPrime(size_t TheNum)
{
  TheNum = TheNum % 10000; //Keep this under to reasonable speeds
  size_t FactorCount = 0;
  for (size_t i=TheNum; i>=2; --i)
    {
    for (size_t j=2; j<std::sqrt(i) + 1; ++j)  // HERE
      {
      if (i % j == 0)
        {
        ++FactorCount;
        break;  // HERE
        }
      }
    if (FactorCount == 0)
      {
      return i;
      break;
      }
    FactorCount = 0;
    }
  return 0;
}


/* A method to compute the signature to ensure that the same
 * results are produced for each run.
 *
 * Simply compute the sum of all white voxels multiplied by index location.
 */
size_t CalculateMandelbrotSignature()
{
  size_t signature = 0.0;
#pragma omp parallel for reduction(+:signature)
  for( size_t i = 0; i < maxI; ++i )
    {
    const size_t primeX = LargestPrime(i);
    for( size_t j = 0; j < maxJ; ++j )
      {
      const float color = zcolor[i][j];
      const bool isWhite = ( color >= .99999 );
      if(isWhite)
       { //NOTE: This is a silly signature for demonstration purposes
       const size_t primeY = LargestPrime(j);
       signature += primeX+primeY*maxI;
       }
      }
    }
  return signature;
}

static float CalcMandelbrot(const float r, const float i)
{
  float lzi = 0.0F;
  float lzr = 0.0F;
  size_t   itercount = 0;
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

static void SetZ( const size_t i, const size_t j, const float xinc, const float yinc )
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
    for( size_t i = 0; i < maxI; ++i )
      {
      for( size_t j = 0; j < maxJ; ++j )
        {
        SetZ(i, j, xinc, yinc);
        }
      }
    }
}
