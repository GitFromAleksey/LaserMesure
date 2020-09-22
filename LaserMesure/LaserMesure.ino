#include <EEPROM.h>

//#include <SPI.h>
#include <stdio.h>
//#include "stdinout.h"
#include "blink.h"
#include "timeout.h"
#include "parser.h"
#include <SoftwareSerial.h>
#include "LedControl.h" //  Подключаем библиотеку
#include "SwT4sProtocolBuilder.h"
#include "SwT4sProtocolParser.h"

LedControl lc = LedControl(12, 11, 10, 1); // используемы пины ардуины для подключения, и сколько драйверов в цепочке

#define DIST_SIZE 4u
char dist[DIST_SIZE];  // массив для отображения расстояния
#define TX_BUF_SIZE   20u
char txBuffer[TX_BUF_SIZE];

// данные для калибровки расстояния
#define SIZE_REAL      4997.0f   // реальный измеренный размер
#define SIZE_REQUIRED  5000.0f   // требуемый размер

#define UART_DEBUG

//#define LASER_OPEN_CMD        (char)'O'
//#define LASER_CLOSE_CMD       (char)'C'
//#define LASER_SLOW_MESURE_CMD (char)'D'
//#define LASER_FAST_MESURE_CMD (char)'F'
//#define LASER_GET_INFO_CMD    (char)'S'
//#define END_OF_PACKET         (char)'#' // '\n'
//#define LASER_MESURE_CMD      LASER_SLOW_MESURE_CMD

#define DEFAULT_BLINK_PERIOD  500u // ms
#define DEFAULT_TIMEOUT       1000u // ms

#define TIMER_SEND_KEY        1000u
#define TIMER_SEND_GET_DATA   500u

#define KEY_NULL_PIN          13u

#define EEPROM_NULL_VALUE_ADDRESS   0

//unsigned int time = millis();
bool isInputData = false;

cBlink ledBlink(DEFAULT_BLINK_PERIOD);
cTimeout timeOut;
cTimeout timerKey;
cTimeout timerGetData;
cParser parser(0);
cSwT4sProtocolBuilder swT4sProtocolBuilder;
//SwT4sProtocolParser swT4sProtocolParser;

SoftwareSerial mySerial(8, 9); // RX, TX

void setup()
{
  Serial.begin(9600);

#ifdef UART_DEBUG
  mySerial.begin(9600);
  parser.SetSerial(&mySerial);
//  mySerial.println("Hello, world?");
#endif

  //Инициируем MAX7219
  lc.shutdown(0, false); // включаем дисплей энергосбережение дисплей
  lc.setIntensity(0, 15); // устанавливаем яркость (0-минимум, 15-максимум)
  lc.clearDisplay(0); // очищаем дисплей
  delay(500);

  pinMode(KEY_NULL_PIN, INPUT);
  digitalWrite(KEY_NULL_PIN, HIGH);
  
  parser.setParseDigitValue(EepromRead(EEPROM_NULL_VALUE_ADDRESS));
  parser.setNull(EepromRead(EEPROM_NULL_VALUE_ADDRESS));
  parser.setCorrectCoef(SIZE_REAL, SIZE_REQUIRED);
  IndicatorShow();
  delay(500);
}

void LaserInit()
{
  timeOut.TimeoutStart(DEFAULT_TIMEOUT);
  ledBlink.LedOn();
}

void IndicatorClear()
{
  for(uint8_t i = 0; i < DIST_SIZE; i++)
  {
    dist[i] = 0;
  }
}

void IndicatorShow()
{
  parser.getArray(dist);
  
  for (int a = 0; a < 4; a++)
  {
    //lc.setDigit(0, a, dist[a] , false);
    lc.setChar(0, a, dist[a] , false);
  }
}

void SerialSendData(char* buf, int bufSize)
{
  for(int i = 0; i < bufSize; ++i)
  {
    Serial.write(buf[i]);
  }
}

void serialEvent()
{
  char tmp;

  while(Serial.available())
  {
#ifdef UART_DEBUG
    tmp = Serial.read();
   // mySerial.write(tmp);
#endif
    parser.addNextChar(tmp);
  }
  
  timeOut.TimeoutStart(DEFAULT_TIMEOUT);
}

void EepromSave(int address, int val)
{
  EEPROM.write(address, val>>8);
  EEPROM.write(address+1, val);
}

int EepromRead(int address)
{
  return (int)((EEPROM.read(address)<<8) | EEPROM.read(address+1));
}

void loop()
{
  //ledBlink.run();
  timeOut.run();
  timerKey.run();
  timerGetData.run();

  if(timerKey.isTimeOver())
  {
    timerKey.TimeoutStart(TIMER_SEND_KEY);
    int dataSize = swT4sProtocolBuilder.KeyRead(txBuffer, TX_BUF_SIZE);
    delay(10);
    dataSize = swT4sProtocolBuilder.KeyRead(txBuffer, TX_BUF_SIZE);
    SerialSendData(txBuffer, dataSize);

    timerGetData.TimeoutStart(TIMER_SEND_KEY);
  }

  if(timerGetData.isTimeOver())
  {
    IndicatorShow();
    
    int dataSize = swT4sProtocolBuilder.KeyReadDisplayValue(txBuffer, TX_BUF_SIZE);
    SerialSendData(txBuffer, dataSize);
  }

  if(timeOut.isTimeOver())
  {
    ledBlink.LedOff();
    isInputData = false;

//    int dataSize = swT4sProtocolBuilder.KeyRead(txBuffer, TX_BUF_SIZE);
//    SerialSendData(txBuffer, dataSize);
//    delay(10);
//    SerialSendData(txBuffer, dataSize);
//    delay(10);
//    dataSize = swT4sProtocolBuilder.KeyReadDisplayValue(txBuffer, TX_BUF_SIZE);
//    SerialSendData(txBuffer, dataSize);
    
    timeOut.TimeoutStart(DEFAULT_TIMEOUT);
    //parser.setParseDigitValue(EepromRead(EEPROM_NULL_VALUE_ADDRESS)); // выводим все 0-ли при инициализации
    //IndicatorClear();
    IndicatorShow();
  }

//  if(isInputData)
//  {
//    delay(10);
//    isInputData = false;
////    Serial.write(LASER_MESURE_CMD);
//    ledBlink.LedOff();
//  }

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
