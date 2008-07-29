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


#ifndef __BALDEFS_H
#define __BALDEFS_H


#include "recdefs.h"
#include "leodefs.h"

// ������� ���������
  typedef struct tagBAL_RSTR_GLOBALS
  {
	  Int32  language;
	  Int32  line_number;
	  Int32  fax1x2;

	  Int32  actual_resolution;
      Int32  fEdCode ;  // ASCII
      Int32  line_BL ;
      Int32  spec_camera ;
      Int32  no_linpen ;

      Int16  prop_l_delta;
	  Int16  prop_r_delta;

	  Word8 *let_lindef3;
      Word8 *let_lindef;
      Word8 *let_linpos;
      Word8 *let_linshape;
      Word8 *let_sans_acc;          // [257]
      Word8 *letters_pidx_table;    // 512
      Word8 *decode_ASCII_to_;      // [256][4]
	  Handle skew_corr;
	  Handle rast_is_BOX_solid;

	  Word8 db_status;
	  Word8 db_pass;
	  Handle snap_monitor;
	  Handle snap_show_text;
	  Handle snap_activity;
	  Handle snap_monitor_ori;//IGOR
	  Handle snap_is_marked; //IGOR
	  Handle snap_baselines; //IGOR
	  Handle snap_draw_line; //IGOR
	  Handle snap_del_line; //IGOR
  }
  BAL_RSTR_GLOBALS;

// �������-�������� ���������
  typedef struct tagBAL_INOUT_GLOBALS
  {
// ������ ������
   Int32   nIncline;
// ��������� ������
   INT     minrow,mincol, maxrow, maxcol;
// �������� ��
   INT     bs_got;     //
// �����
   INT	   bbs0,bbs1, bbs2, bbs3, bbs4, bbsm;
// ��������� ��� ����������� dust
   INT     bsdust_upper, bsdust_lower, bsdust_ps;
// ��������� ��
   INT     Nb1, Nb2, Nb3, Nb4, Nbt, Ps, Psf;
// ������� �� ������, ������ ������
   INT           Ns1,Ns2;        // in Iot.c   only  !!!
// ������ - ��
   BYTE          multi_bas;
// ����� ���� ���������� � dust
   BYTE          let_to_dust;
// ��� ����� � ������ ���������
   CHAR          all_caps;
// ��������� � ��������� � ������ ->bdiff, ->difflg.
   CHAR          all_diffs_made;
  }
 BAL_INOUT_GLOBALS;

 typedef struct BLIN_bas_ln_type
 { Int16 startcol, endcol;
//, startf, endf, ncells;
   Int16 ps, b1, b2, b3, b4;
   Int16 n1, n2, n3, n4;
   BYTE fl_def;
//   BYTE fl_ext;
//   cell *c1, *c2, *cf1, *cf2;
 } BAL_bas_ln;

#endif
