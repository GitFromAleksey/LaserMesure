#include "parser.h"
//
//
//cParser::cParser(): m_ParseDigit(0), m_NullDigit(0), m_IsData(false), m_CorrectCoef(1.0),m_RxBufCnt(0)
//{
//	Logger("cParser()");
//	m_OutCharBuf[0] = m_OutCharBuf[1] = m_OutCharBuf[2] = m_OutCharBuf[3] = 8;
//}
cParser::cParser(char laserCmd): m_ParseDigit(0), m_NullDigit(0), m_IsData(false), m_CorrectCoef(1.0),m_RxBufCnt(0)
{
  m_OutCharBuf[0] = m_OutCharBuf[1] = m_OutCharBuf[2] = m_OutCharBuf[3] = 8;
//  m_StringBuf = "";
//  m_BeginSubstr = "ATD"; // laserCmd;
}
//// ----------------------------------------------------------------------------
cParser::~cParser(){}
//
void cParser::getArray(char *dist)
{
  int tmp =  (m_NullDigit - m_ParseDigit) * m_CorrectCoef;
//  int tmp = m_ParseDigit;

  //m_ParseDigit = 0;
  if(tmp < 0)
  {
    //tmp = 8888;
    tmp = (tmp < 0)?(-tmp):(tmp);
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
//// ----------------------------------------------------------------------------
void cParser::addNextChar(unsigned char data)
{
  m_RxBuf[m_RxBufCnt++] = data;

  if(m_RxBufCnt == _RX_BUF_SIZE)
  {
    ClearBuf(m_RxBuf, _RX_BUF_SIZE);
    m_RxBufCnt = 0;
  }

  int index = RxBufCheck(m_RxBuf, _RX_BUF_SIZE);

  if( index >= 0 )
  {
    uint32_t result = 0;

    result |= (uint32_t)m_RxBuf[index+3]<<24;
    result |= (uint32_t)m_RxBuf[index+4]<<16;
    result |= (uint32_t)m_RxBuf[index+5]<<8;
    result |= (uint32_t)m_RxBuf[index+6];
    m_ParseDigit = result/10;
    m_IsData = true;

    ClearBuf(m_RxBuf, _RX_BUF_SIZE);
    m_RxBufCnt = 0;
  }
  else
  {
    if(index == -2)
    {
      ClearBuf(m_RxBuf, _RX_BUF_SIZE);
      m_RxBufCnt = 0;
    }
    m_IsData = false;
  }
}
//// ----------------------------------------------------------------------------
int cParser::getCurrentLen()const { return m_ParseDigit; }
//// ----------------------------------------------------------------------------
void cParser::setNull(const int _null) { m_NullDigit = _null; }
//// ----------------------------------------------------------------------------
void cParser::setParseDigitValue(const int val) { m_ParseDigit = val; }
//// ----------------------------------------------------------------------------
void cParser::setCorrectCoef(const float realSize, const float requiredSize)
{ m_CorrectCoef = requiredSize/realSize; }
//// ----------------------------------------------------------------------------
//// private
//// ----------------------------------------------------------------------------
// private:
int cParser::CharToInt(char ch)
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
// ----------------------------------------------------------------------------
// private:
int cParser::RxBufCheck(unsigned char* buf, unsigned char size)
{
  bool is_find_begin = false;
  bool is_find_end = false;
  unsigned char index_begin = 0;
  unsigned char index_end = 0;
  unsigned char data_len = 0;

  for(unsigned char index = 0; index < size; ++index)
  {
    if(!is_find_begin)
    {
      if(buf[index] == BEGIN_SUBSTR[0])
      {
        if(buf[index+1] == BEGIN_SUBSTR[1])
        {
          if(buf[index+2] == BEGIN_SUBSTR[2])
          {
            is_find_begin = true;
            index_begin = index;
            index = index + 3;
          }
        }
      }
    }

    if(buf[index] == END_SUBSTR[0])
    {
      if(is_find_begin)
      {
        is_find_end = true;
        index_end = index;
        break;
      }
      else
      {
        return -2;
      }
    }
  }

  if(is_find_begin && is_find_end)
  {
    data_len = index_end - index_begin;
    if((DATA_LEN-1) == data_len)
    {
      return index_begin; // нужный пакет
    }
    else
    {
      return -2; // другой пакет
    }
  }

  return -1; // нет данных
}
// ----------------------------------------------------------------------------
// private:
void cParser::ClearBuf(unsigned char* buf, unsigned char _size)
{
  for(int i = 0; i < _size; ++i)
  {
    buf[i] = 0;
  }
}
