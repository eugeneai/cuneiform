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


#ifndef CUTSTR

#define CUTSTR 1

#define MAX_CELLS_IN_LIST    8

struct v_v
 {INT v1,v2,v3;};
typedef struct v_v v_val;

struct save_vers
 {INT nvers; version vers[VERS_IN_CELL]; CHAR flg; CHAR pos; BYTE source;
  BYTE broken_II; BYTE cg_flag_fine;BYTE accent_leader;
  BYTE bottom_accent;   // 16.10.97 E.P.
  BYTE history;      // Nick  18.6.99
  INT  clink;        // Nick  18.6.99
  WORD clu_attr;     // Nick  18.6.99
  INT  nClust;
  version pr_vers;
  };
typedef struct save_vers SVERS;

struct cut_elm
 {
 CHAR x;                            // position
 CHAR dh;                           // height to be cut
 CHAR h;                            // end of segment
 CHAR var;                          // method
 v_val lv;                          // two-component estimate of left side
 CHAR px;                           // best previous point
 v_val rv;                          // two-component estimate of right sude
 CHAR duflm, gvarm, duflr, gvarr;   // glue variant, dust flags
 SVERS  versm;                      // best cell versions
 SVERS  versr;                      // right part versions
 };

typedef struct cut_position
 { INT row1, row2, cuth; CHAR flag; } cut_pos;
struct glue_struct
 {
 c_comp *complist[MAX_CELLS_IN_LIST];
 cell *celist[MAX_CELLS_IN_LIST];
 cell *maxlist[MAX_CELLS_IN_LIST];
 cell *nclist[MAX_CELLS_IN_LIST];
 void *kitlist[MAX_CELLS_IN_LIST];
 BYTE ncell, ngluc, arg, maxnc;
 BYTE flarg, fres, var;
 INT  Dist, dist, bdiff, maxval;
 MN   *mn;
 INT  row, col, height, width;
 INT c_r, c_c, c_w, c_h, c_mc, c_mr, c_dens;
 };
typedef struct glue_struct s_glue;

struct all_c
 {
 INT   Nb, Nd, minb, mind, minf;
 BYTE  flag;
 #define dust_left 1
 #define dust_right 2
 #define cl_disorder 4
 cell *minlet, *maxlet, *mincl, *maxcl;
 cell *bcells[MAX_CELLS_IN_LIST],
      *dcells[MAX_CELLS_IN_LIST];
 };
typedef struct all_c all_cells;

struct st_answer
 {
 CHAR ltr;
 CHAR fnt;
 WORD iprob;
 CHAR n_rsn; // number of letter from list of same letters
 };
typedef struct st_answer t_answer;

struct info_elm
 {
 CHAR topline, botline;
 CHAR lnum;
 CHAR topf, toph, botf, both;
 CHAR sumb;
 };

struct own_cut
 {
 CHAR x;     // position
 CHAR dh;    // height to be cut
 CHAR h;     // end of segment
 CHAR var;   // method
 };

struct extrem_elem
 {
 CHAR type;      // +- -- max/min
 CHAR cat;       // category
 CHAR beg, end;  // area limits
 CHAR val;       // etrem value
 };

struct linehdr
 {
 INT  lth;
 WORD  dy;
 WORD  y0;
 CHAR flag;
 };

struct segment
 {
 BYTE lth;
 BYTE end;
 };

struct short_line_header
 {
 BYTE top;      	// top string of line (relative)
 BYTE bot;	        // bottom string of line (relative)
 BYTE fb;	        // beginning of first segment of line
 BYTE fe;	        // end of first segment of line
 BYTE lb;	        // beginning of last segment of line
 BYTE le;	        // end of last segment of line
 BYTE next;	        // number of next line in (shortened) lines' list
 INT  segm_addr;        // offset of first segment in line
 };

struct vertex_header
 {
 BYTE top;	// top string of component (relative)
 BYTE bot;	// bottom string of component (relative)
 INT  beg;	// offset of first segment of line in c_comp
 INT  end;	// offset of last + 1 segment of line in c_comp
 BYTE out;	// outgoing valency
 BYTE in;	// incoming valency
 };

struct local_min
 {
 INT  value;    // value of minimum
 INT  ambeg;    // x-coordinate of beginning
 INT  amend;    // end of local minimum area
 };

struct func_elem
 {			// description of argument (x)
 CHAR fvalue[3];	// values of lth, lower, upper
 CHAR extrem[6];	// number of minimum area for this
			//   particular x for three functions;
			//   -1 means out of minima areas
 CHAR line;		// number of line in graph containing this x
 };

struct graph_comp
 {
 CHAR top;
 CHAR bot;
 CHAR left;
 CHAR right;
 };

struct less_vertex_elem
 {			// graph without one vertex
 CHAR n_connect;	// number of connected components
 };

typedef struct own_cut mas_cpnt;
#endif