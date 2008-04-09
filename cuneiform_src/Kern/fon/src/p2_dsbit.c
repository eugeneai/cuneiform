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

 // use weighted distance
#define _WEIDIST_

#include "c_types.h"
#include <string.h>

#include "fon.h"
#include "sfont.h"
extern int  Num11[256];
/**************************************/
// Bitmap distance from b1 to b2
// black point == 1 !
static SINT DistanceBitDLL(BYTE *b1,SINT xbyte1,SINT yrow1,
						 BYTE  *b2,SINT xbyte2,SINT yrow2,
						 SINT porog)
{
 register SINT i,j;
 SINT xbyte=min(xbyte1,xbyte2);
 SINT yrow=min(yrow1,yrow2);
 SINT dist;

 for(i=0,dist=0;i<yrow;i++,b1+=xbyte1,b2+=xbyte2)
  {
	//memset(btmp,0,xbyte*sizeof(ULONG));
	for(j=0;j<xbyte;j++)	   dist+=Num11[b1[j]^b2[j]];
	if(dist >= porog) return dist;

	  // ���� ������ ������ ����
	for(j=xbyte;j<xbyte1;j++) dist+=Num11[b1[j]];
	if(dist >= porog) return dist;

	  // ���� ������ ������ ����
	for(j=xbyte;j<xbyte2;j++)  dist+=Num11[b2[j]];
	if(dist >= porog) return dist;
  }

  // if yrow2 < yrow1  - ������ ������ ����
 for(i=yrow;i<yrow1;i++,b1+=xbyte1)
  {
	for(j=0;j<xbyte1;j++) dist+=Num11[b1[j]];
	if(dist >= porog) return dist;
  }

	//  ���� ������ ������ ����
 for(i=yrow;i<yrow2;i++,b2+=xbyte2)
  {
	for(j=0;j<xbyte2;j++)  dist+=Num11[b2[j]];
	if(dist >= porog) return dist;
  }

 return dist;
}
/**************************************/
SINT DistanceBitFull(BYTE *b1,SINT xbyte1,SINT yrow1,
						 BYTE  *b2,SINT xbyte2,SINT yrow2)
{
 register SINT i,j;
 SINT xbyte=min(xbyte1,xbyte2);
 SINT yrow=min(yrow1,yrow2);
 SINT dist;

 for(i=0,dist=0;i<yrow;i++,b1+=xbyte1,b2+=xbyte2)
  {
	for(j=0;j<xbyte;j++)	dist+=Num11[b1[j]^b2[j]];
	  // ���� ������ ������ ����
	for(j=xbyte;j<xbyte1;j++)  dist+=Num11[b1[j]];
	  // ���� ������ ������ ����
	for(j=xbyte;j<xbyte2;j++)  dist+=Num11[b2[j]];
  }

  // if yrow2 < yrow1  - ������ ������ ����
 for(i=yrow;i<yrow1;i++,b1+=xbyte1)
  {
	for(j=0;j<xbyte1;j++) dist+=Num11[b1[j]];
  }

	//  ���� ������ ������ ����
 for(i=yrow;i<yrow2;i++,b2+=xbyte2)
  {
	for(j=0;j<xbyte2;j++)  dist+=Num11[b2[j]];
  }

 return dist;
}
/**************************************/
// move bitmaps left-right on mov bit ( <8!)
void MoveRightBmp(BYTE *buf,SINT mov,SINT xbyte,SINT yrow)
{
 register SINT i,j;
 SINT mov1=8-mov;

 for(i=0;i<yrow;i++,buf+=xbyte)
  {
	for(j=xbyte-1;j>0;j--) buf[j]=(buf[j]>>mov) | (buf[j-1] << mov1);
	buf[0] >>=mov;
  }
}
////////////
void MoveLeftBmp(BYTE *buf,SINT mov,SINT xbyte,SINT yrow)
{
 register SINT i,j;
 SINT mov1=8-mov;

 for(i=0;i<yrow;i++,buf+=xbyte)
  {
	for(j=0;j<xbyte-1;j++) buf[j]=(buf[j]<<mov) | (buf[j+1] >> mov1);
	buf[xbyte-1] <<=mov;
  }
}
////////////
// tbuf -temporary buffer, in it - moved b1 right,left
SINT  CheckCenterSymbol(BYTE *b1,SINT xbyte,SINT yrow,
			  BYTE *b2,BYTE *tbuf,SINT xbit2,SINT yrow2,
			  SINT *sdvigx,SINT *sdvigy,SINT firdist)
{
 register SINT i;
 SINT dist,bestdist;
 SINT xbyte2=(xbit2>>3)+1;  // bytes in row
 SINT bestx=0;
 SINT besty=0;
 SINT tx;

 *sdvigx=0;
 *sdvigy=0;

 bestdist= DistanceBitFull(b1,xbyte,yrow,b2,xbyte2,yrow2);
 if(bestdist==0) return 0;
 for(tx=0;;)
 {
  // distance to original bitmap
  if(tx)
  {
	dist= DistanceBitDLL(b1,xbyte,yrow,b2,xbyte2,yrow2,bestdist);
	if(tx==1) dist+=firdist;
	if(dist < bestdist) {bestdist=dist;bestx=tx;besty=0;
				if(dist==0) break;  }
  }

  // move b2 - down (or etalon -up)
 dist= DistanceBitDLL(b1+xbyte,xbyte,(SINT)(yrow-1),b2,xbyte2,yrow2,bestdist);
 if(tx==1) dist+=firdist;
 if(dist < bestdist)
	{  // add first row
	  for(i=0;i<xbyte;i++) dist+=Num11[b1[i]];
	  if(dist < bestdist) {bestdist=dist;bestx=tx;besty=1;if(dist==0) break;}
	}

  // move b2 - up
 dist= DistanceBitDLL(b1,xbyte,yrow,b2+xbyte2,xbyte2,(SINT)(yrow2-1),bestdist);
 if(tx==1) dist+=firdist;
 if(dist < bestdist)
	{ for(i=0;i<xbyte;i++) dist+=Num11[b2[i]];
	  if(dist < bestdist) {bestdist=dist;bestx=tx;besty=-1;if(dist==0) break;}
	}

  if(tx==0)
  {
   b1=tbuf;
   tx=-1;
  }
  else
  {
   if(tx!=-1) break;
   tx=1;
   if(firdist >= bestdist) break;
   b1+=xbyte*yrow;
  }
 } // end tx

 *sdvigx=bestx;
 *sdvigy=besty;
 return bestdist;
}
///////////////
// move left/right on 1 etalon
// return - summa 1 im first column
SINT MakeMoved(BYTE *etalon,SINT xbyte,SINT yrow,BYTE *tmpbuf)
{
SINT i,j;

  MEMCPY(tmpbuf,etalon,xbyte*yrow);
  MoveRightBmp(tmpbuf,1,xbyte,yrow);

  tmpbuf+=xbyte*yrow;
  MEMCPY(tmpbuf,etalon,xbyte*yrow);
  MoveLeftBmp(tmpbuf,1,xbyte,yrow);

   // calc 1-s in first column
  for(i=0,j=0;i<yrow;i++,etalon+=xbyte) if(*etalon & 128)j++;
  return j;
}
////////////////
