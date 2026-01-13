#include "../Include/Timer.h"

Timer::Timer()
    : m_secondsPerCount(0.0), m_deltaTime(-1.0), m_baseTime(0), m_prevTime(0),
      m_currTime(0), m_stopped(false) {
  __int64 countsPerSec;
  QueryPerformanceFrequency((LARGE_INTEGER *)&countsPerSec);
  m_secondsPerCount = 1.0 / (double)countsPerSec;
}

float Timer::GetDeltaTime() const { return (float)m_deltaTime; }

float Timer::GetTotalTime() const {
  return (float)((m_currTime - m_baseTime) * m_secondsPerCount);
}

void Timer::Reset() {
  __int64 currTime;
  QueryPerformanceCounter((LARGE_INTEGER *)&currTime);

  m_baseTime = currTime;
  m_prevTime = currTime;
  m_stopped = false;
}

void Timer::Tick() {
  if (m_stopped) {
    m_deltaTime = 0.0;
    return;
  }

  __int64 currTime;
  QueryPerformanceCounter((LARGE_INTEGER *)&currTime);
  m_currTime = currTime;

  m_deltaTime = (m_currTime - m_prevTime) * m_secondsPerCount;

  m_prevTime = m_currTime;

  if (m_deltaTime < 0.0) {
    m_deltaTime = 0.0;
  }
}
