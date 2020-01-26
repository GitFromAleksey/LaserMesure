#include <SPI.h>
#include "blink.h"
#include "timeout.h"

unsigned int time = millis();
bool input = false;
cBlink ledBlink(100);
cTimeout timeOut;

void setup()
{
  Serial.begin(19200);
  Serial.write('O');
  delay(500);
  Serial.write('D');
  //Serial.write('\n');
}

void serialEvent()
{
    while(Serial.available())
    {
      if((char)Serial.read() == '\n')
        input = true;
    }
    timeOut.TimeoutStart(1000);
}

void loop()
{
  if(timeOut.isTimeOver())
  {
    ledBlink.LedToggle();
    timeOut.TimeoutStart(100);
  }
  
//  ledBlink.run();
//  //Serial.write(millis());
//  //printf("%d", millis());
//  if(input)
//  {
//    delay(10);
//    input = false;
//    ledBlink.run();
//    Serial.write('D');
//  }
  
}
