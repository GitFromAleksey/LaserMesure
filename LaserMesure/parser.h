#ifndef PARSER_H
#define PARSER_H

//#include <string>
#include "stdinout.h"
#include <SoftwareSerial.h>

class cParser
{
public:
  SoftwareSerial *serial;
  
  cParser():m_IsData(false)
  {
    m_OutChar[0] = m_OutChar[1] = m_OutChar[2] = m_OutChar[3] = 8;
    m_Buf = "";
  }
  ~cParser(){}

  void SetSerial(SoftwareSerial *serial)
  {
    this->serial = serial;
  }

  void getArray(int *dist)
  {
    dist[0] = m_OutChar[3];
    dist[1] = m_OutChar[2];
    dist[2] = m_OutChar[1];
    dist[3] = m_OutChar[0];
  }

  void addNextChar(char ch)
  {
    
    if(ch == '\n')
    {
      if(m_Buf.lastIndexOf("D: ") > -1 )
      {
        m_Buf.replace("D: ","");
        if(m_Buf.lastIndexOf("m,") > -1)
        {
          m_Buf.replace(".","");
          m_out  = "";
          m_out += m_Buf.charAt(0);
          m_OutChar[0] = CharToInt(m_Buf.charAt(0));
          m_out += m_Buf.charAt(1);
          m_OutChar[1] = CharToInt(m_Buf.charAt(1));
          m_out += m_Buf.charAt(2);
          m_OutChar[2] = CharToInt(m_Buf.charAt(2));
          m_out += m_Buf.charAt(3);
          m_OutChar[3] = CharToInt(m_Buf.charAt(3));
          m_IsData = true;
        }
        serial->println(m_Buf);
        serial->println(m_out);//Print();
      }
      m_Buf = "";
    }
    else
    {
      m_Buf += ch;
      m_IsData = false;
    }
  }

private:
  String m_Buf;
  String m_out;
  int m_OutChar[4];
  bool m_IsData;

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
      default : break;
    }
    return res;
  }
};


#endif /* PARSER_H */
