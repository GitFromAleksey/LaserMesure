#ifndef TIMEOUT_H
#define TIMEOUT_H

class cTimeout
{
public:
  cTimeout() : m_TimeoutMs(0), m_CurrentTimeMs(0)
  {}
  ~cTimeout(){}

  void TimeoutStart(unsigned long timeoutMs)
  { 
    m_TimeoutMs = timeoutMs;
    m_CurrentTimeMs = millis();
  }

  unsigned long getCurrentTime()
  { return m_TimeoutMs;}

  bool isTimeOver()
  {
    run();
    return (m_TimeoutMs == 0);
  }
  
  void run()
  {
    if(m_TimeoutMs > 0)
    {
      if( (millis() - m_CurrentTimeMs) > m_TimeoutMs)
      {
        m_TimeoutMs = 0;
      }
      else
      {
        m_TimeoutMs = m_TimeoutMs - (millis() - m_CurrentTimeMs);
        m_CurrentTimeMs = millis();
      }
    }
  }
private:
  unsigned long m_TimeoutMs;
  unsigned long m_CurrentTimeMs;
};

#endif /* TIMEOUT_H */
