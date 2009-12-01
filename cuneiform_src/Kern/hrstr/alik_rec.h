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

struct tag_intervals {uchar osnl; uchar osnr; uchar lb; uchar mb; uchar rb; uchar cvl; uchar cvr; uchar cvm; uchar wf; };
/* lb-����� �࠭��,rb-�ࠢ�� �࠭��,cvl-���-�� ��������� �� ��� ���ࢠ�
   ᫥��,cvr-���-�� ��������� �� ��� ���ࢠ� �ࠢ�,ps-���-�� ��������� �� ��� ���ࢠ� � �।��� */
typedef struct tag_intervals MasIntervals; /* ���ᨢ ���ࢠ���*/

struct tag_intervals1 {uchar osnl; uchar osnr;};
typedef struct tag_intervals1 MasIntervals1; /* ���ᨢ ���ࢠ���*/

// module defpoint.c
INT  Alik_define_cut_points(pchar,struct own_cut *,INT,INT,INT);
void Alik_set_method_for_cut_points(struct own_cut *,INT,INT,puchar);
uchar Alik_gde_i_kak_naxodjatsa_tochki(uchar,struct own_cut *,INT,INT);

// module alcutfun.c
void Alik_del_equal_hole(PINT,pchar,PINT,INT,INT,INT);
void Alik_del_p_cut(pchar,PINT,INT,INT,INT,char);
void Alik_del_3_cut(pchar,PINT,INT,INT,INT,puchar);
void Alik_del_y_cut(pchar,INT,PINT,INT);
void Alik_del_equal(PINT);
INT  Alik_del_doubl_cut(PINT,pchar,PINT,INT);
INT  Alik_del_detail(pchar,INT,INT,PINT);
uchar Alik_kill_right_points(INT,pchar,pchar,PINT,INT);
uchar Alik_kill_left_points(INT,PINT,INT);
uchar Alik_kill_left_right_points(PINT,INT);
uchar Alik_del_a(PINT,puchar,uchar,uchar);
uchar Alik_del_a_from_interval(PINT,puchar,uchar,uchar,uchar*,uchar*);
void Alik_UpBlackPoint(pchar,INT,INT,puchar);
uchar Alik_check_c(puchar,PINT,INT);

void Alik_cut_short(pchar,pchar,INT,INT,pchar,PINT,PINT,pchar);
void Alik_cut_hole(pchar,INT,PINT,INT,INT,pchar,PINT,uchar);
void Alik_cut_l(PINT,pchar,INT,INT,PINT);
void Alik_cut_d(pchar,PINT,pchar,INT,INT,INT,INT,pchar);
void Alik_cut_y(pchar,pchar,pchar,INT,INT,PINT,puchar,INT,pchar,pchar,PINT,puchar);
void Alik_double_serif(PINT,pchar,pchar,INT,INT,INT,INT,PINT,puchar,puchar);
void Alik_defis(pchar,PINT,INT,INT,INT,INT,PINT);

void Alik_def_cut_flg(cell *,struct cut_elm *,struct cut_elm *,INT,uchar);
INT  Alik_set_position_brus(pchar,INT,INT,INT);
INT  Alik_Check_T(pchar,INT,INT,INT);
void Alik_Check_Rus_D(pchar,pchar,INT,INT,PINT,puchar,INT,pchar,pchar,PINT,puchar);
void Alik_find_brus(pchar,pchar,pchar,INT,INT,INT,pchar,pchar,PINT,PINT,puchar,puchar);
void Alik_rus_bad_c(pchar,pchar,INT,INT,pchar,pchar,PINT,PINT,puchar,puchar);
uchar Alik_find_black_interval(puchar str,uchar len,puchar intrvl);

void Alik_form_bound(pchar,uint16_t,uint16_t,uint16_t,pchar,uint16_t);
void Alik_my_correct_base_lines(PINT,PINT,INT,INT,INT,puchar,PWORD,puchar);
void Alik_correct_base_lines(pchar,INT,INT,INT*,INT*);
INT  Alik_sort(PINT,PINT,INT);
INT  Alik_search_bound_point_in_raster(pchar,INT,INT);
void Alik_tr_bit_matr(INT,INT,pchar,pchar,INT,INT);
void Alik_cor_pnt(PINT,PINT,PINT,INT,INT,INT,INT,pchar,pchar);
int  Alik_sort_function( const void *a, const void *b);
INT  Alik_up_position_double_serif(puchar,INT,INT,PWORD,puchar,INT);
void Alik_CountCut(pchar,INT,INT,puchar,puchar);
uchar Alik_priznak_del_3_cut(puchar,INT,INT);
void Alik_cor_height_and_var(INT,struct own_cut *,PINT,INT,INT);
void Alik_new_points(INT *,struct own_cut *,struct own_cut *,INT,INT,PINT,
                     pchar);



