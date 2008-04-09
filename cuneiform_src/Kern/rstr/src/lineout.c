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


/********************************************************************/
/*                                                                  */
/*                   Output a line to ED-file                       */
/*                                                                  */
/********************************************************************/
#include <string.h>
#include <stdio.h>
#include "cstr.h"

static Word8 language;
static Word8    ed_buffer[64000], *MED_file_bound, *MED_file_end ;

static void ed_write(Word8* p, Word16 size);

void ed_init()
 {
 
 MED_file_end=ed_buffer;
 MED_file_bound=MED_file_end+sizeof(ed_buffer);
 }

void ed_make_word(CSTR_rast b, CSTR_rast e)
{
Word8           *l,p;
CSTR_rast       c;
UniVersions     uni;
Int16           k,i,n,h,wb;
CSTR_rast_attr  a;
Int16           top,bottom,left,right;
/*
struct fragm_disk
{
Word8 code;
Word8 fragm_numb;
Word16 depth;
};

struct fragm_disk_descr
{
Word8 code;
Word16 row;                          
Word16 col;                          
Word16 height;                       
Word16 w_width;                      
Int8 type;
Word8 kegl;                          
Word8 font;                          
Word8 language;//reserv;            
Word8 type_underl;                   
};				      

struct sheet_disk_descr
{
Word8 code;
Int8 quant_fragm;
Word16 sheet_numb;
Word16 descr_lth;
Word8 byte_flag;
Word16 resolution;
Word16  incline;
Int8 tabl[13];
};
*/				      
for(top=10000,bottom=0,left=10000,right=0,c=b;c&&c!=e;c=CSTR_GetNext(c))
    {
    CSTR_GetAttr(c,&a);
    if( a.col<left )
        left = a.col;
    if( a.col+a.w>right )
        right = a.col+a.w;
    if( a.row<top )
        top = a.row;
    if( a.row+a.h>bottom )
        bottom = a.row+a.h;
    if( c==b )
        {
        language=a.language;
        }
    }   
h = bottom-top-1;
wb= (right-left-1+7)/8;
//    start sheet_disk_descr
    p   =0x0a/*SS_SHEET_DESCR*//*f.code*/; ed_write((Word8*)&p,1);
    p   =1/*f.quant_fragm*/; ed_write((Word8*)&p,1);
    n   =0/*f.sheet_numb*/;  ed_write((Word8*)&n,2);
    n   =0x26/*f.descr_lth*/;  ed_write((Word8*)&n,2);
    p   =0/*f.byte_flag*/; ed_write((Word8*)&p,1);
    n   =300/*f.resolution*/;  ed_write((Word8*)&n,2);
    n   =0/*f.incline*/;  ed_write((Word8*)&n,2);
    p   =0/*f.res1*/; ed_write((Word8*)&p,1);
    n   =0/*f.res2-3*/;  ed_write((Word8*)&n,2);
    n   =0/*f.res4-5*/;  ed_write((Word8*)&n,2);
    n   =0/*f.res6-7*/;  ed_write((Word8*)&n,2);
    n   =0/*f.res8-9*/;  ed_write((Word8*)&n,2);
    n   =0/*f.res10-11*/;  ed_write((Word8*)&n,2);
    n   =0/*f.res12-13*/;  ed_write((Word8*)&n,2); 

// start fragm_disk_descr
    p   =0x0b/*SS_FRAGMENT*//*f.code*/; ed_write((Word8*)&p,1);   
    n   =0/*f.row*/;       ed_write((Word8*)&n,2);   
    n   =0/*f.col*/;       ed_write((Word8*)&n,2);
    n   =h/*f.heigh*/;     ed_write((Word8*)&n,2);   
    n   =wb/*f.w_width*/;  ed_write((Word8*)&n,2);   
    p   =0/*FD_TYPE_TEXT*//*f.type*/; ed_write((Word8*)&p,1);   
    p   =10/*f.kegl*/;     ed_write((Word8*)&p,1);   
    p   =0/*f.font*/;      ed_write((Word8*)&p,1);   
    p   = language;        ed_write((Word8*)&p,1);   
    p   =0/*f.type_underl*/;  ed_write((Word8*)&p,1);   

 // start fragm_disk
    p   =0x0b/*SS_FRAGMENT*//*f.code*/; ed_write((Word8*)&p,1);   
    p   =0/*f.fragm_numb*/;  ed_write((Word8*)&p,1);   
    n   =0/*f.depth*/;       ed_write((Word8*)&n,2);   
 for(c=b;c&&c!=e;c=CSTR_GetNext(c))
    {
    CSTR_GetCollectionUni(c,&uni);
    if( uni.lnAltCnt && !uni.Alt[0].Code[0] )
        continue;
    CSTR_GetAttr(c,&a);
    // start bitmap ref
    p   =0/*SS_BITMAP_REF*/; ed_write((Word8*)&p,1);   
    p   =a.cpos;        ed_write((Word8*)&p,1);   
    n   =a.r_row;       ed_write((Word8*)&n,2);   
    n   =a.r_col;       ed_write((Word8*)&n,2);   
    n   =a.h;           ed_write((Word8*)&n,2);   
    n   =a.w;           ed_write((Word8*)&n,2);   
    // stop bitmap ref
    n=(Int16)uni.lnAltCnt;
    if(n>7) n=7;
    if(n<1) n=1;
    for(k=i=0;k<n;)
        {
        p=uni.Alt[i].Prob;
        if( p&1 )   p--;
        if( !p  )   p=2;    // all odd propability
        for(l = &uni.Alt[i++].Code[0];*l && k<n;l++,k++)
            { // for ligas : strlen(uni.Alt[i].Code)>1
            ed_write(l,1);   
            if( k==n-1 )
                p = p+1; // last even propability
            ed_write(&p,1);   
            }
        
        }    
  }

return;
}


//********************** ED-file management *****************************

static void ed_write(Word8* p, Word16 size)
{
if (MED_file_bound -  MED_file_end < size) 	
    {
    //ErrorExit(0);
    return;
    }
memcpy (MED_file_end, p, size); 		
MED_file_end += size;
}

static void ed_save(void)
{
FILE *fp=fopen("d:\\ed.ed","wb");
fwrite(ed_buffer,MED_file_end-ed_buffer,1,fp);
fclose(fp);
}


// dublicate with PASSE.C
#define MAX_LEN_WORD  48
static Word8 left_limit_word[] =" .";
static Word8 right_limit_word[]=" -.���";

static CSTR_rast ed_next_word(CSTR_rast cs)
{
CSTR_rast       c=cs;
CSTR_rast_attr  attr;
RecVersions     vers;

CSTR_GetAttr(c,&attr);
if( attr.flg==CSTR_f_fict && attr.col==0x7fff ) 
    return (CSTR_rast)0; // last rast
do{
  c=CSTR_GetNext(c);
  CSTR_GetAttr(c,&attr);
  CSTR_GetCollection(c,&vers);
  }while( c && memchr(left_limit_word,vers.Alt[0].Code,sizeof(left_limit_word)) &&
          !(attr.flg&CSTR_f_fict) );

return (attr.flg&CSTR_f_fict)?(CSTR_rast)0:c;
}

static CSTR_rast ed_end_word(CSTR_rast cs,Word8 *str,Word8 *word_len)
{
CSTR_rast       c=cs;
CSTR_rast_attr  attr;
Int16           i;
RecVersions     vers;

CSTR_GetCollection(c,&vers);
*str++  = vers.Alt[0].Code;
i=1;
do{
  c=CSTR_GetNext(c);
  CSTR_GetCollection(c,&vers);
  *str++  = vers.Alt[0].Code;  
  CSTR_GetAttr(c,&attr);
  i++;
  }while( c && !memchr(right_limit_word,vers.Alt[0].Code,sizeof(right_limit_word)) &&
          !(attr.flg&CSTR_f_fict) && i<MAX_LEN_WORD-1);
c=c ? c : CSTR_GetLastRaster(CSTR_GetRasterLine(cs));
if( i )
    {
    i--;
    str--;
    }
*str='\0';
*word_len = (Word8)i;
return c;
}

Bool32 ed_cstr_string(CSTR_line ln)
{
CSTR_rast       eng, enge;
Word8           elen,ewrd[MAX_LEN_WORD+40];

eng = CSTR_GetFirstRaster(ln);
while(1)
    {
    eng = ed_next_word(eng);
    if( !eng )
        break;
    enge = ed_end_word(eng,ewrd,&elen);
    ed_init();
    ed_make_word(eng,enge);
    ed_save();
    // ed spell
    // ed conv ed back to CSTR
    break; // debug
    }
return  TRUE;
}

Bool32 ed_CorrectSpeller(Int32 version)
{
Int32           n,  i;
CSTR_line       line;


n=CSTR_GetMaxNumber ();
for(i=0;i<n;i++)
    {
    line = CSTR_GetLineHandle (i, version);
    

    if( line )
        {
	    ed_cstr_string(line);	
        break; // debug
		}
    
    }
return TRUE;
}