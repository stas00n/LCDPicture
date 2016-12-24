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
  uint8_t* seqEnd = sequence + seqSize;
  
  DrawPixelSequenceFull(sequence, seqSize, clut, GPIOC_BASE);
  
//  while(sequence < seqEnd)
//  {
//    tmp = *sequence++;
//    if(tmp < 0xFE)
//    {
//      colIndx = tmp;
//      WritePixels(clut[tmp], 1, GPIOC_BASE);
//    }
//    else
//    {
//      rep = *(sequence++);
//      if(tmp == 0xFE)
//        rep |= (*(sequence++) << 8);
//      WritePixels(clut[colIndx], rep, GPIOC_BASE);
//    }
//  }  
}

//void DrawPixelSequenceFull(uint8_t* seq, uint32_t seqSize, uint16_t* clut, uint32_t GPIOx_BASE)
//{
//  uint8_t tmp, colIndx;
//  uint16_t BSRR = 0x100;
//  uint16_t rep, cl,ch;
//  
//  
//  while(seqSize--)
//  {
//    tmp = *(seq++);
//    if(tmp < 0xFE)
//    {
//      colIndx = tmp;
//      cl = clut[colIndx];
//      ch = cl >> 8;
//      cl &= 0xFF;
//      *((uint16_t*)(GPIOx_BASE + 0x14)) = ch;
//      *((uint16_t*)(GPIOx_BASE + 0x18)) = BSRR;
//      *((uint16_t*)(GPIOx_BASE + 0x14)) = cl;
//      *((uint16_t*)(GPIOx_BASE + 0x18)) = BSRR;
//    }
//    else
//    {
//      rep = *(seq++);
//      seqSize--;
//      if(tmp == 0xFE)
//      {
//        rep |= (*(seq++) << 8);
//        seqSize--;
//      }
//      while(rep--)
//      {
//        *((uint16_t*)(GPIOx_BASE + 0x14)) = ch;
//        *((uint16_t*)(GPIOx_BASE + 0x18)) = BSRR;
//        *((uint16_t*)(GPIOx_BASE + 0x14)) = cl;
//        *((uint16_t*)(GPIOx_BASE + 0x18)) = BSRR;
//      }
//    }
//  }
//  
//}