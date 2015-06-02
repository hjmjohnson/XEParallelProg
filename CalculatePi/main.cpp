//  Created by Hans Johnson on 5/15/15.
//  Copyright (c) 2015 Hans Johnson. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "StopWatch.h"

/**
 * \brief Compute PI
 */
static double pi()
{
  return std::atan2(0,-1.0);
}

/**
 * \brief A unit circle has an area equal to pi
 *
 * Accumulate all grid pixel locations that are
 * are less than a distance of 1 from the origin
 * in the positive R^2 quadrant.
 */
static double CaluculatePiByEstimatingUnitCircleArea(const size_t numSubdivisions)
{

  const double dx = 1.0/static_cast<double>(numSubdivisions);
  const double quarterAreaPixel = dx*dx;

  double quarterArea = 0.0;
  //CONSIDERATIONS  ..
  for(size_t y=0; y < numSubdivisions; ++y)
    {
    for(size_t x=0; x < numSubdivisions; ++x)
      {
      const double xloc = static_cast<double>(x) * dx;
      const double yloc = static_cast<double>(y) * dx;

      const double radius = xloc*xloc+yloc*yloc;
      if (radius < 1 )
        {
        quarterArea += quarterAreaPixel;
        }
      }
    }
    const double areaUnitCircle=quarterArea*4;
  return areaUnitCircle;
}


/**
 * \brief Program to compute PI using brute force a niave algorithm.
 */
int main(int argc, const char * argv[])
{

  std::cout << "Calculating pi by computing the of 1/4 unit-circle." << std::endl;

  StopWatch PiTimer;
  PiTimer.StartTimer();
  const double areaUnitCircle = CaluculatePiByEstimatingUnitCircleArea(50000);
  PiTimer.StopTimer();

  std::cout << std::setprecision(17) ;
  std::cout << "Accurate   PI = " << pi() << std::endl;
  std::cout << "Calculated PI = " << areaUnitCircle << std::endl;
  std::cout << "ERROR         = " << areaUnitCircle - pi() << std::endl;
  std::cout << "Seconds       = " << PiTimer.GetElapsedSeconds() << std::endl;
  return EXIT_SUCCESS;
}
