/*
 * cParser.h
 *
 *  Created on: 21 сент. 2020 г.
 *      Author: borzenkov
 */

#ifndef CPARSER_H_
#define CPARSER_H_

#include <iostream>

const unsigned char RX_BUF_SIZE = 20;

class cParser
{
  public:
    cParser();
    virtual ~cParser();

    void AddData(unsigned char data);

  private:

    unsigned char m_RxBuf[RX_BUF_SIZE];
    unsigned char m_RxBufCnt;

    int RxBufCheck(unsigned char* buf, unsigned char size);
};

#endif /* CPARSER_H_ */
