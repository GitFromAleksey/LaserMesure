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
  {m_Buf = "";}
  ~cParser(){}

  void SetSerial(SoftwareSerial *serial)
  {
    this->serial = serial;
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
          m_OutChar[0] = m_Buf.charAt(0);
          m_out += m_Buf.charAt(1);
          m_OutChar[1] = m_Buf.charAt(1);
          m_out += m_Buf.charAt(2);
          m_OutChar[2] = m_Buf.charAt(2);
          m_out += m_Buf.charAt(3);
          m_OutChar[3] = m_Buf.charAt(3);
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
  char m_OutChar[4];
  bool m_IsData;
};


#endif /* PARSER_H */
