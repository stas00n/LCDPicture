#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>
#include "stm32f0xx.h"
#include "hardware.h"
#include "gpioex.h"

class CRect
{
public:
  uint16_t top;
  uint16_t left;
  uint16_t width;
  uint16_t hidth;
};

class CLCD
{
public:
  CLCD();
  ~CLCD();
  
  void WriteCom(uint8_t com);
  void WriteData (uint8_t data);
  
  
  void SetColumnAddress(uint16_t startCol, uint16_t endCol);
  void SetPageAddress(uint16_t startPg, uint16_t endPg);
  
  void WriteMemoryStart();
  void FillRect(CRect* rect, uint16_t pColor);
  void MemRect(CRect* rect, uint16_t* mem);
  
};





/*---------------------"C" Linkage funcs:------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
  
void WritePixels(uint16_t pixel, uint32_t numPixels, uint32_t GPIOx_BASE);
  
#ifdef __cplusplus
}
#endif
/*---------------------------------------------------------------------------*/


#endif /* _LCD_H_ */