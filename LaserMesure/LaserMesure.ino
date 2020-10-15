#include <EEPROM.h>

#include <stdio.h>
#include "blink.h"
#include "timeout.h"
#include "parser.h"
#include "LedControl.h" //  Подключаем библиотеку индикатора
#include "SwT4sProtocolBuilder.h"
//#include "SwT4sProtocolParser.h"

LedControl lc = LedControl(12, 11, 10, 1); // используемы пины ардуины для подключения, и сколько драйверов в цепочке

#define DIST_SIZE 4u
char dist[DIST_SIZE];  // массив для отображения расстояния
#define TX_BUF_SIZE   20u
char txBuffer[TX_BUF_SIZE];

// данные для калибровки расстояния
#define SIZE_REAL      4997.0f   // реальный измеренный размер
#define SIZE_REQUIRED  5000.0f   // требуемый размер


#define DEFAULT_BLINK_PERIOD  500u // ms
#define DEFAULT_TIMEOUT       1000u // ms

enum eRequestModes
{
  firstTimeSendKey,
  secondTimeSendKey,
  sendDataRequest
};

eRequestModes RequestMode = firstTimeSendKey;

#define KEY_NULL_PIN                9u

#define EEPROM_NULL_VALUE_ADDRESS   0

bool isInputData = false;

cBlink ledBlink(DEFAULT_BLINK_PERIOD);
//cTimeout timeOut;
cTimeout timerRequest(millis);
cParser parser(0);
cSwT4sProtocolBuilder swT4sProtocolBuilder;
//SwT4sProtocolParser swT4sProtocolParser;

// ---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while(!Serial);

  //Инициируем MAX7219
  lc.shutdown(0, false);  // включаем дисплей энергосбережение дисплей
  lc.setIntensity(0, 15); // устанавливаем яркость (0-минимум, 15-максимум)
  lc.clearDisplay(0);     // очищаем дисплей
  delay(500);

  // инициализация кнопки установки нуля
  pinMode(KEY_NULL_PIN, INPUT);
  digitalWrite(KEY_NULL_PIN, HIGH);
  
  parser.setParseDigitValue(EepromRead(EEPROM_NULL_VALUE_ADDRESS));
  parser.setNull(EepromRead(EEPROM_NULL_VALUE_ADDRESS));
  parser.setCorrectCoef(SIZE_REAL, SIZE_REQUIRED);
  IndicatorShow();
  delay(500);
}
// ---------------------------------------------------------------------------------------
void IndicatorClear()
{
  for(uint8_t i = 0; i < DIST_SIZE; i++)
  {
    dist[i] = 0;
  }
}
// ---------------------------------------------------------------------------------------
void IndicatorShow()
{
  parser.getArray(dist);
  
  for (int a = 0; a < 4; a++)
  {
    lc.setChar(0, a, dist[a] , false);
  }
}
// ---------------------------------------------------------------------------------------
void SerialSendData(char* buf, int bufSize)
{
  Serial.write(buf, bufSize);
}
// ---------------------------------------------------------------------------------------
//void serialEvent()
//{
//}
// ---------------------------------------------------------------------------------------
void EepromSave(int address, int val)
{
  EEPROM.write(address, val>>8);
  EEPROM.write(address+1, val);
}
// ---------------------------------------------------------------------------------------
int EepromRead(int address)
{
  return (int)((EEPROM.read(address)<<8) | EEPROM.read(address+1));
}
// ---------------------------------------------------------------------------------------
void loop()
{
  int dataSize = 0;
  timerRequest.run();
//  ledBlink.run();
  
  if(Serial.available())
  {
    parser.addNextChar(Serial.read());
  }

  if(timerRequest.isTimeOver())
  {
    ledBlink.LedToggle();

    switch(RequestMode)
    {
      case firstTimeSendKey:
        // отправка кнопки READ
        IndicatorShow();
        
        dataSize = swT4sProtocolBuilder.KeyRead(txBuffer, TX_BUF_SIZE);
        SerialSendData(txBuffer, dataSize);
        timerRequest.TimeoutStart(15);
        RequestMode = secondTimeSendKey;
        break;
      case secondTimeSendKey:
        // отправка кнопки READ
        dataSize = swT4sProtocolBuilder.KeyRead(txBuffer, TX_BUF_SIZE);
        SerialSendData(txBuffer, dataSize);
        RequestMode = sendDataRequest;
        timerRequest.TimeoutStart(1000);
        break;
      case sendDataRequest:
        // запрос данных
        dataSize = swT4sProtocolBuilder.KeyReadDisplayValue(txBuffer, TX_BUF_SIZE);
        SerialSendData(txBuffer, dataSize);
        RequestMode = firstTimeSendKey;
        timerRequest.TimeoutStart(20);
        break;
      default:
        RequestMode = firstTimeSendKey;
        timerRequest.TimeoutStart(100);
        break;
    } 
  }

  if(digitalRead(KEY_NULL_PIN) == LOW)
  {
    int cnt = 100;
    while(digitalRead(KEY_NULL_PIN) == LOW)
    {
      delay(1);
      if(cnt-- == 0)
      {
        ledBlink.LedOn();
        IndicatorShow();
        EepromSave(EEPROM_NULL_VALUE_ADDRESS, parser.getCurrentLen());
        parser.setNull( parser.getCurrentLen());
        delay(3000);
      }
    }
  }

}
