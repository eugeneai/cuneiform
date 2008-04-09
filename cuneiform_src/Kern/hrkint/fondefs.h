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


#ifndef PPS_MAC
#pragma message(__FILE__)
#endif

#ifndef __FONDEFS_H
#define __FONDEFS_H


#include "recdefs.h"
#include "leodefs.h"

	typedef struct tagFontInfo {
		int count[256];   // how many symbols in biggest cluster
		int width[256];   // symbol width in biggest
		int height[256];  // symbol height in biggest
		int number[256];  // welet number - for fast search
		int numFont[256]; // how many clusters with name
	} FontInfo;

	typedef struct tagSizesInfo {
		int name;
		int count;
		int width;
		int height;
	} SizesInfo;

	typedef struct tagClustInfo {          // information about one cluster
      Word8 let;     // ASCII ��� 
	  Word8 weight;  // �� �������� ������
	  Word8 prob;    // ������
	  Word8 valid;   // ���������� (LEO_VALID_...)
	  Word8 attr;    // �������� (CTB_PRINT_...)
	  Word8 mw;      // ������� ������ �������� � ��������
	  Word8 mh;      // ������� ������ �������� � ��������
	  Word8 kegl;    // �������� ����� 
      char reserved[24];
	} ClustInfo;

	// ���������� � �������������� �������
	typedef struct tagFonSpecInfo {          
      Int16  nInCTB;      // ���� > 0 - ����� � CTB
	  Int16  nFieldRow;   // ���� > 0 - ����� ������ (����?)
      Int16  col;         // ���� - ���������� 
	  Int16  row;         //  
	  Word32 wFonFlags;   // ������� - ����� frhdefs.h

//Andrey - 20030620 - flags from frhdefs.h
//----------------------------------------
         #define  FFC_EMPTY         0x0001
            // cell is empty, in this case rcFill should contain:
            // rcFill.left =<leftmost> ?<field.left> :<prev_char>.rcFill.right+1;
            // rcFill.right=<rightmost>?<field.right>:<next_char>.rcFill.left-1;
            // rcFill.top   = ave( <prev_char>.rcFill.top,<next_char>.rcFill.top );
            // rcFill.bottom= ave( <prev_char>.rcFill.bottom,<next_char>.rcFill.bottom );
            // so, rcFill width should strictly equals to width of space!

         // cell in real coordinates is determined by rcCell:
         #define  FFC_CELL                   0x0002 // rcCell initialized
         #define  FFC_CELL_STRONG_TOPBOTTOM  0x0004 // if rcCell initialized
         #define  FFC_CELL_STRONG_LEFTRIGHT  0x0008 // if rcCell initialized

      ////////////////////////////////////////////
      // �������� ��������� �� ���������� ���������������:
         #define  FFC_FON_CONFIRMED    0x8000                     // ����: FFC_FON_VERIFICATION
            // ������ ������������ ���������� ������������

         #define  FFC_FON_TWIN         0x4000
            // ��������� ������ ����������� ������������ � ������� �������� � ����� ���������

	      #define  FFC_FON_ALERT        0x2000
            // ���������� ����������� (������ ������, ������� ������ ��������� � ����� ������...)
            // �� �� ���������, ����� ���������� �����������

	      #define  FFC_FON_REJECT       0x1000
            // ��������� ����������� � ������������� ���������� ���������� �������

	      #define  FFC_FON_CHANGE       0x0800
            // �������� ������ ������ ������������

      ////////////////////////////////////////////
      // �������� ��������� �� ���������
         #define  FFC_CON_CONFIRMED    0x800000
            // ������ ������������ ���������� ������������

         #define  FFC_CON_TWIN         0x400000
            // ��������� ������ ����������� ������������ � ������� �������� � ����� ���������

	      #define  FFC_CON_ALERT        0x200000
            // ���������� �����������
            // �� �� ���������, ����� ���������� �����������

	      #define  FFC_CON_REJECT       0x100000
            // ��������� ����������� � ������������� ���������� ���������� �������

	      #define  FFC_CON_CHANGE       0x080000
            // �������� ������ ������ ������������

      ////////////////////////////////////////////
      // �������� ��������� �� FRH
         #define  FFC_STR_BEG          0x80000000
            // ������ ������

         #define  FFC_STR_END          0x40000000
            // ����� ������

	      #define  FFC_DBT_BEG          0x20000000
            // ������ ������������� ���������

	      #define  FFC_DBT_END          0x10000000
            // ����� ������������� ���������

	  Int16  nClust;      // ������� - ����� ������� ��������
	  Int16  countRazmaz;
	  Word8  nLet;        // ���� > 0 - ��� ASCII 
	  Word8  onlySelf;    
      Int16  h;          // ���� - �������
	  Int16  w;          //  
	  Word8  palkiLeo;   // ���� != 0 - ������������ ����� �� ���
	} FonSpecInfo;

#define MAXCHECKALT 4
	// ���������� � ����������� �������� �������
	typedef struct tagFonTestInfo { 
		Int16 nClust; // ����� �������
		Word8 prob;
		Word8 flag;
		Word8 kegl;
		Word8 reserv[3];
	} FonTestInfo;

	// ������ � ���������� ���� � CTB-�����
	typedef struct tagFonClusterBase{
		Word8  oem;
		Word8  fullX;
		Word8  fullY;
		Word8  let;
		Word8  w;
		Word8  h;
		Word8  weight;
		Word8  porog;
		Word8  mw;
		Word8  mh;
		Word8  prob;
		Word8  attr;
		Word16 fill;
		Word16 num;
		Word16 invalid;
		Word8  valid;
		Word8  kegl;
        Int16  sr_col;
		Int16  sr_row;
		Word32 summa;
		Word32 fields[2]; // [NFIELDDWORD]
		Int16  nInCTB; 
		Word32 tablColumn;
	} FonClusterBase;

	/////////
	// ��������� ������������� ///
	// �������������� � ���������� �������
#define FONCLU_ClusterHand  0x4000 
	// � ����� ������ ����� ���� ����� �������
#define FONCLU_MultiFontRow 0x2000 
	// ��������� ��� ���� .clu
#define FONCLU_SaveAsClu    0x1000 
	// ��������� ��� �������� - �� ������ ������
#define FONCLU_NotFonts     0x800
	// ��������� ���� ������ ��������
#define FONCLU_SaveWeak     0x400
	// ��������� � ��� ��������� ���������
#define FONCLU_AddClu       0x200
    // ������� ���� - ���� ������� (tiger format) 
#define FONCLU_InputR       0x100
	// ����� ��� ������
#define FONCLU_Threshold    0xFF
#endif
