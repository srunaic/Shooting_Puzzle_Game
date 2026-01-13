#pragma once
#include <windows.h>

class Timer {
public:
  Timer();

  float GetDeltaTime() const; // Seconds
  float GetTotalTime() const; // Seconds

  void Reset();
  void Tick();

private:
  double m_secondsPerCount;
  double m_deltaTime;

  __int64 m_baseTime;
  __int64 m_prevTime;
  __int64 m_currTime;

  bool m_stopped;
};
