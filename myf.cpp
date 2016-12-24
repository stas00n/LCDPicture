#include "myf.h"



void CMYF::Draw_MYF_Start(uint8_t* myf, uint16_t x, uint16_t y)
{
  MYFHEAD_T* head = (MYFHEAD_T*)myf;
  uint16_t* clut = (uint16_t*)(myf + head->clutOffset);
  uint8_t* sequence = myf + head->sequenceOffset;
  uint32_t seqSize = head->sequenceSize;
  

  lcd.SetColumnAddress(x, x + head->imgWidth - 1);
  lcd.SetPageAddress(y, y + head->imgHeight - 1);
  lcd.WriteCom(0x2C);
  
  DrawPixelSequenceFull(sequence, seqSize, clut);
  DrawPixelSequenceFull_Fast(sequence, seqSize, clut, GPIOC_BASE);
}

void DrawPixelSequenceFull(uint8_t* seq, uint32_t seqSize, uint16_t* clut)
{
  uint8_t colIndx, tmp;
  uint16_t rep;
  
  while(seqSize--)
  {
    tmp = *seq++;
    if(tmp < 0xFE)
    {
      colIndx = tmp;
      WritePixels(clut[tmp], 1, GPIOC_BASE);
    }
    else
    {
      rep = *(seq++);
      seqSize--;
      if(tmp == 0xFE)
      {
        rep |= (*(seq++) << 8);
        seqSize--;
      }
      WritePixels(clut[colIndx], rep, GPIOC_BASE);
    }
  }
}  