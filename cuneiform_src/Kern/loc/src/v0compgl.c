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


#include "cttypes.h"
#include "struct.h"
//#include "func.h"
#include "v1comp.h"

//      Common variables


//      Internal functions
static void make_seg_line (Word8* raster, Int16 width);

//      Internal variables
static BWSS *bp,*bpe;
static Word8 extrcomp_flag;
#define SEG_DELIM -0x7000

BWSS *locomp_seglist(Word8* raster, BWSS *bwsp, BWSS *bwe, Int16 height, Int16 width)
{
 bwsp->b = 0; bwsp->w = SEG_DELIM; bwsp++;
 bp = bwsp;  bpe = bwe;extrcomp_flag = 0;
 while (height--)  { make_seg_line (raster,width); raster+=width; }
 return bp;
}

BWSS *extrcomp_seglist(Word8* raster, BWSS *bwsp, BWSS *bwe, Int16 width)
{
 bp = bwsp;  bpe = bwe; extrcomp_flag = 1;
 make_seg_line(raster,width);
 return bp;
}

static void make_seg_line(Word8* raster, Int16 width)
{
 BWSS *p = bp;
 Word8 b;
 int c,current_color,length;


 p->w = p->b = 0;
 current_color=0;

 while (width--)
 {
   if(p >= bpe) return; // bound control
   b=*(raster++);
   length=8;
   while (length>0){
     if (b>127) c=1;
     if (b<128) c=0;
     if (c==0 && current_color==1) p->w=1;
     if (c==0 && current_color==0) (p->w)++;
     if (c==1 && current_color==1) (p->b)++;
     if (c==1 && current_color==0) (++p)->b=1;
     b=(b-128*c)*2;
     current_color=c;
     length=length-1; };
};

 p->w=SEG_DELIM; bp=++p; return;};


  




void invert_tiff (Word8* p, Word16 lth)
{
 while (lth--) {*p = ~*p; p++;}
}
