#include "LedControl.h" //  Подключаем библиотеку
LedControl lc = LedControl(12, 11, 10, 1); // используемы пины ардуины для подключения, и сколько драйверов в цепочке
// pin 12 is connected to the CS (CS)(LOAD)
// pin 11 is connected to the CLK (CLK)
// pin 10 is connected to LOAD(DIN)

int dist[4];  // массив для измеренного расстояния
void setup()
{
  //Инициируем MAX7219
  lc.shutdown(0, false); // включаем дисплей энергосбережение дисплей
  lc.setIntensity(0, 15); // устанавливаем яркость (0-минимум, 15-максимум)
  lc.clearDisplay(0);// очищаем дисплей
}


void loop()
{

  lc.clearDisplay(0);

  for (int a = 0; a < 4; a++)
  {
    dist[a] = a;
    lc.setDigit(0, a, dist[a] , false);
    delay(10);
  }



}
