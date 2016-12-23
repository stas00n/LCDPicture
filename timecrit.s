
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
  end