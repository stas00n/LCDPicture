#include "main.h"

// Pictures
extern const unsigned char x4548y2605[];
extern const unsigned char x4548y2606[];
extern const unsigned char y20825[];
extern const unsigned char test1[];

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
  
  
  while(1)
  {
    lcd.Clear();
//    myf.Draw_MYF_Start((uint8_t*)test1,-5 ,0);
    myf.Draw_MYF_Start((uint8_t*)x4548y2605,-5 ,-1);
    
    myf.Draw_MYF_Start((uint8_t*)x4548y2606, -5, 255);
  }
}



