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


// ROUT.H

//********************************************************************
// Copyright (c) 1999 Cognitive Technologies Ltd.
//
// ROUT.H - API ������ ROUT
//
// This file creation date: 18.05.99
// By Eugene Pliskin pliskin@cs.isa.ac.ru
//********************************************************************
#pragma message(__FILE__"(1)")

#ifndef __ROUT_H
#define __ROUT_H

#include "puma.h"
#include "pumadef.h"

#ifdef __ROUT__
  #define ROUT_FUNC  FUN_EXPO
#else
  #define ROUT_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
	extern "C" {
#endif


#ifndef Byte
	typedef unsigned char Byte;
#endif

//*****************************************************************
// ������� ������ �������� ��� ���������
// ��. ������� ROUT_ListFormats � ROUT_ListCodes
typedef struct {
	long code;
	char name[64];
} ROUT_ITEM;
//*****************************************************************
// ������ ��������
typedef enum {
ROUT_FMT_Text  = PUMA_TOTEXT,// 2 - Plain text
ROUT_FMT_SmartText = PUMA_TOSMARTTEXT, // 4 - Formatted text
ROUT_FMT_TableText  = PUMA_TOTABLETXT, // 0x100 - Table text
ROUT_FMT_CSV = PUMA_TOTABLECSV, // 0x200 - Table CSV (comma separated)
ROUT_FMT_DBF = PUMA_TOTABLEDBF,	// 0x400 - Table DBF
ROUT_FMT_WKS = PUMA_TOTABLEWKS,	// 0x1000 - Table WKS (Lotus)
ROUT_FMT_HTML = PUMA_TOHTML,	// 0x2000 - HTML

ROUT_FMT_COUNT  = 7,	// ���������� ��������
ROUT_FMT_MAX  = 0x2000	// ������������ ������
	} ROUT_FMT;

//*****************************************************************
// ������ ���������
typedef enum {
// 1 - ASCII (text, formatted text, dbf)
ROUT_CODE_ASCII = PUMA_CODE_ASCII,

// 2 - Windows (all formats)
ROUT_CODE_ANSI = PUMA_CODE_ANSI,

// 4 - KOI8-R (text, formatted text, html)
ROUT_CODE_KOI8R = PUMA_CODE_KOI8,

// 8 - ISO (text, formatted text, html)
ROUT_CODE_ISO = PUMA_CODE_ISO,

	ROUT_CODE_COUNT  = 4,	// ���������� ���������
	ROUT_CODE_MAX  = 8		// ������������ ���������
	} ROUT_CODE;
//*****************************************************************
// ����� ���������� ������
typedef enum {
// 1 - �������� ������� � ����� �������� � ������� ROUT_FMT_Text
ROUT_TABLE_TEXT_INCLUDED = 1,

// 2 - ������������ �������
ROUT_TABLE_TEXT_ALIGN_COLUMNS = 2,

	} ROUT_TABLE_TEXT_OPTIONS;
//*****************************************************************
// ����� ����� � DLL ����� ����� ���������.
ROUT_FUNC(Bool32) ROUT_Init(Word16 wHeightCode,Handle hStorage);
ROUT_FUNC(Bool32) ROUT_Done();
ROUT_FUNC(Word32) ROUT_GetReturnCode();
ROUT_FUNC(Int8 *) ROUT_GetReturnString(Word32 dwError);
ROUT_FUNC(Bool32) ROUT_GetExportData(Word32 dwType, void * pData);
ROUT_FUNC(Bool32) ROUT_SetImportData(Word32 dwType, void * pData);
//*****************************************************************
// �������
typedef enum
{
	// ����� ���������� ������ (�������-������ �����������
	// �� ����������� ������; ����������� ��� �������� ���
	// ��������� ������ ���������� ����� �� ����� ���������)
	ROUT_LONG_TableTextOptions = 100

} ROUT_EXPORT_ENTRIES;

/*
#ifdef __ROUT__
	#define DEC_FUN(a,b,c) typedef a (*FN##b)c; ROUT_FUNC(a) b c
#else
	#define DEC_FUN(a,b,c) typedef a (*FN##b)c;
//#endif
*/
#define DEC_FUN(a,b,c) ROUT_FUNC(a) b c

// ������ ��������, ������������ �� REC6.DAT � SPELABC.C.
// ������� ����� ���������� ������ "^", ��������� ����� �������� ��������
// �������� ��� ����������� vowels = "^bcd^fgh^^klmn^pqrst^v^x^z"
DEC_FUN(Bool32, ROUT_SetAlphabet,(
		Word32 sizeAlphabet,// ���������� ����
		char *upper,		// ��������� ����� ( ����� sizeAlphabet )
		char *lower,		// �������� �����  ( ����� sizeAlphabet )
		char *vowels		// ������� �����   ( ����� sizeAlphabet )
		));

// ������� ��� �������� ������ ������ �� ����� rec6all.dat
DEC_FUN(Bool32, ROUT_LoadRec6List,(
		char *rec6AllFilename
		));

// �������� ED-�����
DEC_FUN(Bool32, ROUT_LoadEd,
		// ��������� ��� � CED_ReadFormattedEd:
		(char *lpEdFile,	// ��� ����� ��� ����� � ������
		Bool32 readFromFile,	// TRUE, ���� ������ ��� �����
		Word32 bufLen));	// ����� (������ ��� readFromFile=FALSE)

// �������� ED-�����
DEC_FUN(Bool32, ROUT_UnloadEd,(void));

// ��������� ������ �������������� ��������
// ���������� ���������� �������� ��� (-1) ��� ������
DEC_FUN(long, ROUT_ListFormats,
	(PWord8 buf,	  // ����� ������ ��� ������ ROUT_ITEM
	Word32 sizeBuf // ����� ������
	));

// ��������� ������ ��������� �������� ����������
// ��� ������� ����������� ��������.
// ���������� ���������� �������� ��� (-1) ��� ������
DEC_FUN(long, ROUT_ListAvailableFormats,
	(PWord8 buf,	// ����� ������ ��� ������ ROUT_ITEM
	Word32 sizeBuf	// ����� ������
	));

// ��������� ������ ��������� ��� ������� �������
// ���������� ���������� ��������� ��� -1 ��� ������
DEC_FUN(long, ROUT_ListCodes,
	(PWord8 buf,	// ����� ������ ��� ������ ROUT_ITEM
	Word32 sizeBuf	// ����� ������
	));

// �������������� ���� ���� �� ������� �������
DEC_FUN(Byte, ROUT_Byte,(Byte c));

// �������������� ���� ������ �� ������� �������
DEC_FUN(Bool32, ROUT_Block,(
		Byte *lpMem,	// ����� ����� ������
		long sizeMem	// ����� ����� ������
		));

// ��������� ���������� �������� �� ��������.
// �������������� ������������� ��������� �������� (ROUT_LoadEd)
// � ���������� ������ ������ (ROUT_LONG_Format).
//
// ��� ��������� �������� ������ ���������� ������ �� ��������,
// � ��� ��-��������� �������� ������ ������ 1.
//
// ������ -1, ���� �������� �� ��������� ��� ��� ������ ������.
//
DEC_FUN(long, ROUT_CountObjects,());

// ��������������� � ���� ������ �� �������� ������
DEC_FUN(Bool32, ROUT_GetObject,
		(
		Word32 objIndex,	// ������ ������� ������� �� 1
		Byte *lpMem,	// ����� ����� ������ ( 0 - ������ ������)
		long *sizeMem	// ����� ����� ������ ( 0 - ������ ������)
		));

// ��������������� � ���� ������ � ������ � ����
DEC_FUN(Bool32, ROUT_SaveObject,
		(
		Word32 objIndex,	// ������ ������� ������� �� 1
		char *path,			// ���� �� ��������� �����
		Bool32 append		// ���������� � ����� �����
		));

//	������������ ��� ��������� ����� �� ����� ��������,
//	��� ������������� ���������� ������-��������� � ���
//	��������� ������� �������. ��������:
//		PageName_w.txt - ����� � ��������� ANSI
//		PageName_a.txt - ����� � ��������� ASCII
//		PageName_k.txt - ����� � ��������� KOI8-R
//		PageName_i.txt - ����� � ��������� ISO
//		PageName_b_w.txt - ��������� ����� � ��������� ANSI
//		PageName_b_w2.txt - ������ ������� �� ��������
//		� �.�.
DEC_FUN(char *, ROUT_GetDefaultObjectName,
		(
		Word32 objIndex	// ������ ������� ������� �� 1
		));

// ������ ������� ��� ����������� ����� �������
DEC_FUN(Word32, ROUT_GetObjectSize,(
		Word32 objIndex	// ������ ������� ������� �� 1
		));

#undef DEC_FUN

//*****************************************************************

// ������
typedef enum
{
 	// ��� �������� ��� ���������� .tif ��� .fed;
	// ����� �������� ��� �� �������� ����
	ROUT_PCHAR_PageName = 1,

	// �������� � ���������� CED
	ROUT_HANDLE_PageHandle = 2,

	// ���� �������������
	ROUT_LONG_Language = 3,

	// ������
	ROUT_LONG_Format = 4,

	// �������� ���������
	ROUT_LONG_Code = 5,

	// ���������� ������ �����
	ROUT_BOOL_PreserveLineBreaks = 6,

	// �������������� ������
	ROUT_PCHAR_BAD_CHAR = 7,

	// ���������� ����������� �� REC6.DAT
	ROUT_LONG_CountTigerToUserCharSet = 8,

	// ������ ����������� [3][128] (Tiger/Windows/DOS)
	ROUT_PPBYTE_TigerToUserCharSet = 9,

	// ������������ ���������� ����� ������ � ����� �������
	ROUT_LONG_MaxTextLinesInOneTable = 10,

	// �������� ����� �������� ������� �� ���������
	ROUT_ULONG_TableTextIntervalBetweenCellsYY = 11,

	// �������� ����� �������� ������� �� �����������
	ROUT_ULONG_TableTextIntervalBetweenCellsXX = 12,

	// �������� ������� �� ������ ������
	ROUT_ULONG_TableTextLeftIndent = 13,

	// ������ ������������ (������ - ���, t - ���������):
	// ������ 0 - ����� ������ �������� �������
	// ������ 1 - ����� ��������� �������
	// ������ 2 - ����� ��������� ������� �������
	ROUT_PCHAR_TableTextSeparators = 14

	// ����� ���������� ������ (�������-������ �����������
	// �� ����������� ������; ����������� ��� �������� ���
	// ��������� ������ ���������� ����� �� ����� ���������.
	// ��. enum ROUT_EXPORT_ENTRIES)
	// ROUT_LONG_TableTextOptions = 100

} ROUT_IMPORT_ENTRIES;

//#define DEC_FUN(a,b,c) typedef a (*FN##b)c
// �������
//#undef DEC_FUN

//*****************************************************************
// ���� ��������
typedef enum {
	ROUT_RETURN_OK = 0,
	ROUT_RETURN_NOTIMPLEMENT = 1,
	ROUT_RETURN_NO_MEMORY = 2,
	ROUT_RETURN_WRONG_ARGUMENT = 3,
	ROUT_RETURN_WRITING_TO_FILE = 4,
	ROUT_RETURN_OPEN_FILE = 5,
	ROUT_RETURN_CLOSE_FILE = 6,
	ROUT_RETURN_PAGE_NOT_LOADED = 7,
	ROUT_RETURN_OBJECT_NOT_FOUND = 8,
	ROUT_RETURN_POSSIBLE_LOSS_OF_DATA = 9
	} ROUT_RETURN_CODES;
//*****************************************************************

#ifdef __cplusplus
	}
#endif

#endif	// __ROUT_H
