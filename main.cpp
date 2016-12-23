#include "main.h"
#include "picture.h"


CLCD lcd;

void main()
{
  Clock_Config();
  GPIO_Config();
  

  GPIO_ResetPin(PIN_LCD_RST);
  GPIO_SetPin(PIN_LCD_RD);
  GPIO_SetPin(PIN_LCD_WR);
  GPIO_SetPin(PIN_LCD_CS);
  __delay(50000);
  GPIO_SetPin(PIN_LCD_RST);
  __delay(50000);
  
  lcd.WriteCom(1);      // SW Reset  
  lcd.WriteCom(0x11);   // Exit Sleep
  __delay(100000);
  
  lcd.WriteCom(0x36);   //Set Address Mode
  lcd.WriteData(0x48);  //(0x48);
  lcd.WriteCom(0x3A);   //Set Pixel Format
  lcd.WriteData(0x05);
  lcd.WriteCom(0x29);   //set display on
  
  CRect rect;
  uint16_t colors[4] = {0xF800, 0x07E0, 0x001F, 0x0000}; // R, G, B, BK
  uint8_t indx = 0;     // Color indx
  
  // Clear screen (Fill Black)
  rect.top = 0;
  rect.left = 24;
  rect.width = 272;
  rect.hidth = 482;
  lcd.FillRect(&rect, 0);
  
  // Fill screen then cycle fill color
  while(1)
  {
    // Set Breakpoint here...
    // lcd.FillRect(&rect, colors[indx]);
    rect.top = 209;
    rect.left = 128;
    rect.width = 64;
    rect.hidth = 64;
    lcd.MemRect(&rect, (uint16_t*)tile2);
    // indx++;
    // indx &= 3;
  }
}



