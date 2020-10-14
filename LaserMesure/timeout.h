#ifndef TIMEOUT_H
#define TIMEOUT_H

class cTimeout
{
public:
  cTimeout();
  cTimeout(unsigned long (*_millis)());
  ~cTimeout();

  void TimeoutStart(unsigned long timeoutMs);

  unsigned long getCurrentTime();

  bool isTimeOver();
  
  void run();
  
private:
  bool m_TimeIsStart;
  unsigned long m_TimeoutMs;
  unsigned long m_PreviosTimeMs; 
  unsigned long m_CurrentTimeMs;
  unsigned long (*fmillis)();
};

#endif /* TIMEOUT_H */
