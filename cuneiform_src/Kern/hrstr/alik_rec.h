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

#define AlikBrusOn
#define AlikcOn
#define AliktOn
#define AlikdOn
#define AlikyOn
#define AlikBlOn

#define R_H 48          /* raster height */
#define R_W 128         /* raster width (in dots) */
#define R_WB R_W/8      /* raster width (in bytes) */
#define R_S  128*64/8 //R_H*R_W/8   /* raster size */

#define NEW_POINTS_NAV_BOUND  19  /* �࠭�� ����ᠭ��                                      */
#define NAV_BOUND       25  /* �࠭�� ����ᠭ��                                      */
#define BOUND_SH         2  /* �࠭�� ���⪮�� ࠧ१����                           */
#define MaxHeightBrus    5  /* ���� ���� (��,�� ��.)                              */
#define MAX_HEIGHT_DS    8
#define MIN_WIDTH_WINGS  2  /* �ਭ� ���� (��,�� ��.)                              */
#define MIN_WIDTH_RAS   20
#define MaxCountBrus    15  /* ����. ���-�� ���ᮢ.                             */
#define MAX_WIDTH_STOLB  8  /* �ਭ� ���� (�)                                */
#define MIN_OSNOV_D     16  /* ���. �᭮����� ��� �*/
#define MIN_WIDTH_TAIL   6  /* �ਭ� 墮�� �     */
#define MIN_HEIGHT_FOR_C 6
#define MAX_HEIGHT_FOR_C 11
#define MAX_BAD_INTERVAL 6


#define MINCOL       4  /* ����� ��砫쭮�� �⮫�� ��� ��१����                     */
#define MAX_HOLE    10  /* ���ᨬ��쭠� �ਭ� ��                                    */
#define NUMB_STEP    8  /* (5) �᫮ 蠣�� ����� ��� ���᪠ ����� � "�" ��� "�"       */
#define MIN_D        3  /* �������쭠� ���� ����⪠ ���� ������� �����             */
#define LEN_D        3  /* (5) ���ᨬ��쭠� ���� (MIN_D+LEN_D) ����⪠             */
#define LEFT_STEP    3  /* �᫮ 蠣�� ����� �� ���뢠��� ����                       */
#define MIN_FOOT     3  /* �������쭠� �ਭ� ���� � "�", "�", "�" � �.�.             */
#define MAX_FOOT    10  /* ���ᨬ��쭠� �ਭ� ����                                   */
#define FROM_CEN_UP 10  /* (4) ��室 �� �।�������� ���孥� ������� ����� �� 業��  */
#define FROM_CEN_DW  4  /* ��室 �� �।�������� ������ ������� ����� �� 業��       */
#define TO_CENTER    3  /* ��室 �� �।�������� ������� ����� � 業���               */
#define MAX_SDVIG    2  /* ���ᨬ���� ᤢ�� � ��஭� �� ���� ��                   */
#define STEP_SER     8  /* 蠣 ���। �� ���������� ���                            */
#define DEFIS_LEN    6  /* ����� ����                                               */
#define OTSTUP_L     4  /* ����� ����� �� ������ ������� ����� � �� "�"           */
#define SDVIG_L      8  /* �᫮ 蠣�� ��ࠢ� �� �� "�"                            */
#define SDVIG_H      5  /* �������쭠� ��㯥�쪠                                      */
#define Y_CUT        6  /* ���⮯�������� ����祭�� ����� "�"                       */
#define OTSTUP      10
#define MAX_CUT_POINT_NUMBER 30 /* maximal number of cut points */

struct tag_brus { INT  L; INT  R; INT H; INT P;}; /* L-left,R_right,H-height,P-position */
typedef struct tag_brus  Coor_brus;

struct tag_intervals {BYTE osnl; BYTE osnr; BYTE lb; BYTE mb; BYTE rb; BYTE cvl; BYTE cvr; BYTE cvm; BYTE wf; };
/* lb-����� �࠭��,rb-�ࠢ�� �࠭��,cvl-���-�� ��������� �� ��� ���ࢠ�
   ᫥��,cvr-���-�� ��������� �� ��� ���ࢠ� �ࠢ�,ps-���-�� ��������� �� ��� ���ࢠ� � �।��� */
typedef struct tag_intervals MasIntervals; /* ���ᨢ ���ࢠ���*/

struct tag_intervals1 {BYTE osnl; BYTE osnr;};
typedef struct tag_intervals1 MasIntervals1; /* ���ᨢ ���ࢠ���*/

// module defpoint.c
INT  Alik_define_cut_points(PCHAR,struct own_cut *,INT,INT,INT);
void Alik_set_method_for_cut_points(struct own_cut *,INT,INT,PBYTE);
BYTE Alik_gde_i_kak_naxodjatsa_tochki(BYTE,struct own_cut *,INT,INT);

// module alcutfun.c
void Alik_del_equal_hole(PINT,PCHAR,PINT,INT,INT,INT);
void Alik_del_p_cut(PCHAR,PINT,INT,INT,INT,char);
void Alik_del_3_cut(PCHAR,PINT,INT,INT,INT,PBYTE);
void Alik_del_y_cut(PCHAR,INT,PINT,INT);
void Alik_del_equal(PINT);
INT  Alik_del_doubl_cut(PINT,PCHAR,PINT,INT);
INT  Alik_del_detail(PCHAR,INT,INT,PINT);
BYTE Alik_kill_right_points(INT,PCHAR,PCHAR,PINT,INT);
BYTE Alik_kill_left_points(INT,PINT,INT);
BYTE Alik_kill_left_right_points(PINT,INT);
BYTE Alik_del_a(PINT,PBYTE,BYTE,BYTE);
BYTE Alik_del_a_from_interval(PINT,PBYTE,BYTE,BYTE,BYTE*,BYTE*);
void Alik_UpBlackPoint(PCHAR,INT,INT,PBYTE);
BYTE Alik_check_c(PBYTE,PINT,INT);

void Alik_cut_short(PCHAR,PCHAR,INT,INT,PCHAR,PINT,PINT,PCHAR);
void Alik_cut_hole(PCHAR,INT,PINT,INT,INT,PCHAR,PINT,BYTE);
void Alik_cut_l(PINT,PCHAR,INT,INT,PINT);
void Alik_cut_d(PCHAR,PINT,PCHAR,INT,INT,INT,INT,PCHAR);
void Alik_cut_y(PCHAR,PCHAR,PCHAR,INT,INT,PINT,PBYTE,INT,PCHAR,PCHAR,PINT,PBYTE);
void Alik_double_serif(PINT,PCHAR,PCHAR,INT,INT,INT,INT,PINT,PBYTE,PBYTE);
void Alik_defis(PCHAR,PINT,INT,INT,INT,INT,PINT);

void Alik_def_cut_flg(cell *,struct cut_elm *,struct cut_elm *,INT,BYTE);
INT  Alik_set_position_brus(PCHAR,INT,INT,INT);
INT  Alik_Check_T(PCHAR,INT,INT,INT);
void Alik_Check_Rus_D(PCHAR,PCHAR,INT,INT,PINT,PBYTE,INT,PCHAR,PCHAR,PINT,PBYTE);
void Alik_find_brus(PCHAR,PCHAR,PCHAR,INT,INT,INT,PCHAR,PCHAR,PINT,PINT,PBYTE,PBYTE);
void Alik_rus_bad_c(PCHAR,PCHAR,INT,INT,PCHAR,PCHAR,PINT,PINT,PBYTE,PBYTE);
BYTE Alik_find_black_interval(PBYTE str,BYTE len,PBYTE intrvl);

void Alik_form_bound(PCHAR,WORD,WORD,WORD,PCHAR,WORD);
void Alik_my_correct_base_lines(PINT,PINT,INT,INT,INT,PBYTE,PWORD,PBYTE);
void Alik_correct_base_lines(PCHAR,INT,INT,INT*,INT*);
INT  Alik_sort(PINT,PINT,INT);
INT  Alik_search_bound_point_in_raster(PCHAR,INT,INT);
void Alik_tr_bit_matr(INT,INT,PCHAR,PCHAR,INT,INT);
void Alik_cor_pnt(PINT,PINT,PINT,INT,INT,INT,INT,PCHAR,PCHAR);
int  Alik_sort_function( const void *a, const void *b);
INT  Alik_up_position_double_serif(PBYTE,INT,INT,PWORD,PBYTE,INT);
void Alik_CountCut(PCHAR,INT,INT,PBYTE,PBYTE);
BYTE Alik_priznak_del_3_cut(PBYTE,INT,INT);
void Alik_cor_height_and_var(INT,struct own_cut *,PINT,INT,INT);
void Alik_new_points(INT *,struct own_cut *,struct own_cut *,INT,INT,PINT,
                     PCHAR);



