#include "timeout.h"

cTimeout::cTimeout() : m_TimeIsStart(false), m_TimeoutMs(0), m_PreviosTimeMs(0), m_CurrentTimeMs(0)
{}
cTimeout::cTimeout(unsigned long (*_millis)()) : m_TimeIsStart(false), m_TimeoutMs(0), m_PreviosTimeMs(0), m_CurrentTimeMs(0)
{ fmillis = _millis; }
cTimeout::~cTimeout(){}

void cTimeout::TimeoutStart(unsigned long timeoutMs)
{ 
	m_TimeoutMs = timeoutMs;
	m_PreviosTimeMs = fmillis();
  m_TimeIsStart = true;
}

unsigned long cTimeout::getCurrentTime()
{ return m_TimeoutMs;}

bool cTimeout::isTimeOver()
{
	run();
//	return (m_TimeoutMs == 0);
  return !m_TimeIsStart;
}

void cTimeout::run()
{
	m_CurrentTimeMs = fmillis();
  
	if(m_TimeIsStart)
	{
	  if( (m_CurrentTimeMs - m_PreviosTimeMs) > m_TimeoutMs) // таймер дотикал
	  {
		  m_TimeIsStart = false;
		  m_TimeoutMs = 0;
	  }
	  else
	  {
  		m_TimeoutMs = m_TimeoutMs - (m_CurrentTimeMs - m_PreviosTimeMs);
  		m_PreviosTimeMs = m_CurrentTimeMs;
	  }
	}
  else
  {
    m_PreviosTimeMs = m_CurrentTimeMs;
  }
}
