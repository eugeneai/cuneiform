/*
Copyright (c) 1993-2008, Cognitive Technologies
All rights reserved.

����������� ��������� ��������������� � ������������� ��� � ���� ��������� ����,
��� � � �������� �����, � ����������� ��� ���, ��� ���������� ��������� �������:

      * ��� ��������� ��������������� ��������� ���� ������ ���������� ���������
        ���� ����������� �� ��������� �����, ���� ������ ������� � ����������� 
        ����� �� ��������. 
      * ��� ��������� ��������������� ��������� ���� � ������������ �/��� � 
        ������ ����������, ������������ ��� ���������������, ������ �����������
        ��������� ���� ���������� �� ��������� �����, ���� ������ ������� �
        ����������� ����� �� ��������.  
      * �� �������� Cognitive Technologies, �� ����� �� ����������� �� ����� 
        ���� ������������ � �������� �������� ��������� �/��� ����������� 
        ���������, ���������� �� ���� ��, ��� ���������������� �����������
        ����������. 

��� ��������� ������������� ����������� ��������� ���� �/��� ������� ������ "���
��� ����" ��� ������-���� ���� ��������, ���������� ���� ��� ���������������, 
������� �������� ������������ �������� � ����������� ��� ���������� ����, �� ��
������������� ���. �� �������� ��������� ���� � �� ���� ������ ����, ������� 
����� �������� �/��� �������� �������������� ���������, �� � ���� ������ �� 
��Ѩ� ���������������, ������� ����� �����, ���������, ����������� ��� 
������������� ������, ��������� � �������������� ��� ���������� ���������� 
������������� ������������� ��������� (������� ������ ������, ��� ������, 
������� ���������, ��� ������ �/��� ������ �������, ���������� ��-�� �������� 
������� ��� �/��� ������ ��������� �������� ��������� � ������� �����������, 
�� �� ������������� ����� ��������), �� �� ������������� ���, ���� ���� ����� 
�������� ��� ������ ���� ���� �������� � ����������� ����� ������� � ������.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Cognitive Technologies nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string.h>
#include "ccom.h"
#include "ccom_fun.h"
static Word8 make_fill[] = {0, 1, 3, 7, 15, 31, 63, 127, 255};
static Bool32 StoreOneInterval( Word8 *p, int end , int len,Word8 *pe)
{
Int16     sh;
Word16    w;
p = p + (end>>3);
if( p>=pe )
    return FALSE;
sh = end & 7;
while (len > 8)   { w = 0xff00 >> sh;*p |= w & 0xff; *(--p) |= w>>8; len-=8; }
w = make_fill[len]; w = w << (8-sh); *p |= w & 0xff; *(p-1) |= w >> 8;
return TRUE;
}


Bool32 Linerep2Raster(CCOM_lnhead *linerep, Int16 size, 
                      Int16 w, Int16 h, Int16 c, Int16 r,
                      RecRaster *rec, Bool32 bChangeSize)
{
    int         ww, len, i, wmax;
    CCOM_lnhead    * line;
    CCOM_interval  * inter;
    Word8   *pe=rec->Raster+REC_MAX_RASTER_SIZE;
    
    if( !w || !h || c+w>rec->lnPixWidth || r+h>rec->lnPixHeight )
        return FALSE;
    ww = REC_GW_WORD8(rec->lnPixWidth);
    
    if (bChangeSize) // ����� ���� ����������
     {
       for(line=linerep,wmax=len=0; len<size && line->lth; len+=line->lth,line=(CCOM_lnhead    *)((int)line+line->lth))
       {
           for(inter = (CCOM_interval*)(line+1), i=0; i<line->h; i++, inter++)
           {
               if( !StoreOneInterval( &rec->Raster[ (line->row+r+i)*ww ], inter->e+c, inter->l,pe) )
                   return FALSE;
               if( inter->e+c>wmax )
                   wmax=inter->e+c;
           }
       }

       if( (ww==REC_GW_WORD8(wmax)) ) 
                 //// ��������� ��� �����������
        {
          rec->lnPixWidth=wmax;
        }
     }
    else //bChangeSize==false ����� �� ���� ����������
     {
       for(line=linerep,wmax=len=0; len<size && line->lth; len+=line->lth,line=(CCOM_lnhead    *)((int)line+line->lth))
       {
           for(inter = (CCOM_interval*)(line+1), i=0; i<line->h; i++, inter++)
           {
               if( !StoreOneInterval( &rec->Raster[ (line->row+r+i)*ww ], inter->e+c, inter->l,pe) )
                   return FALSE;
           }
       }
     }
    
    return TRUE;
}


Bool32 Linerep2ExtRaster(CCOM_lnhead *linerep, Int16 size, 
                      Int16 w, Int16 h, Int16 c, Int16 r,
                      RecRaster *rec)
{
int         ww, len, i;
CCOM_lnhead    * line;
CCOM_interval  * inter;
Word8   *pe=rec->Raster+REC_MAX_RASTER_SIZE;

if( !w || !h || c+w>rec->lnPixWidth || r+h>rec->lnPixHeight )
  return FALSE;
ww = REC_GW_WORD8(rec->lnPixWidth);

for(line=linerep,len=0; len<size && line->lth; len+=line->lth,line=(CCOM_lnhead    *)((int)line+line->lth))
  {
  for(inter = (CCOM_interval*)(line+1), i=0; i<line->h; i++, inter++)
    {
    if( !StoreOneInterval( &rec->Raster[ (line->row+r+i)*ww*2   ], (inter->e)*2+c, inter->l*2,pe) )
        return FALSE;
    if( !StoreOneInterval( &rec->Raster[ (line->row+r+i)*ww*2+ww], (inter->e)*2+c, inter->l*2,pe) )
        return FALSE;
    }
  }

return TRUE;
}

static Bool32 StoreOneScaleInterval (Word8 *p,  Int32 h, Int32 b, Int32 e, Int32 bw, Int32 scale,Word8*pe)
{
b>>=scale;
e>>=scale;
if( b==e )
    {
    if( b )
        b--;
    else 
        e++;
    }
return StoreOneInterval ( &p[(h>>scale)*bw] , e , e-b,pe);
}


Bool32 Linerep2ScaleRaster(CCOM_lnhead *linerep, Int16 size, 
                      Int16 w, Int16 h, Int16 c, Int16 r,
                      RecRaster *rec,Int32 scale)
{
int         ww, len, i;
CCOM_lnhead    * line;
CCOM_interval  * inter;
Word8   *pe=rec->Raster+REC_MAX_RASTER_SIZE;

if( !w || !h || c+w>(rec->lnPixWidth<<scale) || r+h>(rec->lnPixHeight<<scale) )
  return FALSE;
ww = REC_GW_WORD8(rec->lnPixWidth);

for(line=linerep,len=0; len<size && line->lth; len+=line->lth,line=(CCOM_lnhead    *)((int)line+line->lth))
  {
  for(inter = (CCOM_interval*)(line+1), i=0; i<line->h; i++, inter++)
    {
    if( !StoreOneScaleInterval( &rec->Raster[0],line->row+i, inter->e+c-inter->l, inter->e+c,ww,scale,pe) )
        return FALSE;
    }
  }
return TRUE;
}
