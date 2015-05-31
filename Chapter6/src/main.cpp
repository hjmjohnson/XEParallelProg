#include <fstream>
#include <iostream>
#include <iomanip>
#include "mandelbrot.h"
#include "StopWatch.h"


int main(int, char * [])
{
  StopWatch TotalTimer;
  TotalTimer.StartTimer();
  //1. First compute the madelbrot solution
  StopWatch MandelbrotTimer;
    {
    std::cout << "calculating..." << std::flush << std::endl;
    MandelbrotTimer.StartTimer();
    Mandelbrot();
    MandelbrotTimer.StopTimer();
    }

  ////////////////////////////////////////////
  //2. Second do tasks that only read the solution
  StopWatch MandelbrotSignatureTimer;
  size_t signature;
  const size_t known_signature=2035989842094878;
  StopWatch PrintTimer;

//#pragma omp parallel shared(zr,zi,zcolor), firstprivate(maxI,maxJ)
    {
//#pragma omp sections nowait
      {
      //2a. Compute the signature
//#pragma omp section
        {
        MandelbrotSignatureTimer.StartTimer();
        std::cout << "signature..." << std::flush << std::endl;
        signature = CalculateMandelbrotSignature();
        MandelbrotSignatureTimer.StopTimer();
        }

      //2b. Print to disk
//#pragma omp section
        {
        PrintTimer.StartTimer();
        std::cout << "printing..." << std::flush << std::endl;
        WriteMandlebrot();
        PrintTimer.StopTimer();
        }
      }
    }


  //Finally print results to screen
  std::cout << "Time_to_calc: " << std::setprecision(4) \
    << MandelbrotTimer.GetElapsedSeconds() << std::flush << std::endl;
  std::cout << "Time_to_print: "
      << PrintTimer.GetElapsedSeconds() << std::flush << std::endl;
  std::cout << "Time_to_signature: "
    << MandelbrotSignatureTimer.GetElapsedSeconds() << std::flush << std::endl;



  const double totalTime= MandelbrotTimer.GetElapsedSeconds() + PrintTimer.GetElapsedSeconds() + MandelbrotSignatureTimer.GetElapsedSeconds();
  TotalTimer.StopTimer();
  std::cout << "Time_Total: "
    << totalTime << " Wall_Time: " << TotalTimer.GetElapsedSeconds() << std::flush << std::endl;

  std::cout << "CurrentSignature = " << signature << " is different from known_signature by " << signature - known_signature << std::flush << std::endl;
}
