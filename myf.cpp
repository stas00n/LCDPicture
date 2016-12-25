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

void CMYF::DrawPart(CRect area, uint8_t* myf, int16_t x, int16_t y)
{
  MYFHEAD_T* head = (MYFHEAD_T*)myf;
  uint16_t* clut = (uint16_t*)(myf + head->clutOffset);
  uint8_t* seq = myf + head->sequenceOffset;
  uint32_t seqSize = head->sequenceSize;
  

  lcd.SetColumnAddress(area.left, area.left + area.width - 1);
  lcd.SetPageAddress(area.top, area.top + area.hidth - 1);
  
  
  uint32_t first = 110;
  uint32_t last = first + area.width * area.hidth;
  uint32_t npix = 0;
  
  lcd.WriteCom(0x2C);
  
  uint8_t colIndx, tmp;
  uint16_t rep;
  bool foundfirst = false;
  
  while(seqSize--)
  {
    tmp = *seq++;
    if(tmp < 0xFE)
    {
      colIndx = tmp;
      if(npix++ < first)
        continue;
      foundfirst = true;
      if(npix > last)
         break;
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
      npix += rep;
      if(npix < first)
        continue;
      if(!foundfirst)
      {
        rep = npix - first;
        WritePixels(clut[colIndx], rep, GPIOC_BASE);
        foundfirst = true;
        npix = first;
        continue;
      }
      if(npix > last)
      {
        npix -= rep;
        rep = last - npix;
        WritePixels(clut[colIndx], rep, GPIOC_BASE);
        break;
      }
      WritePixels(clut[colIndx], rep, GPIOC_BASE);
    }
  }
}