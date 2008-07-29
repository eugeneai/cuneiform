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

/************************************************************/
/* CTB_aln.c : functions for aligne of results **************/
/************************************************************/
#include <string.h>
#include "ctb.h"

static  Word8   local_rst[REC_MAX_RASTER_SIZE];
CTB_FUNC(void) CTB_align8_lines(Word8 *bin,Int32 w, Int32 h)
{
int i,ii,iii, wb=(w+7)/8, wb_new=((w+63)/64)*8;
Word8   buf[256];

memset(buf,0,wb_new);
for(iii=(h-1)*wb_new,ii=(h-1)*wb,i=0;i<h;i++,ii-=wb,iii-=wb_new)
    {
    memcpy(buf,&bin[ii],wb);
    memcpy(&bin[iii],buf,wb_new);
    }

return;
}

CTB_FUNC(void) CTB_align1_lines(Word8 *bin,Int32 w, Int32 h)
{
int i,ii,iii, wb=((w+63)/64)*8, wb_new=(w+7)/8;
Word8   buf[256];

memset(buf,0,wb_new);
for(iii=ii=i=0;i<h;i++,ii+=wb,iii+=wb_new)
    {
    memcpy(buf,&bin[ii],wb);
    memcpy(&bin[iii],buf,wb_new);
    }

return;
}

CTB_FUNC(void) CTB_align8_124lines(Word8 *bin,Int32 w, Int32 h,
                                   Int32 alin, Word8 init)
{
int i, wb, wb_new;
Word8   buf[256];
Word8  *bout;

switch( alin )
    {
    case    1:
        wb=(w+7)/8;
        break;
    case    2:
        wb=((w+1)/2)*2;
        break;
    case    4:
        wb=((w+3)/4)*4;
        break;
    default:
        return;
    }
wb_new=((w+7)/8)*8;

memset(buf,init,wb_new);
for(bout=bin+wb_new*(h-1),bin+=wb*(h-1),i=0;i<h;i++,bin-=wb,bout-=wb_new)
    {
    memcpy(buf,     bin,    w);
    memcpy(bout,    buf,    wb_new);
    }

return;
}

// bin : B/W images align to 4 bytes
CTB_FUNC(void) CTB_align41(Word8 *sbin,Int32 w, Int32 h)
{
int i, wb_in, wb_out;
Word8   buf[256];
Word8  *bout, *bin=sbin;

wb_in=(w/32+1)*4;
wb_out=(w+7)/8;

for(bout=local_rst+wb_out*(h-1),bin+=wb_in*(h-1),i=0;i<h;i++,bin-=wb_in,bout-=wb_out)
    {
    memcpy(buf,     bin,    wb_out);
    memcpy(bout,    buf,    wb_out);
    }
memcpy( sbin, local_rst, wb_out*h);
return;
}

