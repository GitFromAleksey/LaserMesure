/*
 * SwT4sProtocolParser.h
 *
 *  Created on: 21 ����. 2020 �.
 *      Author: borzenkov
 */

#ifndef SwT4sProtocolParser_H_
#define SwT4sProtocolParser_H_

#include <SoftwareSerial.h>

const unsigned char RX_BUF_SIZE = 20;

class SwT4sProtocolParser
{
  public:
    SwT4sProtocolParser();
    ~SwT4sProtocolParser();

    void AddData(unsigned char data);
    void getArray(char *dist);

  private:
    int m_ParseDigit;
    unsigned char m_RxBuf[RX_BUF_SIZE];
    unsigned char m_RxBufCnt;

    int RxBufCheck(unsigned char* buf, unsigned char size);
};

#endif /* SwT4sProtocolParser_H_ */
