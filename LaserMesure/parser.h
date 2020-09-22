#ifndef PARSER_H
#define PARSER_H

//#include <string>
#include "stdinout.h"
#include <SoftwareSerial.h>

const unsigned char _RX_BUF_SIZE = 20;

const char BEGIN_SUBSTR[] = "ATD";
const char END_SUBSTR[] = "#";
const unsigned char DATA_LEN = 17;

class cParser
{
public:
  SoftwareSerial *serial; // указатель на экземпляр COM порта для отправки логов

  cParser(char laserCmd): m_ParseDigit(0), m_NullDigit(0), m_IsData(false), m_CorrectCoef(1.0),m_RxBufCnt(0)
  {
    m_OutCharBuf[0] = m_OutCharBuf[1] = m_OutCharBuf[2] = m_OutCharBuf[3] = 8;
    m_StringBuf = "";
    m_BeginSubstr = "ATD"; // laserCmd;
//    m_BeginSubstr = m_BeginSubstr + ": ";
  }
  ~cParser(){}

  void SetSerial(SoftwareSerial *serial)
  {
    this->serial = serial;
  }

  void getArray(char *dist)
  {
//    int tmp =  (m_NullDigit - m_ParseDigit) * m_CorrectCoef;
    int tmp = m_ParseDigit;
    //m_ParseDigit = 0;
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
// -----------------------------------------------------------------------------
  void addNextChar(unsigned char data)
  {
    m_RxBuf[m_RxBufCnt++] = data;
    if(m_RxBufCnt == _RX_BUF_SIZE)
      m_RxBufCnt = 0;
  
    int index = RxBufCheck(m_RxBuf, _RX_BUF_SIZE);
    if( index >= 0 )
    {
      int result = 0;
  
      result |= m_RxBuf[index+3]<<24;
      result |= m_RxBuf[index+4]<<16;
      result |= m_RxBuf[index+5]<<8;
      result |= m_RxBuf[index+6];

      ClearBuf(m_RxBuf, _RX_BUF_SIZE);
      m_ParseDigit = result/10;
      m_RxBufCnt = 0;

      m_IsData = true;
    }
    else
    {
      m_IsData = false;
    }
  }
// -----------------------------------------------------------------------------
  void _addNextChar(char ch)
  {
    int tmp = 0;

    int index = RxBufCheck(m_RxBuf, _RX_BUF_SIZE);
    
    //if(ch == '\n')
    if(ch == '#')
    {
//      if( (tmp = m_StringBuf.lastIndexOf(m_BeginSubstr)) > -1)
      if( (tmp = m_StringBuf.indexOf("ATD")) > -1)
      {
        m_ParseDigit = 0;
        m_ParseDigit |= m_RxBuf[3]<<24;
        m_ParseDigit |= m_RxBuf[4]<<16;
        m_ParseDigit |= m_RxBuf[5]<<8;
        m_ParseDigit |= m_RxBuf[6];
        m_ParseDigit /= 10;
        m_IsData = true;
        
        serial->println(m_StringBuf);
        serial->println(m_StringOut);
      }
      m_StringBuf = "";
      m_RxBufCnt = 0;
    }
    else
    {
      m_StringBuf += ch;
      m_RxBuf[m_RxBufCnt++] = ch;
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
  uint8_t m_RxBufCnt;
  uint8_t m_RxBuf[_RX_BUF_SIZE];
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

  int RxBufCheck(unsigned char* buf, unsigned char size)
  {
    bool is_find_begin = false;
    bool is_find_end = false;
    unsigned char index_begin = 0;
    unsigned char index_end = 0;
    unsigned char data_len = 0;
  
    for(unsigned char index = 0; index < size; ++index)
    {
      if(!is_find_begin)
        if(buf[index] == BEGIN_SUBSTR[0])
          if(buf[index+1] == BEGIN_SUBSTR[1])
            if(buf[index+2] == BEGIN_SUBSTR[2])
            {
              is_find_begin = true;
              index_begin = index;
              index = index + 3;
            }
  
      if(is_find_begin)
      {
        if(buf[index] == END_SUBSTR[0])
        {
          is_find_end = true;
          index_end = index;
          break;
        }
      }
    }
  
    if(is_find_begin && is_find_end)
    {
      data_len = index_end - index_begin;
      if((DATA_LEN-1) == data_len)
      {
        return index_begin;
      }
    }
  
    return -1;
  }

  void ClearBuf(unsigned char* buf, unsigned char size)
  {
    for(int i = 0; i < size; ++i)
    {
      buf[i] = 0;
    }
  }
};


#endif /* PARSER_H */
