//
//  StopWatch.h
//  CalculatePi
//
//  Created by Hans Johnson on 5/31/15.
//  Copyright (c) 2015 Hans Johnson. All rights reserved.
//

#ifndef CalculatePi_StopWatch_h
#define CalculatePi_StopWatch_h

#include <chrono>
/**
 * \brief A simple timer class
 *
 *   StopWatch myTimer;
 *   myTimer.StartTimer();
 *   // < Do Stuff >
 *   myTimer.StopTimer();
 *   std::cout << "Seconds       = " << myTimer.GetElapsedSeconds() << std::endl;
 *
 */
class StopWatch
{
public:
  void StartTimer()
  {
  this->m_clock_start = std::chrono::high_resolution_clock::now();
  }
  void StopTimer()
  {
  this->m_clock_stop = std::chrono::high_resolution_clock::now();
  }
  double GetElapsedSeconds() const
  {
  const std::chrono::duration<double> elapsed_seconds = m_clock_stop-m_clock_start;
  return elapsed_seconds.count();
  };
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_clock_start;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_clock_stop;
};


#endif
