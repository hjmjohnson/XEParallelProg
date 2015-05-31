#include <fstream>
#include <iostream>
#include <iomanip>
#include "mandelbrot.h"
#include "wtime.h"


int main()
{
  std::cout << "calculating..." << std::endl;
  const double start = wtime();

  Mandelbrot();
  const double mid = wtime();

  std::cout << "printing..." << std::endl;
  WriteMandlebrot();
  const double end = wtime();

  std::cout << "Time_to_calc: " << std::setprecision(4) \
            << mid - start << std::endl;
  std::cout << "Time_to_print: " << end - mid << std::endl;
  std::cout << "Time_Total: " << end - start << std::endl;
}
