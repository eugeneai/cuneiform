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

#include <stdio.h>
#include <string.h>
#include "globus.h"
#include "struct.h"
#include "v1comp.h"
#include "msgerr.h"

extern  Word8   fax1x2;
extern  Int32   box_number;
//------------------------ Common working fields

extern Word8 double_fax;
extern Word8 image_disp_mask;
extern Word16 image_disp_end;
extern Word16 image_disp_byte;

extern Int16 image_blth    ;  // pixels per line
extern Int16  image_height  ;  // lines in file number
extern Int16 image_lth     ;  // bytes per line
extern Word8 image_black   ;  // mask for black pixels adding
extern Word8 image_white   ;  // mask for wite pixels adding
extern struct main_memory_str Q;

void analise();
BWS *extrcomp_seglist(Word8* raster, BWS *bwsp, BWS *bwe, Int16 width);
Word32 progress_set_percent (Word32 volume);
Int16 source_read(Word8* start, Word8* ptr, Word8* end);

//---------------------- Internal working fields
// TGCV static LONG progress_next;

//--------------------- Internal functions
static void enough_memory();
static void initdsect();
static void allocboxes();
static void begin();
static Word16 readline();
static void exchangelines();
static void fax_double();
static Int16 fax_test();
static void emptyline();
/*
static MN   * Cmnstart;
static BWS  * Cline1;
static BWS  * Cline2;
static Word8 * Cscan;*/
/*
comp_mem_alloc()
{
  Cmnstart = malloc ( sizeof (MN)  * SEG_MAX_NUM);
  Cline1   = malloc ( sizeof (BWS) * SEG_MAX_NUM);
  Cline2   = malloc ( sizeof (BWS) * SEG_MAX_NUM);
  Cscan    = malloc (0x4000 + LINE_MAX_LTH);
}
  */

//========================== Extract components pass ====================

void extrcomp()
{
 // TGCV prop_init();
 // TGCV rules_open();
 // TGCV sweeper_ini();
 // TGCV progress_next = progress_set_step (image_height + 1);
 initdsect();
 //enough_memory();
 allocboxes();
 // TGCV save_comp_ini();
 double_fax = fax1x2;
 begin();

 if (double_fax)
  {
fax_loop:
   Q.lineno++;
   if (!readline()) goto lastline;
   analise();
   Q.lineno++;
   if (!readline()) { fax_double(); analise(); goto lastline; }
   if (!fax_test()) error_exit (ERR_comp,14);   // not a fax image
   analise();
// TGCV    if (Q.lineno >= progress_next)
   progress_set_percent (Q.lineno);
   goto fax_loop;
  }

main_loop:
 Q.lineno++;
 if (readline())
  {
   analise();
 // TGCV   if (Q.lineno >= progress_next)
   progress_set_percent (Q.lineno);
   goto main_loop;
  }

lastline:
 exchangelines();
 emptyline();
 analise();
}
  /*
static void enough_memory()
{
 Q.boxalloc = (BOX *)box_pool;
 root_file = (PROOT) (((Word8*)Q.boxalloc) + BOX_NUMBER*BOXSIZE);
 if (memory_pool_end <= (Word8*)root_file) error_exit(ERR_comp,9);
}
    */
static void initdsect()
{
 MN *p;
 Int16 i;
 /*memset (&Q, 0, sizeof(Q));

 Q.mnstart    = Cmnstart;
 Q.line1start = Cline1;
 Q.line2start = Cline2;
 Q.scan_buffer = Cscan;
   */
 memset (Q.mnstart,      0 , sizeof (MN)  * SEG_MAX_NUM);
 memset (Q.line1start,   0 , sizeof (BWS) * SEG_MAX_NUM);
 memset (Q.line2start,   0 , sizeof (BWS) * SEG_MAX_NUM);
 /*memset (Q.scan_buffer,  0 , 0x4000 + LINE_MAX_LTH);
   */
 Q.lineno = 0;
 p = Q.mainalloc = Q.mnstart;
 for (i = 0; i < SEG_MAX_NUM-1; p++, i++) p->mnfirstbox = (BOX *)(p+1);
 p->mnfirstbox = NULL;
 Q.oldline = Q.line1start; Q.newline = Q.line2start;
}

static void allocboxes()
{
 BOX *b;
 Int32 i;
 for (b = Q.boxalloc = Q.boxstart, i=0; i<box_number-1; i++,
      b = (BOX *)((Word8*)b + BOXSIZE))
  b->boxnext = (BOX *)((Word8*)b + BOXSIZE);
 b->boxnext = NULL;
}

static void begin()
{
 Q.dcodeptr = Q.scan_buffer; Q.dcodeend = Q.dcodeptr + image_lth;
 emptyline();
}

static void emptyline()
{
 Q.newline->b=0; Q.newline->w=-0x7000;
}

static void exchangelines()
{
 BWS *p;
 p = Q.oldline; Q.oldline = Q.newline; Q.newline = p;
}

static Word16 readline()
{
 Word8* p;
 Int16 i;
 p =  Q.dcodeptr + image_lth;
after_read:
 if (p + image_lth > Q.dcodeend) goto rd_source;

 Q.dcodeptr = p; exchangelines();
 p+=image_disp_byte;
 *p &= image_disp_mask; *(p+image_disp_end-1) &= image_black;
 extrcomp_seglist (p,Q.newline,Q.newline + SEG_MAX_NUM,
                   image_disp_end);
 return 1;

rd_source:
 i = source_read (Q.scan_buffer, p, Q.dcodeend);
 if ( i<=0 ) return 0;
 Q.dcodeend = Q.dcodeend - p + i + Q.scan_buffer;
 p = Q.scan_buffer;     goto after_read;
}

static Int16 fax_test()
{
 BWS * old, * new;
 old = Q.oldline; new = Q.newline;
 while (1)
  {
   if ((old->b != new->b) || (old->w != new->w)) return 0;
   if (old->w < 0) return 1;
   old++; new++;
  }
}

static void fax_double()
{
 BWS * old, * new;
 exchangelines();
 old = Q.oldline; new = Q.newline;
 while (1)
  {
   new->b = old->b; new->w = old->w; new->box = NULL;
   if (old->w < 0) return;
   old++; new++;
  }
}
