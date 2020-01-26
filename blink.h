#ifndef BLINK_H
#define BLINK_H

class cBlink
{

public:

  cBlink() : m_LedState(false), m_blinkDelay(1000), m_Time(millis())
  {
  	pinMode(LED_BUILTIN, OUTPUT);
  }
  cBlink(unsigned int delayTime) : m_LedState(false), m_Time(millis())
  {
    setBlinkPeriodMs(delayTime);
    
    pinMode(LED_BUILTIN, OUTPUT);
  }
  ~cBlink(){}
  
  void run(void)
  {
    if( (millis() - m_Time) > m_blinkDelay )
    {
    	m_Time = millis();
    	LedToggle();
    }

    if(millis() < m_Time)
      m_Time = millis();
  }

  void LedToggle()
  {
    if(m_LedState)
    {digitalWrite(LED_BUILTIN, HIGH); m_LedState = false;}
    else
    {digitalWrite(LED_BUILTIN, LOW); m_LedState = true;}
  }

  void setBlinkPeriodMs(unsigned int delayTime){ m_blinkDelay = delayTime; }
  
private:
  bool m_LedState;
  unsigned int m_blinkDelay;
  unsigned long m_Time;
  
};

#endif
