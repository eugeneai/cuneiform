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

#ifndef H_ccomdef_h
#define H_ccomdef_h

#include "Recdefs.h"
#pragma pack (push,8)

#define CCOM_VERSION_CODE   1
#define CCOM_DUST_SIZE      8
//-------------------- user blocks      --------------------------
struct _USER_BLOCK
{
Word32  code;
Int32   size;
Word8 * data;
struct _USER_BLOCK * next_block;
};
typedef struct _USER_BLOCK CCOM_USER_BLOCK;
#define CCOM_UB_DENSITY     1
#define CCOM_UB_BEGENDS     2
#define CCOM_UB_CAPDROPLN   3
#define CCOM_UB_MERGEFRAME  4
#define CCOM_UB_SIZELINEREP 5
//-------------------- component in kit --------------------------

struct _CCOM_comp
 {
 Int16 upper;                   // upper boundary of component
 Int16 left;                    // left boundary of component
 Int16 h;                       // height of component
 Int16 w;                       // width of component
// 8
 Word8 rw;                      // raster width in bytes
 Word8 type;                    // recognition type :
#define CCOM_CH_PERFECT    1      // perfect type defined
#define CCOM_CH_LETTER     2      // letter type
#define CCOM_CH_DUST       4      // dust type
#define CCOM_CH_PUNCT      8      // punctuation
#define CCOM_CH_STICK     16      // vertical bar component
#define CCOM_CH_GREAT     32      // great component
#define CCOM_CH_MERGE     64      // merged components
#define CCOM_CH_NOTLTR   128      // not letter or punctuation 
 Int16 nl;                      // number of lines
 Int16        size_linerep;     // sizeof to line representation
 Word8  *     linerep;          // linear (inteval) representation 
 Word8 begs;                    // number of free begins
// 16
 Word8 ends;                    // number of free ends
 Word8 large;                   // large type :
#define CCOM_LR_UNDERLINED  1   // component was underlined
#define CCOM_LR_TAKEN       2   // taken to line at dust_ini
#define CCOM_LR_LINEREP     4   // store line representation
#define CCOM_LR_KILLED      8   // killed component
 Word8 scale;                   // scale of the component
#define CCOM_LONGLINES      128 // int16 end, int16 len
 Word8  cs;                     // respond from events
 Word8 pidx;            // proportional index (ref.)            *
 Word8 reasno;           // proportional criteria messages
 Int16 numcomp;
 CCOM_USER_BLOCK   * user_block ; // user information
// 24
#define CCOM_USER_NO    0
 struct _CCOM_comp * next_comp; // goto next comp from the global list 
 RecVersions  *vers;             // recognition collection
// 32
 };
typedef struct _CCOM_comp CCOM_comp;

//-------------------- linear (interval) representation ----------------------

//	At the beginning of line representation - word of total length -
//	not use it, simply skip
//	At end of each line zero byte as mark of line end
//	After last line zero word

//	line header
typedef struct _lnhead
 {
 Int16 lth; // length of one line representation
 Int16 h;   // height of line
 Int16 row; // relative row of line start
 Word16 flg;  // flags of free beg and free end
#define CCOM_l_fbeg     0x20
#define CCOM_l_fend     0x80
#define CCOM_l_cbeg     0x02
#define CCOM_l_cend     0x08
 } CCOM_lnhead;
typedef struct _lnhead CCOM_linerep; // alias

//	one interval
typedef struct _interval
 {
 Word8 l;  // length of interval
 Word8 e;  // end of interval coordinates
 } CCOM_interval;

 typedef struct _interval16
 {
 Word16 l;  // length of interval
 Word16 e;  // end of interval coordinates
 } CCOM_interval16;

typedef struct _CCOM_cont
    {
    CCOM_comp           *   first;
    CCOM_comp           *   last;
    struct _CCOM_cont   *   next;
    struct _CCOM_cont   *   prev;
    Int32                   nall,nsmall[8];
    Bool16                kill_dust_mode,language,style_new;
    } CCOM_cont;

typedef Int32  CCOM_handle;
#pragma pack (pop)
#endif


