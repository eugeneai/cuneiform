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

/*

  SPELTAB.h containes structures, headers and constants for
  Special dictionary <CountryCode>.ART and SpecialReplacementTable
  <CountryCode>.TAB files creature and processing.

*/

#ifndef __SPEC_REP_TAB_DEFS__
#define __SPEC_REP_TAB_DEFS__

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

#ifndef PPS_MAC
   #pragma message(__FILE__)
#endif

/* -------------------------------------------------------------------------
The following constants are restriction flags for special replacement table.
 ------------------------------------------------------------------------- */


#define ANY_S  0x00   /*No restrictions                                */
#define BAD_S  0x01   /*Replacement applies only for notconfidentially
                        recognized symb                                */
#define EMB_S  0x01   /*Replacement applies for a couple of symbs with
                        overlapped envelopes.                          */
#define DEL_S  0x02   /* Only for delemeters.                          */
#define WID_S  0x04   /* wide letter */
#define FAX_M  0x10   /*Only for Fax recognition                       */

/* -------------------------------------------------------------------------
   Some definitions for Spec dictionary and Spec Replacements Table.
 ------------------------------------------------------------------------ */
#define ARTFILE_ID "CTC AS v1.0"
#define TABFILE_ID "CTC RT v1.0"

#define BUFF_SIZE 0x5000
#define LINE_LTH  120

#define EMP "_EMPTY"

#define XOR_MASK  0x4a

typedef struct
 {
  BYTE   id[ sizeof(ARTFILE_ID)];
  BYTE   voc_no;                      // INT
  BYTE  _unused;
 } ArtFH;

typedef struct
 {
  CHAR pref_no;
  CHAR post_no;
  BYTE relabty;                       // INT
  BYTE  _unused;
 } ArtVH;

#define NOVOC -1
#define  VOC  0
#define PREF  1
#define BODY  2
#define POST  3
#define FREC  4



typedef struct
 {
  BYTE  id[ sizeof(TABFILE_ID)];
  BYTE  rep_no;                       // INT
  BYTE  _unused;
 } TabFH;

typedef struct artstr
 {
  BYTE sr1;                   /* code1 of what replace */
  BYTE sr2;                   /* code2 of what replace */
  BYTE obj1;                  /* code1 by what replace */
  BYTE obj2;                  /* code2 by what replace */
  BYTE objt1;                 /* type of obj1          */
  BYTE objt2;                 /* type of obj2          */
  BYTE objts1;                /* type_sp of obj1       */
  BYTE objts2;                /* type_sp of obj2       */
  BYTE cond_sr1;              /* cond1 for sr1         */
  BYTE cond_sr2;              /* cond2 for sr2         */
  BYTE cond_sr12;             /* cond12 for sr1&sr2    */
  BYTE cond_obj12x;           /* cond12 for obj1&obj2 to check before */
  BYTE cond_obj12r;           /* cond12 for obj1&obj2 to check after  */
  BYTE _unused;
 } ARTS;

/*
#if !defined(WATCOM) && !defined(THINK_C)
  #if sizeof(TabFH)%2 != 0
  #error Must be odd length of structure for MAC portability.
#endif
  #if sizeof(ARTS)%2 != 0
  #error Must be odd length of structure for MAC portability.
#endif
#if sizeof(ArtFH)%2 != 0 || sizeof(ArtVH)%2 != 0
  #error Must be odd length of structure for MAC portability.
  #endif
#endif
*/
#endif
