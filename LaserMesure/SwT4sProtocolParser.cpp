/*
 * SwT4sProtocolParser.cpp
 *
 *  Created on: 21 ����. 2020 �.
 *      Author: borzenkov
 */
#include "SwT4sProtocolParser.h"

//#define DEBUG

const char BEGIN_SUBSTR[] = "ATD";
const char END_SUBSTR[] = "#";
const unsigned char DATA_LEN = 17;

SwT4sProtocolParser::SwT4sProtocolParser() : m_ParseDigit(0), m_RxBufCnt(0){}

SwT4sProtocolParser::~SwT4sProtocolParser(){}

// ---------------------------------------------------------------------------------------
void SwT4sProtocolParser::AddData(unsigned char data)
{
	m_RxBuf[m_RxBufCnt++] = data;
	if(m_RxBufCnt == RX_BUF_SIZE)
		m_RxBufCnt = 0;

	int index = RxBufCheck(m_RxBuf, RX_BUF_SIZE);
	if( index >= 0 )
	{
		int result = 0;

		result |= m_RxBuf[index+3]<<24;
		result |= m_RxBuf[index+4]<<16;
		result |= m_RxBuf[index+5]<<8;
		result |= m_RxBuf[index+6];

    m_ParseDigit = result;
		m_RxBufCnt = 0;
	}
}
// ----------------------------------------------------------------------------
void SwT4sProtocolParser::getArray(char *dist)
{
//    int tmp =  (m_NullDigit - m_ParseDigit) * m_CorrectCoef;
  int tmp = m_ParseDigit;
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
// ----------------------------------------------------------------------------
// private:
// ----------------------------------------------------------------------------
int SwT4sProtocolParser::RxBufCheck(unsigned char* buf, unsigned char size)
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
