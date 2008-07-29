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


#include "nt_types.h"
#include "struct.h"
#include "func.h"
#include "lang.h"
#include "ligas.h"

//		Common variables

extern c_comp wcomp;
//extern version * start_rec;
//extern BYTE records_change;

//
//		Proportional criteria
//
//
//

extern INT prop_l_delta, prop_r_delta;
extern BYTE * letters_pidx_table;
void pidx_crit ()
{
	/*
 INT pidx;
 version *v;
 INT i;
 WORD let;
 pidx = prop_index (wcomp.h, wcomp.w);
 wcomp.pidx = (BYTE)pidx;
 for (i=0, v=start_rec; i<wcomp.nvers; i++, v++)
  {
   let = (BYTE)(v->let) * 2;
   if (pidx + prop_l_delta < letters_pidx_table[let])
    {
     wcomp.reasno |= c_rn_left;
false:
     v->prob = 0; records_change = 1; continue;
    }
   if (pidx - prop_r_delta > letters_pidx_table[let+1])
    { wcomp.reasno |= c_rn_right;	goto false; }
  }
  */
}

void v2_pidx_crit (cell *c)
{
 INT pidx;
 version *v, *wv;
 WORD let;
 // Paul 07-12-99
 if (c->nvers==0)
   return;
 //
 c->reasno=0; pidx = prop_index(c->h, c->w); wv = v = c->vers;
 while (v->let)
  {
   if( !c->accent_leader &&
	   (is_cen_language(language)	||
	    is_baltic_language(language)||	// 09.07.2001 E.P.
	    is_turkish_language(language)	// 21.05.2002 E.P.
	   )
	 )
    let = (wv->let=v->let) * 2;
   else
    let = (let_sans_acc[wv->let=v->let]) * 2;
   wv->prob = v->prob;
   if (pidx + prop_l_delta < letters_pidx_table[let])
	{ c->reasno |= c_rn_left; v++; continue; }
   if (pidx - prop_r_delta > letters_pidx_table[let+1])
	{ c->reasno |= c_rn_right; v++; continue; }
   v++; wv++;
  }
 wv->let = 0;
 if ((c->nvers -= v-wv) == 0) set_bad_cell(c);
}

BOOL pidx_skip(INT h, INT w,BYTE t_let)
{
  INT pidx;
  WORD let;

  pidx=prop_index(h,w);
  let = t_let <<1;
  if( (pidx + prop_l_delta < letters_pidx_table[let]) ||
    (pidx - prop_r_delta > letters_pidx_table[let+1]) ) return FALSE;
  else return TRUE;
}

WORD el_pidx_crit(WORD t_let,INT pidx)
{
  WORD let;

  let = (BYTE)t_let * 2;
  if( (pidx + prop_l_delta < letters_pidx_table[let]) ||
    (pidx - prop_r_delta > letters_pidx_table[let+1]) ) return FALSE;
  else return TRUE;
}
