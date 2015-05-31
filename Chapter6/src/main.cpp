#include <fstream>
#include <iostream>
#include <iomanip>
#include "mandelbrot.h"
#include "StopWatch.h"


int main()
{
  std::cout << "calculating..." << std::endl;
  StopWatch ComputeMandelbrot;
  ComputeMandelbrot.StartTimer();

  Mandelbrot();
  ComputeMandelbrot.StopTimer();

  StopWatch PrintMandelbrot;
  PrintMandelbrot.StartTimer();
  std::cout << "printing..." << std::endl;
  WriteMandlebrot();
  PrintMandelbrot.StopTimer();

  std::cout << "Time_to_calc: " << std::setprecision(4) \
            << ComputeMandelbrot.GetElapsedSeconds() << std::endl;
  std::cout << "Time_to_print: "
            << PrintMandelbrot.GetElapsedSeconds() << std::endl;
  const double totalTime= ComputeMandelbrot.GetElapsedSeconds() + PrintMandelbrot.GetElapsedSeconds();
  std::cout << "Time_Total: "
 << totalTime << std::endl;
}
