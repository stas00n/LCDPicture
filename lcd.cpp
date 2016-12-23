#include "lcd.h"
  
CLCD::CLCD(){;}
CLCD::~CLCD(){;}

void CLCD::SetColumnAddress(uint16_t startCol, uint16_t endCol)
{
  WriteCom(0x2A);
  WriteData(startCol >> 8);
  WriteData((uint8_t)startCol);
  WriteData(endCol >> 8);
  WriteData((uint8_t)endCol);
}

void CLCD::SetPageAddress(uint16_t startPg, uint16_t endPg)
{
  WriteCom(0x2B);
  WriteData(startPg >> 8);
  WriteData((uint8_t)startPg);
  WriteData(endPg >> 8);
  WriteData((uint8_t)endPg);
}

void CLCD::FillRect(CRect* rect, uint16_t color)
{
  uint32_t nPixels = rect->width * rect->hidth;
  SetColumnAddress(rect->left, rect->left + rect->width - 1);
  SetPageAddress(rect->top, rect->top + rect->hidth - 1);
  WriteCom(0x2C);
  
  uint16_t pixel = color;
  
  WritePixels(pixel, nPixels, GPIOC_BASE);

}

void CLCD::MemRect(CRect* rect, uint16_t* mem)
{
  uint16_t pix;
  uint32_t nPixels = rect->width * rect->hidth;
  SetColumnAddress(rect->left, rect->left + rect->width - 1);
  SetPageAddress(rect->top, rect->top + rect->hidth - 1);
  WriteCom(0x2C);
  
    
  for(uint32_t i = 0; i < nPixels; i++)
  {
    pix = *mem++;
    WritePixels(pix, 1, GPIOC_BASE);
//    WriteData((uint8_t)(pix >> 8));
//    WriteData((uint8_t)pix);
  }
}

void CLCD::WriteCom(uint8_t com)
{
  GPIO_ResetPin(PIN_LCD_CS);
  GPIO_ResetPin(PIN_LCD_DCX);
  GPIO_ResetPin(PIN_LCD_WR);
  GPIOC->ODR = com;
  GPIO_SetPin(PIN_LCD_WR);
  GPIO_SetPin(PIN_LCD_DCX);
}

void CLCD::WriteData (uint8_t data)
{
  GPIO_ResetPin(PIN_LCD_CS);
  GPIO_SetPin(PIN_LCD_DCX);
  GPIO_ResetPin(PIN_LCD_WR);
  GPIOC->ODR = data;
  GPIO_SetPin(PIN_LCD_WR);
}