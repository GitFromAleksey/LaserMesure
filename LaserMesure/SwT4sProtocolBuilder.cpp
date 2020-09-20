#include "SwT4sProtocolBuilder.h"

const char PACKET_BEGIN_SEQUENSE[] = "AT";
const char PACKET_END_SYMBOL = '#';

const char PACKET_KEY_PRESS_IMITATION_SYMBOL = 'K';

const char PACKET_KEY_CODE_READ[] = "001";
const char PACKET_KEY_CODE_PLUS[] = "002";
const char PACKET_KEY_CODE_MENU[] = "003";
const char PACKET_KEY_CODE_MINUS[] = "004";
const char PACKET_KEY_CODE_AREA[] = "005";
const char PACKET_KEY_CODE_LEVEL_BUBBLE[] = "006";
const char PACKET_KEY_CODE_PYPHAGORAS[] = "007";
const char PACKET_KEY_CODE_TIMER[] = "008";
const char PACKET_KEY_CODE_CLEAR_OFF[] = "009";
const char PACKET_KEY_CODE_SAVE[] = "00A";
const char PACKET_KEY_CODE_READ_DISPLEY_VALUE[] = "00C";

cSwT4sProtocolBuilder::cSwT4sProtocolBuilder()
{
  
}
// -----------------------------------------------------------------------------
cSwT4sProtocolBuilder::~cSwT4sProtocolBuilder()
{
  
}
// -----------------------------------------------------------------------------
int cSwT4sProtocolBuilder::KeyRead(char* buf, int bufSize)
{
  return ProtocolSerealize(buf, bufSize, PACKET_KEY_CODE_READ);
}
// -----------------------------------------------------------------------------
int cSwT4sProtocolBuilder::KeyReadDisplayValue(char* buf, int bufSize)
{
  return ProtocolSerealize(buf, bufSize, PACKET_KEY_CODE_READ_DISPLEY_VALUE);
}
// -----------------------------------------------------------------------------
// private methods
// -----------------------------------------------------------------------------
int cSwT4sProtocolBuilder::ProtocolSerealize(char* buf, int bufSize, char* keyCode)
{
  if( (bufSize < 7) || (buf == 0))
    return -1;

  int cnt = 0;
  
  buf[cnt++] = PACKET_BEGIN_SEQUENSE[0];
  buf[cnt++] = PACKET_BEGIN_SEQUENSE[1];
  
  buf[cnt++] = PACKET_KEY_PRESS_IMITATION_SYMBOL;
  
  buf[cnt++] = keyCode[0];
  buf[cnt++] = keyCode[1];
  buf[cnt++] = keyCode[2];
  
  buf[cnt++] = PACKET_END_SYMBOL;

  return cnt;
}
