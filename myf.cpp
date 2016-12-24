#include "myf.h"



void CMYF::Draw_MYF_Start(uint8_t* myf, uint16_t x, uint16_t y)
{
  MYFHEAD_T* head = (MYFHEAD_T*)myf;
  uint32_t nPix = head->imgWidth * head->imgHeight;
  uint16_t* clut = (uint16_t*)(myf + head->clutOffset);
  uint8_t* sequence = myf + head->sequenceOffset;
  uint32_t seqSize = head->sequenceSize;
  

  lcd.SetColumnAddress(x, x + head->imgWidth - 1);
  lcd.SetPageAddress(y, y + head->imgHeight - 1);
  lcd.WriteCom(0x2C);
  
  uint8_t colIndx, tmp;
  uint16_t rep;
  for (uint32_t i = 0; i < seqSize; i++)
  {
    tmp = sequence[i];
    if(tmp < 0xFE)
    {
      colIndx = tmp;
      WritePixels(clut[colIndx], 1, GPIOC_BASE);
    }
    else
    {
      rep = sequence[++i];
      if(tmp == 0xFE)
        rep |= (sequence[++i] << 8);
      WritePixels(clut[colIndx], rep, GPIOC_BASE);
    }
  }  
}