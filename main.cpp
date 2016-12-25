#include "main.h"

extern const unsigned char x4548y2605[];
extern const unsigned char x4548y2606[];
extern const unsigned char y20825[];

CLCD lcd;
CMYF myf;

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


  
  // Fill screen then cycle fill color
  while(1)
  {
    // Clear screen (Fill Black)
    rect.top = 0;
    rect.left = 24;
    rect.width = 272;
    rect.hidth = 482;
    lcd.FillRect(&rect, 0);
    
    rect.left = 30;
    rect.top = 50;
    rect.width = 256;
    rect.hidth = 256;
    myf.DrawPart(rect, (uint8_t*)x4548y2605, 0, 0);

  }
}



