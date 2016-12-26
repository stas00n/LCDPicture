#include "myf.h"

bool CMYF::GetDrawBounds(int16_t x, int16_t y, uint16_t width, uint16_t height, DRAWBOUNDS_T* db)
{
  int sc;
  bool fits = true;
  // x bounds
  if(x < 0)
  {
    sc = DISP_COL_MIN;
    fits = false;
  }
  else sc = DISP_COL_MIN + x;
  
  if(sc > DISP_COL_MAX)
  {
    sc = DISP_COL_MAX;
    fits = false;
  }
  db->sc = (uint16_t)sc;
  
  int ec;
  ec = DISP_COL_MIN + x + width - 1;
  if(ec > DISP_COL_MAX)
  {
    ec = DISP_COL_MAX;
    fits = false;
  }
  if(ec < sc)
    ec = sc;
  
  if(ec > DISP_COL_MAX)
  {
    ec = DISP_COL_MAX;
    fits = false;
  }
  
  db->ec = (uint16_t)ec;
  
  // y bounds
  int sp;
  if(y < 0)
  {
    sp = DISP_PAGE_MIN;
    fits = false;
  } 
  else sp = DISP_PAGE_MIN + y;
  
  if(sp > DISP_PAGE_MAX)
  {
    sp = DISP_PAGE_MAX;
    fits = false;
  }
  db->sp = (uint16_t)sp;
  
  int ep;
  ep = DISP_PAGE_MIN + y + height - 1;
  if(ep < sp)
    ep = sp;
  if(ep > DISP_PAGE_MAX)
  {
    ep = DISP_PAGE_MAX;
    fits = false;
  }
  db->ep = (uint16_t)ep;
  
  // First
  if(y < 0) db->firstPixIndx = -y * width;
  else db->firstPixIndx = 0;
  if(x < 0) db->firstPixIndx += -x;
  // Last
  db->lastPixIndx = db->firstPixIndx + (ep - sp) * width + ec - sc;
  // Draw-Skip
  db->nDraw = ec - sc + 1;
  db->nSkip = width - (ec - sc) - 1;
  
  return fits;
}

void CMYF::Draw_MYF(uint8_t* myf, int16_t x, int16_t y)
{
  //GetDrawBounds(DRAWBOUNDS_T* db
}



void CMYF::Draw_MYF_Start(uint8_t* myf, int16_t x, int16_t y)
{
  MYFHEAD_T* head = (MYFHEAD_T*)myf;
  uint16_t* clut = (uint16_t*)(myf + head->clutOffset);
  uint8_t* sequence = myf + head->sequenceOffset;
  uint32_t seqSize = head->sequenceSize;
  
  DRAWBOUNDS_T db;
  bool fits = GetDrawBounds(x, y, head->imgWidth, head->imgHeight,&db);
  lcd.SetColumnAddress(db.sc, db.ec);
  lcd.SetPageAddress(db.sp, db.ep);
  
  lcd.WriteCom(0x2C);
  
  if(fits)
    DrawPixelSequenceFull(sequence, seqSize, clut);
  else
    DrawPart(myf, &db);
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

void CMYF::DrawPart(uint8_t* myf, DRAWBOUNDS_T* db)
{
  MYFHEAD_T* head = (MYFHEAD_T*)myf;
  uint16_t* clut = (uint16_t*)(myf + head->clutOffset);
  uint8_t* seq = myf + head->sequenceOffset;
  uint32_t seqSize = head->sequenceSize;
  
    
  
  uint32_t first = db->firstPixIndx;
  uint32_t lastlast = db->lastPixIndx;
  uint32_t next = first;
  uint32_t last = first + db->nDraw;
  uint32_t npix = 0;
  int32_t remrep = 0;
  int32_t drawLim = -(db->nDraw * (db->ep - db->sp + 1));// Temp hang protection
  
  lcd.WriteCom(0x2C);
  
  uint8_t colIndx, tmp;
  uint16_t rep;
  bool foundnext = false;
  
  while(npix < lastlast)
  {
    if(remrep > 0)
    {
      npix += remrep;
      if(npix > last)
      {
        npix -= remrep;
        rep = last - npix;
        npix += rep;
      }
      else rep = remrep;
      WritePixels(clut[colIndx], rep, GPIOC_BASE);
      
      remrep -= rep;
      remrep -= db->nSkip;
      if(npix >= last)
      {
        next += db->nDraw + db->nSkip;
        last = next + db->nDraw;
        foundnext = false;
        continue;
      }
    }
    while(seqSize--)
    {
      tmp = *seq++;
      if(tmp < 0xFE)
      {
        colIndx = tmp;
        if(npix++ < next)
          continue;
        foundnext = true;
        if(npix > last)
          break;
        drawLim += 1;
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
        if(npix < next)
          continue;
        if(!foundnext)
        {
          rep = npix - next;
          drawLim += rep;
          WritePixels(clut[colIndx], rep, GPIOC_BASE);
          foundnext = true;
          npix = next + rep;
          continue;
        }
        if(npix > last)
        {
          remrep = rep;
          npix -= rep;
          rep = last - npix;
          drawLim += rep;
          WritePixels(clut[colIndx], rep, GPIOC_BASE);
          npix += rep;
          remrep -= rep;
          remrep -= db->nSkip;
          break;
        }
        drawLim += rep;
        WritePixels(clut[colIndx], rep, GPIOC_BASE);
      }
      if(drawLim > 0)break;
      if(npix >= last)break;
    }/* while (seqSize) */
    next += db->nDraw + db->nSkip;
    last = next + db->nDraw;
    foundnext = false;
    if(drawLim > 0)break;
  }/* while(npix < lastlast) */

}