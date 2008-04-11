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

#define _ONLY_FINAL_

#include "c_types.h"

#include <stdlib.h>
#include <string.h>

#include "ctb.h"
#include "sfont.h"
#include "leo.h"

#define ParolBase "ClBas"

static BYTE UseHand=0;

/////////////////
void EndCTB(CTB_handle *CTBFile)
{
	CTB_close(CTBFile);
//	CTB_done();
}
/////////////////
int StartCTB(char *outname,CTB_handle *CTBFile,Int16 countFont,
			 Word32 *fields)
{
Word8 CTBdata[CTB_DATA_SIZE];
Int16  *pint16=(Int16 *)(CTBdata+6);
Word32 *pword32=(Word32 *)(CTBdata+8);
int i;
 
 memset(CTBdata,0,CTB_DATA_SIZE);
 memcpy(&CTBdata[1],ParolBase,5);
 *pint16=countFont;
 i=min(countFont,4);
 memcpy(pword32,fields,i*NFIELDDWORD*sizeof(Word32));

 CTBdata[0]=max(8+4*NFIELDDWORD*sizeof(Word32),
	           34+NFIELDDWORD*sizeof(Word32));

 if( CTB_create_gray(outname,CTBdata) == FALSE )
   {
//    MessageBox(GetActiveWindow(),outname,"Error create CTB",MB_OK);
    return -1;
   }

 if( CTB_open(outname,CTBFile,"w") ==FALSE)
 {
//    MessageBox(GetActiveWindow(),outname,"Error open CTB",MB_OK);
    return -2;
  }

 return 1;
}
/////////////////
int SaveWeletAsCTB(welet *wel,CTB_handle *CTBFile)
{
Word8 CTBdata[CTB_DATA_SIZE];
int fullX;
int fullY;
BYTE *bufCTB;
Word16 *pword16;
Word32 *pword32;
Int16  *pint16;
static  num=0;
int i;
  

//  if( (j=write(flout,wel,sizeof(welet))) !=sizeof(welet))

    fullX= 128; //((wel->w+7)>>3)<<3;
	fullY= 64;  // wel->h;
	bufCTB=wel->raster;
/*
    allRaster=wel->raster+((WR_MAX_HEIGHT-fullY)/2)*WR_MAX_WIDTH+
	  (WR_MAX_WIDTH-fullX)/2;
    startRaster=bufCTB=wel->raster;
    for(j=0;j< fullY;j++,allRaster+=WR_MAX_WIDTH,startRaster+=fullX)
	{ for(k=0;k<fullX;k++) 
	   //startRaster[k]=255-allRaster[k]; 
	  //  startRaster[k]=allRaster[k]>0?0:1;
        startRaster[k]=allRaster[k]; 
	  //memset(startRaster+wel->w,0,fullX-wel->w);
	}
*/
	memset(CTBdata,0,CTB_DATA_SIZE);
    CTBdata[0]= CTB_OEM_CHARSET;
    CTBdata[1]= (Word8)fullX;       // 128
    CTBdata[2]= (Word8)fullY;       //  64
    CTBdata[3]= (Word8)wel->let;    // in ASCII
    // now my features
	CTBdata[4]=(Word8)wel->w;
	CTBdata[5]=(Word8)wel->h;
	CTBdata[6]=(Word8)wel->weight;  // how many symbols make 
	CTBdata[7]=(Word8)wel->porog;   // threshold 
	CTBdata[8]=(Word8)wel->mw;      // medium width
	CTBdata[9]=(Word8)wel->mh;      //        height
    CTBdata[10]=(Word8)wel->prob;   // for CTB - probability  
	CTBdata[11]=(Word8)wel->attr;   // for attributes

	// now put words
    pword16=(Word16 *)(CTBdata+12);
	pword16[0]=wel->fill;
	pword16[1]=wel->num;
	pword16[2]=wel->invalid;

	CTBdata[18]=wel->valid;  // for CTB - validity  
    CTBdata[19]=wel->kegl;
	
	// now short int's
	pint16=(Int16 *)(CTBdata+20);
	pint16[0]=wel->sr_col;
	pint16[1]=wel->sr_row;
    
	// now dword
	pword32=(Word32 *)(CTBdata+24);
	pword32[0]=wel->summa;

	for(i=0;i<NFIELDDWORD;i++)
	 pword32[1+i]=wel->fields[i];

	pint16=(Int16 *)(CTBdata+28+NFIELDDWORD*sizeof(Word32));
	pint16[0]=wel->nInCTB;

	pword32=(Word32 *)(pint16+1);
    pword32[0]=wel->tablColumn;

   if( CTB_write(CTBFile,-1,bufCTB,CTBdata) == FALSE )
//    PutMyMessage(NULL,CTB_get_error(),"CTB error write raster!"); 
        return 0;
num++;
 return 1;
}
////////////////////
//
//   input from b/w ctb-base
//
////////////////////// 
static CTB_handle CTBfileBW;
static Word8 CTBima[((BASE_MAX_W+7)/8)*(BASE_MAX_H+1)];
static Word8 CTBdata[max(CTB_DATA_SIZE,36)];

void CloseBase(void)
{ 
	 	CTB_close(&CTBfileBW);
		return;
}
//////////////////////
int OpenBase(char *bas) 
{ 

  if( !CTB_open(bas,&CTBfileBW,"w") )
	  return -2;

 // grey file ?
  if( CTBfileBW.signums & CTB_GRAY  )
  {
	 CTB_close(&CTBfileBW);
//	 MessageBox(GetActiveWindow(),name,"Grey base!",MB_OK);
	 return -3;
  }

  return CTB_volume(&CTBfileBW);
}
///////////////
int GetSymbolFromBase(int i,Nraster_header *rh,BYTE **pBuf)
{
Int16 *pint16;
 
 memset(rh,0,sizeof(Nraster_header));

 if( !CTB_read(&CTBfileBW,i,CTBima,CTBdata ) ) 
	 return 0;

 if( CTBdata[5] == 0  && !UseHand ) 
	 return 0; // not printed symbol

#ifdef _ONLY_FINAL_
  if( ( CTBdata[15] & LEO_VALID_FINAL ) ==0 ) 
	  return 0;  // no in final 
#endif

 rh->w  =CTBdata[1];   //result_struct.dx;
 rh->h  =CTBdata[2];   //result_struct.dy;
 rh->let=CTBdata[3]; //result_struct.let;
 rh->solid=1;

 pint16=(Int16 *)(CTBdata+6);
 rh->sr_col=pint16[0];
 rh->sr_row=pint16[1];

 rh->prob =CTBdata[14];   // probability
 rh->valid=CTBdata[15];   // validity

 rh->nInCTB=i+1;     // count from 1 !
 rh->nField=CTBdata[25];   // which field 

 if( CTBdata[5] & CTB_PRINT_ITALIC )
	 rh->italic=1;
 if( CTBdata[5] & CTB_PRINT_BOLD )
	 rh->bold=1;
 if( CTBdata[5] & CTB_PRINT_SERIFIC )
	 rh->serif=1;
 if( CTBdata[5] & CTB_PRINT_GELV )
	 rh->gelv=1;
 if( CTBdata[5] & CTB_PRINT_NARROW )
	 rh->narrow=1;

 rh->kegl=CTBdata[34];        // 25.10.2000 - accord Oleg ! rstr_con_store
 rh->tablColumn=CTBdata[35];  // were - [32],[33] !!!
 *pBuf=&CTBima[0];
 return 1;
}
/////////////////////////
BYTE SetHand(BYTE val)
{
	UseHand = val;
	return UseHand;
}
////////
