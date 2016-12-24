
 section .text:CODE
  PUBLIC WritePixels
WritePixels
;r0 = pixel;
;r1 = nPixels;
;r2 = GPIOx Base
;r5 - value to write bsrr
  push {r4-r6}
  movs  r4, #255 ;LSB in r4
  ands  r4, r4, r0
  lsrs r0, r0, #8 ;MSB in r0
  movs r5, #1  ;load BSRR value
  lsls r5, r5, #8
  
  movs r6, #0
  mvns r6, r6 ; -1 in r6
_lp1  
  strh          r0, [r2, #0x14];write odr
  strh          r5,[r2, #0x18]
  adds          r1, r1, r6
  strh          r4, [r2, #0x14]
  strh          r5, [r2, #0x18]
  bne           _lp1  
  
  pop {r4-r6}
  bx      lr
  
  
  PUBLIC WritePixelsBitmap
WritePixelsBitmap       ;(uint16_t* bm, uint32_t nPixels, uint32_t GPIOx_BASE);
  
  push          {r4}
  movs          r3, #1                  ;load BSRR value
  lsls          r3, r3, #8
  
_lp2
  ldrb          r4,[r0, #1]
  strh          r4, [r2, #0x14]         ;write odr
  strh          r3,[r2, #0x18]
  ldrb          r4, [r0]
  strh          r4, [r2, #0x14]
  strh          r3, [r2, #0x18]
  adds          r0, r0, #2
  subs          r1, r1, #1
  bne           _lp2
  
  pop           {r4}  
  bx lr
  
  
  PUBLIC WritePixelsBitmap2
WritePixelsBitmap2       ;(uint16_t* bm, uint32_t nPixels, uint32_t GPIOx_BASE);
  
  push          {r4-r6}
  movs          r3, #1                  ;load BSRR value
  movs          r6, #255                ;mask
  lsls          r3, r3, #8
  
  lsrs          r1, r1, #1              ;count uint32
  
_lp3
  ldr           r5,[r0]
  
  lsrs          r4, r5, #8
  ands          r4, r6
  strh          r4, [r2, #0x14]         ;write odr
  strh          r3,[r2, #0x18]
  
  movs          r4, r5
  ands          r4, r6
  strh          r4, [r2, #0x14]
  strh          r3, [r2, #0x18]
  
  lsrs          r4, r5, #24
  ands          r4, r6
  strh          r4, [r2, #0x14]
  strh          r3, [r2, #0x18]
  
  lsrs          r4, r5, #16
  ands          r4, r6
  strh          r4, [r2, #0x14]
  strh          r3, [r2, #0x18]
  
  adds          r0, r0, #4
  subs          r1, r1, #1
  bne           _lp3
  
  pop           {r4-r6}  
  bx lr
  end
  end