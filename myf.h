#ifndef _MYF_H_
#define _MYF_H_

#include <stdint.h>
#include "lcd.h"

typedef struct
{
  uint8_t  id[4];
  uint16_t imgWidth;
  uint16_t imgHeight;
  uint16_t clutOffset;
  uint16_t clutUsed;
  uint16_t reserved;
  uint16_t sequenceOffset;
  uint32_t sequenceSize;
}MYFHEAD_T;

typedef struct
{
  uint32_t firstPixIndx;
  uint32_t lastPixIndx;
  uint16_t nDraw;
  uint16_t nSkip;  
  uint16_t sc;
  uint16_t ec;
  uint16_t sp;
  uint16_t ep;
}DRAWBOUNDS_T;

class CMYF
{
public:
  CLCD lcd;
  bool GetDrawBounds(int16_t x, int16_t y, uint16_t width, uint16_t height, DRAWBOUNDS_T* db);
  void Draw_MYF(uint8_t* myf, int16_t x, int16_t y);
  void Draw_MYF_Start(uint8_t* myf, int16_t x, int16_t y);
  void DrawPart(uint8_t* myf, DRAWBOUNDS_T* db);
};

extern "C" void DrawPixelSequenceFull_Fast(uint8_t* seq, uint32_t seqSize, uint16_t* clut, uint32_t GPIOx_BASE);
void DrawPixelSequenceFull(uint8_t* seq, uint32_t seqSize, uint16_t* clut);


#endif /* _MYF_H_ */