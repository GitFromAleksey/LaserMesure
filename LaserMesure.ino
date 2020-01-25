#include <SPI.h>
#include "blink.h"

bool input = false;
Blink *ledBlink;

void setup()
{
  ledBlink = new Blink();
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
//      Serial.write(Serial.read());
      if((char)Serial.read() == '\n')
        input = true;
    }
}

void loop()
{
  //delay(5000);
  if(input)
  {
    delay(10);
    input = false;
    ledBlink->run();
    Serial.write('D');
  }
  //Serial.write('\n');
}
