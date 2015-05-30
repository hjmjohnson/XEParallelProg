#include <fstream>
#include <iostream>
#include <iomanip>
#include "mandelbrot.h"
#include "wtime.h"

float zr[maxI][maxJ], zi[maxI][maxJ];
float zcolor[maxI][maxJ];

int main()
{
  std::cout << "calculating..." << std::endl;
  double start = wtime();

  Mandelbrot();
  double mid = wtime();

  std::cout << "printing..." << std::endl;
  WriteMandlebrot();
  double end = wtime();

  std::cout << "Time_to_calc: " << std::setprecision(4) \
            << mid - start << std::endl;
  std::cout << "Time_to_print: " << end - mid << std::endl;
  std::cout << "Time_Total: " << end - start << std::endl;
}
