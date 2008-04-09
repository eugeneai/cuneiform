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
#include <direct.h>

#include "leo.h"
#include "std.h"
#include "ctb.h"
#include "tuner.h"

extern Int16 line_number;
extern char  local_grey_ctb[];
extern char  local_ctb_name[];
static CTB_handle   this_ctb={0};
static int  datalen = 38; 

static CTB_handle   this_ctb1={0};
static int  datalen1 = 38; 

Int16 rstr_cont_store(RecRaster *r,Word8 let, Word8 nLns,Rect16 *rect,Word8 IsPrint,
		Word8	Prob, Word8 Valid, RecVersions *v,Word8 control,
        Word8   kegl,Word8 column, Word8 tabno)
{
Int32       num;
Word8       raster[4096],data[CTB_DATA_SIZE]={0};
Int32       wb, k;
Bool32      ret;
RecVersions ver;

if( !this_ctb.bas ) // || !cont_name[0] )
    return 0;
data[0]= CTB_OEM_CHARSET;
data[1] = (Word8)r->lnPixWidth;
data[2] = (Word8)r->lnPixHeight;
data[3] = let; //stdAnsiToAscii(let);
data[4] = 0;
data[31] = nLns;
data[32] = 0;
data[5] = IsPrint;
memcpy(&data[6],rect,sizeof(Rect16));
data[14] = Prob;
data[15] = Valid;

if( v )
    {
    ver=*v;
    if( ver.lnAltCnt>4 )
        ver.lnAltCnt=4;
    data[16]=(Word8)ver.lnAltCnt;
    for(k=0;k<ver.lnAltCnt;k++)
        {
        data[17+k*2]= stdAnsiToAscii(ver.Alt[k].Code);
        data[18+k*2]= ver.Alt[k].Prob;
		data[28+k]  = ver.Alt[k].Method;
        }
    }
data[25] = (Word8)line_number; // !!! can be great than 255
data[26] = 0;//leo_current_alpha_ndx;
data[27] = control;

if( datalen>34 )
    data[34]=kegl;
if( datalen>35 )    
    data[35]=column;
if( datalen>36 )    
    data[36]=tabno;
wb = ((r->lnPixWidth+63)/64)*8;
memcpy( raster, r->Raster, wb*r->lnPixHeight);
#ifdef _USE_CTB_
CTB_align1_lines(raster, r->lnPixWidth, r->lnPixHeight);
ret = CTB_write( &this_ctb, -1, raster,  data);
if( !ret )
    return -1;
num = this_ctb.num;

return (Int16)num;  // id_rast = last sequentaly saved raster+1
#else
ret=-1;
num=-1;
return -1;
#endif
}

void rstr_close_cont(void)
{
if( this_ctb.bas )
    {
#ifdef _USE_CTB_
    CTB_close(&this_ctb);
#endif
    memset(&this_ctb,0,sizeof(this_ctb));
    }
return;
}

Bool32 rstr_open_cont(void)
{
#ifdef _USE_CTB_
Word8   data[CTB_DATA_SIZE]={0};
rstr_close_cont();
data[0]=38;
if( !CTB_create(local_ctb_name,data) || !CTB_open(local_ctb_name,&this_ctb,"w") )
    {
    _mkdir(".\\TMP");
    if( !CTB_create(local_ctb_name,data) || !CTB_open(local_ctb_name,&this_ctb,"w") )
        return FALSE;
    }

CTB_read_global_data(&this_ctb,data);

datalen = data[0];
return TRUE;
#else
return FALSE;
#endif
}

// save base for spell learning
Bool32 rstr_open_cont1(void)
{
#ifdef _USE_CTB_
Word8   data[CTB_DATA_SIZE]={0};
static  int init=1;
if( init )
    {
    init=0;
    data[0]=38+12*3+1;
    if( !CTB_create("d:\\vers",data) || !CTB_open("d:\\vers",&this_ctb1,"w") )
        return FALSE;
    CTB_read_global_data(&this_ctb1,data);
    datalen1 = data[0];
    }
return TRUE;
#else
return FALSE;
#endif
}

Int16 rstr_cont_store1(RecRaster *r,Word8 let, Word8 nLns,Rect16 *rect,Word8 IsPrint,
		Word8	Prob, Word8 Valid, RecVersions *v,Word8 control,
        Word8   kegl)
{
Int32       num;
Word8       raster[4096],data[CTB_DATA_SIZE]={0};
Int32       wb, k;
Bool32      ret;
RecVersions ver;

if( !this_ctb1.bas ) // || !cont_name[0] )
    return 0;
data[0]= CTB_OEM_CHARSET;
data[1] = (Word8)r->lnPixWidth;
data[2] = (Word8)r->lnPixHeight;
data[3] = let; //stdAnsiToAscii(let);
data[4] = 0;
data[31] = nLns;
data[32] = 0;
data[5] = IsPrint;
memcpy(&data[6],rect,sizeof(Rect16));
data[14] = Prob;
data[15] = Valid;

if( v )
    {
    ver=*v;
    data[16]=(Word8)ver.lnAltCnt;
    if( data[16]>4 )
        data[16]=4;
    
    for(k=0;k<data[16];k++)
        {
        data[17+k*2]= stdAnsiToAscii(ver.Alt[k].Code);
        data[18+k*2]= ver.Alt[k].Prob;
		data[28+k]  = ver.Alt[k].Method;
        }
    }
data[25] = (Word8)line_number; // !!! can be great than 255
data[26] = 0;//leo_current_alpha_ndx;
data[27] = control;

if( datalen1>34 )
    data[34]=kegl;
if( datalen1>38 && ver.lnAltCnt>4 )
    {
    data[16]=(Word8)ver.lnAltCnt;
    for(k=4;k<data[16];k++)
        {
        data[38+k*3]= stdAnsiToAscii(ver.Alt[k].Code);
        data[39+k*3]= ver.Alt[k].Prob;
		data[40+k*3]= ver.Alt[k].Method;
        }
    }

wb = ((r->lnPixWidth+63)/64)*8;
memcpy( raster, r->Raster, wb*r->lnPixHeight);
#ifdef _USE_CTB_
CTB_align1_lines(raster, r->lnPixWidth, r->lnPixHeight);
ret = CTB_write( &this_ctb1, -1, raster,  data);
if( !ret )
    return -1;
num = this_ctb1.num;

return (Int16)num;  // id_rast = last sequentaly saved raster+1
#else
ret=-1;
num=-1;
return -1;
#endif
}


void rstr_close_cont1(void)
{
#ifdef _USE_CTB_
if( this_ctb1.bas )
    {
    CTB_close(&this_ctb1);
    memset(&this_ctb1,0,sizeof(this_ctb));
    }
#endif
return;
}