#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

const unsigned char _RX_BUF_SIZE = 50;

const char BEGIN_SUBSTR[] = "ATD";
const char END_SUBSTR[] = "#";
const unsigned char DATA_LEN = 17; // длина нужного пакета данных

class cParser
{
public:

  cParser(char laserCmd);

  ~cParser();

  void getArray(char *dist);

  void addNextChar(unsigned char data);

  int getCurrentLen()const;

  void setNull(const int _null);

  void setParseDigitValue(const int val);

  void setCorrectCoef(const float realSize, const float requiredSize);

private:
  int m_ParseDigit;     // ответ от лазера в виде числа
  int m_NullDigit;      // нулевая координата, число от которого вычитается m_ParseDigit. Это и есть искомое расстояние
  int m_OutCharBuf[4];  // промежуточный буфер для конвертации строки в число
  uint8_t m_RxBufCnt;
  uint8_t m_RxBuf[_RX_BUF_SIZE];
  bool m_IsData;        // флаг готовых данных
  float m_CorrectCoef;  // корректирующий коэффициент если набегает ошибка
  

  int CharToInt(char ch);

  int RxBufCheck(unsigned char* buf, unsigned char size);

  void ClearBuf(unsigned char* buf, unsigned char _size);

};

#endif /* PARSER_H */
