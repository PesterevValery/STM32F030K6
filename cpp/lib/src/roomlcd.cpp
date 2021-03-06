#include "roomlcd.h"

uint8_t Roomlcd::buffer[32] = {0};

uint8_t Roomlcd::picS [37][2] = {
{10, 1},
{17, 2},
{10, 2},
{22, 2},
{17, 0},
{10, 3},
{11, 3},
{13, 3},
{16, 3},
{19, 3},
{22, 0},
{9, 0},
{9, 1},
{9, 2},
{9, 3},
{15, 0},
{15, 1},
{15, 2},
{15, 3},
{23, 2},
{21, 0},
{21, 1},
{21, 2},
{21, 3},
{23, 3},
{22, 3},
{0, 3},
{0, 2},
{3, 0},
{1, 0},
{7, 0},
{0, 1},
{0, 0},
{23, 1},
{23, 0}
};

uint8_t Roomlcd::digits [2][10] = {
{0x3F, 0x06, 0x6B, 0x2F, 0x36, 0x3D, 0x7D, 0x07, 0x7F, 0x3F},
{0xAF, 0x06, 0x6D, 0x4F, 0xC6, 0xCB, 0xEB, 0x0E, 0xEF, 0x6F}
};

Roomlcd::Roomlcd (Ht1621 & d)
:lcdDriver(&d)
{
 
}

void Roomlcd::setDigit (uint8_t val, digitsPosition n)
{
  uint8_t tempval=0;
  union
  {
   uint16_t full;
   uint8_t half [2];
  }
  tempaddr;
  tempaddr.full= static_cast <uint16_t>(n);
  tempval = buffer [tempaddr.half[1]];
  tempval &= ~ (1 << 3);
  if (static_cast <uint16_t>(n)<4)
  {   
    buffer [tempaddr.half[1]] = tempval|(digits[0][val] >> 4);
    buffer [tempaddr.half[0]] = digits[0][val]&0x0F;
  }
  else
  {
    buffer [tempaddr.half[1]] = tempval|(digits[1][val] >> 4);
    buffer [tempaddr.half[0]] = digits[1][val]&0x0F;
  }
}

void Roomlcd::setPic (pic p)
{
  uint8_t pic_ = static_cast<uint8_t>(p);
  uint8_t tempval=buffer [picS[pic_][0]];
  tempval |= 1 << picS[pic_][1];
  buffer [picS[pic_][0]] = tempval&0x0F;
}

void Roomlcd::clearPic (pic p)
{
  uint8_t pic_ = static_cast<uint8_t>(p);
  uint8_t tempval=buffer [picS[pic_][0]];
  tempval &= ~(1 << picS[pic_][1]);
  buffer [picS[pic_][0]] = tempval&0x0F;
}


