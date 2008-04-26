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

// must accord #define _USE_DETOUCH_ in p2_proc !!!
//#define _USE_DETOUCH_

 #include <stdlib.h>
 #include <sys/stat.h>
 /*#include <io.h>*/

 #include "nt_types.h"
 #include <stdio.h>
 #include <fcntl.h>
/* #include <direct.h>*/
 #include <string.h>

#include "cstr.h" // OLEG
#include "globus.h"
#include "alphabet.h"
#include "p2libr.h"
#include "leo.h"
#include "lang_def.h"
#include "ccom.h"
//#include "struct.h" 
#include "fon.h" 
#include "std.h" 

#include "p2.h"
#include "rstr_p2.h"
////////////
extern P2GLOBALS p2globals;
// ���� language
#include "ligas.h"				// 01.06.2001 E.P.

////////////////
Bool32 p2_StoreVersions(CSTR_rast rast,RecVersions *rver)
{
INT i, ret=0;
UniVersions cver,*ver;
Word8 let;
INT lang=p2globals.language;

if( lang==LANG_ENGLISH && p2globals.multy_language )
    lang    = LANG_RUSENG;

 if(!rast) return FALSE;
 ver=&cver;
 memset(ver,0,sizeof(UniVersions));
 ver->lnAltCnt = MIN(REC_MAX_VERS,rver->lnAltCnt);
 ver->lnAltMax = REC_MAX_VERS;

 for(i=0;i<ver->lnAltCnt;i++)
      {
      let = rver->Alt[i].Code;
      //strcpy(ver->Alt[i].Code , decode_ASCII_to_[let]);
	  RSTR_p2_DecodeCode(ver->Alt[i].Code,let);
      ver->Alt[i].Liga      =  let;
      ver->Alt[i].Prob      =  rver->Alt[i].Prob;
      ver->Alt[i].Method    =  rver->Alt[i].Method;
      //ver->Alt[i].Charset   =  CodePages[lang]; // Oleg
	  ver->Alt[i].Charset = RSTR_p2_GetCodePage(lang);
      ver->Alt[i].Info      =  rver->Alt[i].Info; 
      }

 return CSTR_StoreCollectionUni(rast,ver);
}
/////////////////

static void StoreOneInterval( Word8 *raster, int b, int e)
{
int i;
Word8 mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

if(b < 0) b=0;
for(i=b;i<e;i++)
  {
  raster[ i>>3 ] |=  mask[ i&7 ];
  }

return;
}
////////////
static Bool32 Lines2Raster(CCOM_lnhead *linerep, Int16 size, 
                      Int16 w, Int16 h, 
                      RecRaster *rec)
{
 int            ww, len, i;
 CCOM_lnhead    * line;
 CCOM_interval  * inter;

 if( !w || !h || w > rec->lnPixWidth || h > rec->lnPixHeight )
  return FALSE;

 ww = REC_GW_WORD8(rec->lnPixWidth);

 for(line=linerep,len=0; len<size && line->lth; len+=line->lth,line=(CCOM_lnhead *)((int)line+line->lth))
  {
   Word8 *buf=&rec->Raster[ line->row*ww ];
   for(inter = (CCOM_interval*)(line+1), i=0; i<line->h; i++, inter++,buf+=ww)
    StoreOneInterval( buf, inter->e-inter->l, MIN(w,inter->e));
  }

return TRUE;
}
///////////////
// �������� �����, �������� ������, �� �������� ����������
// 
// Bool32 p2_Line2Raster(c_comp *comp, RecRaster *rec)
//   lp = (Word8 *)(comp+1);
//   lt = *(Int16*)lp;
//   w = comp->w
//   h = comp->h
P2_FUNC(Bool32) p2_Comp2Raster(Int16 lt,Word8 *lp,Int16 w,Int16 h,
					  RecRaster *rec)
{
//Int16  w, h;
//Word8  *lp;
//Int16  *lt;
Bool32 ret;

// if( !comp || !rec )
//    return FALSE;

 rec->lnPixWidth  = w;
 rec->lnPixHeight = h;
 rec->lnRasterBufSize=REC_MAX_RASTER_SIZE;

// if( comp->scale )
//    {
//    rec->lnPixWidth  >>= comp->scale;
//    rec->lnPixHeight >>= comp->scale;    
//    }

  if( rec->lnPixWidth  <= 0 ||
     rec->lnPixHeight <= 0 )
         return FALSE;

  memset( rec->Raster, 0 , REC_GW_WORD8(rec->lnPixWidth)*rec->lnPixHeight);

//  lp = (Word8 *)(comp+1);
//  lt = *(Int16*)lp;
// 
  w=(Int16)rec->lnPixWidth;
  h=(Int16)rec->lnPixHeight;

//  do  { // comps cycle - in CCOM_GetRaster if numcomp>1
//          if( (*lt) <= 2 ) break;
        ret = Lines2Raster((CCOM_lnhead*)&lp[2],(Int16)(lt-2), w, h ,rec);
//      lp += *lt;
//      lt  = (Int16*)lp;
//       }
//  while( ret ); 

  return ret;
}
////////////
static int fir1[256]=
{8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
///////////
static int las1[256]=
{8,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,

7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0} ;

//////////////////////         
///////////////////////////////////
static void MoveWindowRow0(BYTE *outrow,BYTE *inrow,int SizeByte,int fir)
{
          memcpy(outrow,inrow,SizeByte);
}
//////////
static void MoveWindowRow2(BYTE *outrow,BYTE *inrow,int SizeByte,int fir)
{
 int i;
  switch(fir)
  {
   case 1:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<1)|(inrow[i+1]>>7);
        break;
   case 2:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<2)|(inrow[i+1]>>6);
        break;
   case 3:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<3)|(inrow[i+1]>>5);
        break;
   case 4:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<4)|(inrow[i+1]>>4);
        break;
   case 5:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<5)|(inrow[i+1]>>3);
        break;
   case 6:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<6)|(inrow[i+1]>>2);
        break;
   case 7:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<7)|(inrow[i+1]>>1);
        break;
   default:return;
  }

//  outrow[SizeByte-1] |=       (BYTE)tiffWindow.maska;
}
///////////////
void MoveWindowRow1(BYTE *outrow,BYTE *inrow,int SizeByte,int fir)
{
 int i;
  SizeByte--;
  switch(fir)
  {
   case 1:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<1)|(inrow[i+1]>>7);
        outrow[SizeByte]=inrow[SizeByte]<<1;
        break;
   case 2:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<2)|(inrow[i+1]>>6);
        outrow[SizeByte]=inrow[SizeByte]<<2;
        break;
   case 3:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<3)|(inrow[i+1]>>5);
        outrow[SizeByte]=inrow[SizeByte]<<3;
        break;
   case 4:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<4)|(inrow[i+1]>>4);
        outrow[SizeByte]=inrow[SizeByte]<<4;
        break;
   case 5:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<5)|(inrow[i+1]>>3);
        outrow[SizeByte]=inrow[SizeByte]<<5;
        break;
   case 6:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<6)|(inrow[i+1]>>2);
        outrow[SizeByte]=inrow[SizeByte]<<6;
        break;
   case 7:
        for(i=0;i<SizeByte;i++)
         outrow[i]=(inrow[i]<<7)|(inrow[i+1]>>1);
        outrow[SizeByte]=inrow[SizeByte]<<7;
        break;
   default:return;
  }

//  outrow[SizeByte] |= (BYTE)tiffWindow.maska;
}
///////////////
static void (*MoveWindowRow)(BYTE *orow,BYTE *irow,int SizeByte,int fir);
static Word8 tmpRaster[REC_MAX_RASTER_SIZE];
/////////////////
int p2_rotateRecRaster(RecRaster *rec,int ninc)
{
  int xbyte8 = REC_GW_WORD8(rec->lnPixWidth);
  int xbyte  = (rec->lnPixWidth+7)>>3;
  int yrow   = rec->lnPixHeight;
  int i,j,k;
  Word8 *tmpBuf;
  Word8 *tmpRas;
  int outByte;
  int firCol,lasCol;
  int max_shift,outXbit,outXbyte;

  if( ninc == 0 ) 
          return 1;

  //rec->lnPixWidth=erect_raster_value(tmpRaster,(INT)rec->lnPixWidth,(INT)yrow,(INT)ninc);  

  max_shift=((long)(yrow-1)*ninc)/2048;
  if( max_shift < 0 )
          max_shift = -max_shift;

  if( max_shift < 1 )
          return 1;
            

  outXbit = rec->lnPixWidth + max_shift;
  outXbyte=(outXbit+7)>>3;

  memset (tmpRaster, 0, outXbyte*yrow); 

        {
        int s1,s2,c;
        Word8 *rr;

        for (tmpRas=tmpRaster,tmpBuf=rec->Raster,i=0; i < yrow ; 
              i++, tmpRas+=outXbyte,  tmpBuf+=xbyte8 ) 
        {
                if( ninc < 0)
                        c=((long)(i+1-yrow)*ninc)/2048;
                else
                        c=max_shift- (((long)(yrow-1-i)*ninc)/2048);

        rr = tmpRas + (c>>3) ; 
                s1 = c&7;
                s2 = 8 - s1;

                rr[0]=(tmpBuf[0]>>s1);      // first
                for( j=1; j<xbyte; j++) 
                        rr[j] = (tmpBuf[j-1]<<s2) | (tmpBuf[j]>>s1);
            
        if( outXbyte > xbyte )
            rr[j]=tmpBuf[j-1]<<s2;
         }

        }

//  rec->lnPixWidth=erect_raster_value(tmpRaster,(INT)rec->lnPixWidth,(INT)yrow,(INT)ninc);  

// ����� ��������� ������� !
  for(i=0,firCol=outXbit;i<outXbyte;i++)
  {
          tmpBuf=tmpRaster+i;
          for(j=0;j<yrow;j++,tmpBuf+=outXbyte)
                  if( *tmpBuf )
                  {
                          k=(i<<3)+fir1[*tmpBuf];
                          if( k < firCol)
                                  firCol=k;
                  }
     if(firCol < outXbit ) break;
  }

  for(i=outXbyte-1,lasCol=0;i>=0;i--)
  {
          tmpBuf=tmpRaster+i;
          for(j=0;j<yrow;j++,tmpBuf+=outXbyte)
                  if( *tmpBuf)
                  {
                          k=(i<<3)+8-las1[*tmpBuf];
                          if( k > lasCol)
                                  lasCol=k;
                  }
     if(lasCol > 0) break;
  }

  // ����� �������� ���������� ���� ?
  if( firCol >= lasCol )
     return 0;

  rec->lnPixWidth = lasCol-firCol;
  outByte=(rec->lnPixWidth+7)>>3;
  xbyte8 = REC_GW_WORD8(rec->lnPixWidth);

  tmpBuf=tmpRaster+(firCol>>3);
  tmpRas=rec->Raster;
  memset(tmpRas,0,xbyte8*yrow);


  if( (firCol&7) == 0) MoveWindowRow=MoveWindowRow0;
  else if( ((lasCol-1)&7) >= ((lasCol-1-firCol)&7) )
           MoveWindowRow=MoveWindowRow1;
  else MoveWindowRow=MoveWindowRow2;

  firCol&=7;
  for (i =0; i < yrow; i++, tmpBuf+=outXbyte,tmpRas+=xbyte8)
    MoveWindowRow(tmpRas,tmpBuf,outByte,firCol);
 
  return 1;
}
///////////////
void p2_TextWord(CSTR_rast  c,CSTR_rast stop, char *intxt,BOOL ansi)
{
        CSTR_rast_attr attr;
        UniVersions     vers;
        char *txt=intxt;

        for(*txt='\0'; c && c!=stop; c=CSTR_GetNextRaster (c,CSTR_f_all))
    {
    CSTR_GetAttr(c, &attr);
    if( !(attr.flg & (CSTR_f_let|CSTR_f_punct|CSTR_f_bad|CSTR_f_space)) )
        continue;
    CSTR_GetCollectionUni(c, &vers);
    if( !vers.lnAltCnt )
                strcat(txt,"~");
    else
                strcat(txt,vers.Alt[0].Code);
    }

		
    for(txt=intxt;*txt;txt++)
         *txt=stdAnsiToAscii(*txt);

}
//////////////////
void p2_FillTxt(CSTR_line cc,char *intxt,BOOL ansi)
{
        CSTR_rast first=CSTR_GetFirstRaster(cc);
        CSTR_rast last=CSTR_GetLastRaster(cc);
        if(!first) return;
    p2_TextWord(CSTR_GetNext(first),last,intxt,ansi);   
}
//////////////////////////////
Int32 p2_TextProb(CSTR_line cc,CSTR_rast  first,CSTR_rast last, char *intxt,int maxTxt)
{
        CSTR_rast_attr  attr;
        UniVersions     vers;
        CSTR_rast       c;
        char            *txt=intxt;

  if( cc )
        {
          first=CSTR_GetNext( CSTR_GetFirstRaster(cc));
          last=CSTR_GetLastRaster(cc);
        }

  for(c=first,*txt='\0'; c && c!=last; c=CSTR_GetNextRaster (c,CSTR_f_all))
  {
    CSTR_GetAttr(c, &attr);
    if( !(attr.flg & (CSTR_f_let|CSTR_f_punct|CSTR_f_bad|CSTR_f_space)) )
        continue;
    CSTR_GetCollectionUni(c, &vers);
    if( !vers.lnAltCnt )
                strcat(txt,"~(0)");
    else
        {
                strcat(txt,vers.Alt[0].Code);
                sprintf(txt+strlen(txt),"(%d)",vers.Alt[0].Prob);
        }

        if( (int)strlen(txt) >= maxTxt) 
                break;
  }

//      if(ansi)
        {
            for(txt=intxt;*txt;txt++)
                 *txt=stdAnsiToAscii(*txt);
        }

  return strlen(intxt);
}
//////////////////
static Word32 oddEvenFlag=CSTR_fn_val2odd;
Int32 p2_setOddEvenFlag(CSTR_rast first,CSTR_rast last)
{
  int numCell;
  CSTR_rast curr;
  CSTR_rast_attr cur;

  for (numCell=0,curr=first; curr&&curr!=last; curr=CSTR_GetNextRaster (curr, CSTR_f_all))
  {
    CSTR_GetAttr(curr,&cur);
    if(! ( cur.flg & CSTR_f_let) )
                continue;
        numCell++;
        cur.flg_new |= oddEvenFlag;
        CSTR_SetAttr(curr,&cur);
  }

  if( numCell <= 0)
          return 0;

  if( oddEvenFlag == CSTR_fn_val2odd)
          oddEvenFlag = CSTR_fn_val2even;
  else
          oddEvenFlag = CSTR_fn_val2odd;

  return numCell;
}
////////////////
/* Function returns UPPER CASE variant of the letter.             */
BYTE p2_to_upperASCII( BYTE c )
{
  if ( c >= (BYTE)'a' && c <= (BYTE)'z') return c - (BYTE)'a' + (BYTE)'A';
  if(p2globals.language==LANG_RUSSIAN)
  {
     // for ASCII
    if ( c >= (BYTE)'�' && c <= (BYTE)'�') return c - (BYTE)'�' + (BYTE)'�';
    if ( c >= (BYTE)'�' && c <= (BYTE)'�') return c - (BYTE)'�' + (BYTE)'�';
  }
  return c;
}

 /* Function returns LOWER CASE variant of the letter.             */
BYTE p2_to_lowerASCII(BYTE c)
{
  if ( c >= (BYTE)'A' && c <= (BYTE)'Z') return c - (BYTE)'A'+ (BYTE)'a' ;
  if(p2globals.language==LANG_RUSSIAN)
  {
   // for ASCII
    if ( c >= (BYTE)'�' && c <= (BYTE)'�') return c - (BYTE)'�'+ (BYTE)'�' ;
    if ( c >= (BYTE)'�' && c <= (BYTE)'�') return c - (BYTE)'�'+ (BYTE)'�' ;
  }
  return c;
}
///////////////
Bool32 p2_is_lowerASCII(BYTE ch)
{

 if(p2globals.language==LANG_RUSSIAN)
 {
   // for ASCII
   if((ch >=(BYTE)'�' && ch <=(BYTE)'�') ||
      (ch >=(BYTE)'�' && ch <=(BYTE)'�') 
     ) 
	 return TRUE;
 }
 if(ch >= 'a' && ch <= 'z') return TRUE;
 return FALSE;
}
/////////////////////
Bool32 p2_is_upperASCII(BYTE ch)
{
 if(p2globals.language==LANG_RUSSIAN)
 {
      if(ch >=(BYTE)'�' && ch <=(BYTE)'�')
          return 1;
 }
 if(ch >= 'A' && ch <= 'Z') return 1;
 return 0;
}
//////////////////
static Word8 rus_alias  []="��⡂8";  // "�����8"
static Word8 eng_alias  []="rnr68B";
/////////////
Word8    p2_rsadd_get_alias_class(Word8 let,Word8 lang)
{
 Word8   *fa;
 if( lang==LANG_RUSSIAN )
    fa=rus_alias;
 else if( lang==LANG_ENGLISH )
    fa=eng_alias;
 else
    return 0;    

 if( strchr(fa,let) )
    return 1;
 return 0;
}
/////////////////////
