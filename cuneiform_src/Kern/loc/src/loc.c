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

#include <math.h>
#include <string.h>
#include <fcntl.h>
/*#include <io.h>*/
#include <stdio.h>
#include <stdlib.h>
#include "loc.h"
#include "struct.h"

#ifdef PPS_MAC
#include <unix.h>
#else
#include <sys/stat.h>
#endif


//-------------- FROM DIF.DLL


static evn_error_code=ER_LOC_NO_ERROR;
char alphabet[256];
Word8   language;
Bool32  enable_save_stat=FALSE;
Word8   save_event_txt[36],save_eventr_txt[36];
Word8   save_event_txts[80],save_eventr_txts[80];
Word8 *events_treeh=NULL, *events_tree_rth=NULL;  // event tables hnd
Word8 *events_treep=NULL, *events_tree_rtp=NULL;  // event tables prn
Word8 *events_tree=NULL,  *events_tree_rt=NULL;  // event tables
Word8 ev_rt_num_ln,ev_num_ln;
extern c_comp wcomp;         // working component structure
extern version* start_rec;   // ptr to answer
extern Word8 lpool[];
extern Word8 evline[], evline1[];

extern MN * c_locomp (Word8* raster, Int32 bw, Int32 h, Int16 upper, Int16 left);
extern void MN_to_line(MN *);
extern Int32 recog_letter(void);
extern Int32 recog_letter_lp(ExtComponent *ec, Word8 *lp,Word16 lth);


#ifndef PPS_MAC
static void *EvnAlloc(Word32 len) { return malloc(len); }
static void  EvnFree(void *ptr,Word32 len) { free(ptr); }
static Int32 GetFileLength(Int32 handle) { return filelength(handle);}
#else
static void *EvnAlloc(Word32 len) { return NewPtr(len); }
static void  EvnFree(void *ptr,Word32 len) { DisposPtr(ptr); }
static Int32 GetFileLength(Int32 handle) {return filelength_n(handle);}
#endif

static void* (*my_alloc)(Word32 len)=EvnAlloc;
static void  (*my_free)(void *ptr,Word32 len)=EvnFree;






LOC_FUNC(Bool32)  LOCInit( MemFunc* mem )
{
return TRUE;
}



LOC_FUNC(void)  LOCDone(void)
{

return ;
}

LOC_FUNC(Int16) LOCGetErr(void)
{
return evn_error_code;
}



Word8 evn_multy_lpool[6000+2];


LOC_FUNC(MN *) LOC_CLocomp (Word8* raster, Int32 bw, Int32 h, Int16 upper, Int16 left)
{
  return c_locomp (raster,bw,h,upper,left);
}
extern Word8* segment_pool;

LOC_FUNC(Word8*) LOC_GetSegmentPool(void)
{
return segment_pool;
}
