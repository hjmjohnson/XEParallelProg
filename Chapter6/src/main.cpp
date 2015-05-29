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

  std::cout << "Time to calc :..." << std::setprecision(4) \
            << mid - start << std::endl;
  std::cout << "Time to print :..." << end - mid << std::endl;
  std::cout << "Time (Total) :..." << end - start << std::endl;
}
