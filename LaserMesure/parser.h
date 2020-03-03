#ifndef PARSER_H
#define PARSER_H

//#include <string>
#include "stdinout.h"
#include <SoftwareSerial.h>

class cParser
{
public:
  SoftwareSerial *serial; // указатель на экземпляр COM порта для отправки логов
  
  cParser(char laserCmd): m_ParseDigit(0), m_NullDigit(0), m_IsData(false), m_CorrectCoef(1.0)
  {
    m_OutCharBuf[0] = m_OutCharBuf[1] = m_OutCharBuf[2] = m_OutCharBuf[3] = 8;
    m_StringBuf = "";
    m_BeginSubstr = laserCmd;
    m_BeginSubstr = m_BeginSubstr + ": ";
  }
  ~cParser(){}

  void SetSerial(SoftwareSerial *serial)
  {
    this->serial = serial;
  }

  void getArray(char *dist)
  {
    int tmp =  (m_NullDigit - m_ParseDigit) * m_CorrectCoef;
    if(tmp < 0)
    {
      //tmp = 8888;
      tmp = abs(tmp);
      dist[3] = '-';
      dist[0] = tmp%10;
      tmp = tmp/10;
      dist[1] = tmp%10;
      tmp = tmp/10;
      dist[2] = tmp%10;
    }
    else
    {
      dist[0] = tmp%10;
      tmp = tmp/10;
      dist[1] = tmp%10;
      tmp = tmp/10;
      dist[2] = tmp%10;
      dist[3] = tmp/10;
    }
  }

  void addNextChar(char ch)
  {
    if(ch == '\n')
    {
      if(m_StringBuf.lastIndexOf(m_BeginSubstr) > -1)
      {
        m_StringBuf.replace(m_BeginSubstr,"");
        if(m_StringBuf.lastIndexOf("m,") > -1)
        {
          m_StringBuf.replace(".","");

          m_StringOut  = "";
          m_StringOut += m_StringBuf.charAt(0);
          m_StringOut += m_StringBuf.charAt(1);
          m_StringOut += m_StringBuf.charAt(2);
          m_StringOut += m_StringBuf.charAt(3);


          m_OutCharBuf[0] = CharToInt(m_StringBuf.charAt(0));
          m_OutCharBuf[1] = CharToInt(m_StringBuf.charAt(1));
          m_OutCharBuf[2] = CharToInt(m_StringBuf.charAt(2));
          m_OutCharBuf[3] = CharToInt(m_StringBuf.charAt(3));

          m_ParseDigit = 0;
          m_ParseDigit += m_OutCharBuf[0] * 1000;
          m_ParseDigit += m_OutCharBuf[1] * 100;
          m_ParseDigit += m_OutCharBuf[2] * 10;
          m_ParseDigit += m_OutCharBuf[3];

          m_IsData = true;
        }
        serial->println(m_StringBuf);
        serial->println(m_StringOut);
      }
      m_StringBuf = "";
    }
    else
    {
      m_StringBuf += ch;
      m_IsData = false;
    }
  }

  int getCurrentLen()const { return m_ParseDigit; }

  void setNull(const int _null) { m_NullDigit = _null; }

  void setParseDigitValue(const int val) { m_ParseDigit = val; }

  void setCorrectCoef(const float realSize, const float requiredSize) { m_CorrectCoef = requiredSize/realSize; }
  
private:
  String m_StringBuf; // для хранения входящей строки ответа от лазера
  String m_BeginSubstr;
  String m_StringOut; // распарсенный ответ от лазера в виде строки
  int m_ParseDigit;   // ответ от лазера в виде числа
  int m_NullDigit;    // нулевая координата, число от которого вычитается m_ParseDigit. Это и есть искомое расстояние
  int m_OutCharBuf[4];  // промежуточный буфер для конвертации строки в число
  bool m_IsData;        // флаг готовых данных
  float m_CorrectCoef;  // корректирующий коэффициент если набегает ошибка

  int CharToInt(char ch)
  {
    int res = 0;
    switch(ch)
    {
      case '0': res = 0; break;
      case '1': res = 1; break;
      case '2': res = 2; break;
      case '3': res = 3; break;
      case '4': res = 4; break;
      case '5': res = 5; break;
      case '6': res = 6; break;
      case '7': res = 7; break;
      case '8': res = 8; break;
      case '9': res = 9; break;
      default:           break;
    }
    return res;
  }
};


#endif /* PARSER_H */
