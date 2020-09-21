/*
 * cParser.cpp
 *
 *  Created on: 21 сент. 2020 г.
 *      Author: borzenkov
 */
#include "cParser.h"

//#define DEBUG

const char BEGIN_SUBSTR[] = "ATD";
const char END_SUBSTR[] = "#";
const unsigned char DATA_LEN = 17;

cParser::cParser() : m_RxBufCnt(0)
{

}

cParser::~cParser()
{

}

void cParser::AddData(unsigned char data)
{
	m_RxBuf[m_RxBufCnt++] = data;
	if(m_RxBufCnt == RX_BUF_SIZE)
		m_RxBufCnt = 0;

	int index = RxBufCheck(m_RxBuf, RX_BUF_SIZE);
	if( index >= 0 )
	{
		unsigned int result = 0;

		result |= m_RxBuf[index+3]<<24;
		result |= m_RxBuf[index+4]<<16;
		result |= m_RxBuf[index+5]<<8;
		result |= m_RxBuf[index+6];

		m_RxBufCnt = 0;
		std::cout << "packet is find, result = " << result << std::endl;
	}
}
// ----------------------------------------------------------------------------
// private:
// ----------------------------------------------------------------------------
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
#ifdef DEBUG
			std::cout << "DATA_LEN == data_len" << std::endl;
#endif
			return index_begin;
		}
	}

	return -1;
}
