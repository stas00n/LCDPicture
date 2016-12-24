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

class CMYF
{
public:
  CLCD lcd; 
  void Draw_MYF_Start(uint8_t* myf, uint16_t x, uint16_t y); 
};

extern "C" void DrawPixelSequenceFull(uint8_t* seq, uint32_t seqSize, uint16_t* clut, uint32_t GPIOx_BASE);



#endif /* _MYF_H_ */