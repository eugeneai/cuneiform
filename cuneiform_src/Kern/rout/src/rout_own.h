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


// ROUT_OWN.H
#pragma message(__FILE__"(1)")

#pragma once

#define __ROUT__

#include "stdafx.h"
#include "rout.h"
#include "cfio.h"

#include "ced.h"
//#include "ced_struct.h"
#include "resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "compat_defs.h"

//*****************************************************************

// ���������� �����
// ���������, ����� DEBUG_PRINT ������� �� ���������� �����������
// � �� ������ �������������� ����� if ��� �������� ������...
// ���������: if (...) { DEBUG_PRINT(...,...,...); }
#ifdef _DEBUG
	#define DEBUG_PRINT \
			gFile = __FILE__;gLine = __LINE__;\
			MyDebugPrint
#else
	#define DEBUG_PRINT if(0) MyDebugPrint
#endif

#define NOT_IMPLEMENTED NotImplemented(__FILE__,__LINE__)
#define WRONG_ARGUMENT  WrongArgument(__FILE__,__LINE__)
#define NO_MEMORY NoMemory(__FILE__,__LINE__)
#define ERR_WRITING_TO_FILE ErrWritingToFile(__FILE__,__LINE__)
#define ERR_OPEN_FILE ErrOpenFile(__FILE__,__LINE__)
#define ERR_CLOSE_FILE ErrCloseFile(__FILE__,__LINE__)
#define ERR_CREATE_DIRECTORY ErrCreateDirectory(__FILE__,__LINE__)
#define ERR_PICTURE_DATA ErrPictureData(__FILE__,__LINE__)
#define ERR_LOAD_ALPHABET ErrLoadAlphabet(__FILE__,__LINE__)
#define ERR_LOAD_REC6LIST ErrLoadRec6List(__FILE__,__LINE__)
#define ERR_UPDATE_ACTIVE_ALPHABET ErrUpdateActiveAlphabet(__FILE__,__LINE__)

#define PAGE_NOT_LOADED ErrPageNotLoaded(__FILE__,__LINE__)
#define OBJECT_NOT_FOUND ErrObjectNotFound(__FILE__,__LINE__)
#define POSSIBLE_LOSS_OF_DATA ErrPossibleLossOfData(__FILE__,__LINE__)
#define ASSERT assert

#define NEW_LINE {if(!NewLine()) return FALSE;}
#define ONE_CHAR(a) {if(!OneChar(a)) return FALSE;}
#define PUT_STRING(a) {if(!PutString((char*)a)) return FALSE;}
#define PUT_SPACES(a) {if(!PutSpaces((long)a)) return FALSE;}

#define WORDS_CONTROL(a) {if(!WordsControl(a)) return FALSE;}
#define IS_LETTER(c) IsLetter((Byte)c)
#define INIT_MEMORY(a,b) {if(!InitMemory(a,b)) return FALSE;}
#define CHECK_MEMORY(a) {if(gMemCur+(a)>gMemEnd)\
						{NO_MEMORY; return FALSE;}}

//*****************************************************************
// ���������� ������.
#ifdef __ROUT_DLL__
	#define EXTERN
	#define VAL(a) = a
	#define VAL2(a,b) = {a,b}
#else
	#define EXTERN extern
	#define VAL(a)
	#define VAL2(a,b)
#endif

//*****************************************************************
// ������� �� CFIO
EXTERN FNCFIOAllocMemory		CFIO_Alloc		VAL(0);
EXTERN FNCFIOReAllocMemory		CFIO_ReAlloc	VAL(0);
EXTERN FNCFIOLockMemory			CFIO_Lock		VAL(0);
EXTERN FNCFIOUnlockMemory		CFIO_Unlock		VAL(0);
EXTERN FNCFIOFreeMemory			CFIO_Free		VAL(0);
EXTERN FNCFIOOpenFreeFile		CFIO_Open		VAL(0);
EXTERN FNCFIOCloseFreeFile		CFIO_Close		VAL(0);
EXTERN FNCFIOWriteToFile		CFIO_Write		VAL(0);
EXTERN FNCFIOSeekFilePointer	CFIO_Seek		VAL(0);

//*****************************************************************
// ��� ���������� ������
EXTERN char *gFile	VAL(0);	// ��� ����� CPP �� __FILE__
EXTERN long gLine	VAL(0);	// ����� ������ �� __LINE

// ���������� ����� ��� �������� ������������ ������
EXTERN long gROUT_Option1	VAL(0);

// ��������� ������������� � ��� ��� ������
EXTERN Word16	gwHighRC_rout	VAL(0);
EXTERN Word16   gwLowRC_rout    VAL(0);
EXTERN HANDLE   ghStorage_rout	VAL(NULL);
EXTERN HANDLE   ghInst_rout	VAL(NULL);

// ���� �������������, ��. lang_def.h
EXTERN long gLanguage		VAL(-1);

// ��� ������������ Windows
EXTERN BOOL gWinFrench		VAL(FALSE);

// ������, ��. enum ROUT_FMT
EXTERN long gFormat			VAL(0);

// ������� ���������, ��. enum ROUT_CODE
EXTERN long gActiveCode		VAL(ROUT_CODE_ANSI);

// �������� ������� �������������
EXTERN Byte *gActiveCodeTable	VAL(NULL);

// ��������� �� ����� ����� � ��������� ��������
EXTERN BOOL gPreserveLineBreaks VAL(FALSE);

// �������������� ������
EXTERN char gBadChar		VAL('~');

// ����������� ����� ������, ���������� ��� ���������
EXTERN Handle gOwnMemory		VAL(NULL);
EXTERN long gOwnMemorySize	VAL(16384);

// ������� ������: ������� ��� ����.
// � ������ ������ � � ����� ��������� ������� ��� ���������.
EXTERN long gBumperSize	VAL(16);	// ����� �������
EXTERN Byte *gMemStart	VAL(0);		// ������ ������
EXTERN Byte *gMemEnd	VAL(0);		// ����� ������� ������
EXTERN Byte *gMemCur	VAL(0);		// ������� ����� ������

// ��������� �������������, ����������� �� REC6.DAT
// ��� ���������� � ����������.
EXTERN long gCountTigerToUserCharSet	VAL(0);
EXTERN BYTE **gTigerToUserCharSet VAL({0});	// [3][128]; // SPELABC.C

// ��� ��������
EXTERN BOOL langUzbek	VAL(FALSE);
EXTERN BOOL langKaz		VAL(FALSE);

// ����� ������
#if defined(_WIN32)
EXTERN char gEOL[4]		VAL2(0x0d,0x0a);
#else
EXTERN char gEOL[4]             VAL2(0x0a, 0x00);
#endif

// ��� �������� ��� ���������� .tif ��� .fed;
// ����� �������� ��� �� �������� ����
EXTERN char gPageName[_MAX_PATH] VAL("PageName");

// ����������� ��������
EXTERN Handle gPageHandle		VAL(0);

// �������� ���� ��������� ����
EXTERN BOOL gPageLoadedByMe		VAL(FALSE);

// ��������� ������ ��������.
// ������ Browse.cpp.

// ������
EXTERN Handle gSectionHandle	VAL(0);
EXTERN long gHitSections		VAL(0);

// �������
EXTERN Handle gColumnHandle		VAL(0);
EXTERN long gHitColumns			VAL(0);

// �����
EXTERN Handle gFrameHandle		VAL(0);
EXTERN long gHitFrames			VAL(0);

// �������
EXTERN Handle gTableHandle		VAL(0);
EXTERN long gHitTables			VAL(0);

// ������ �������
EXTERN long gTableRows			VAL(0);
EXTERN long gTableCols			VAL(0);
EXTERN long gTableCells			VAL(0);
EXTERN long *gLogicalCells		VAL(0);

// ������ �������
EXTERN long gIndexTableRow		VAL(0);
EXTERN Handle gRowHandle		VAL(0);

// ������
EXTERN Handle gCellHandle		VAL(0);
EXTERN long gHitCells			VAL(0);
EXTERN long gIndexTableCol		VAL(0);
EXTERN long gIndexTableCell		VAL(0);

// �����
EXTERN Handle gParagraphHandle	VAL(0);
EXTERN long gHitParagraphs		VAL(0);

// ������
EXTERN Handle gLineHandle		VAL(0);
EXTERN long gHitLines			VAL(0);

// ����� ������ "�������" (TRUE) ��� "�������" (FALSE)
EXTERN BOOL gEdLineHardBreak	VAL(FALSE);

// ������
EXTERN Handle gCharHandle		VAL(0);

// ������� ������
EXTERN BOOL gEdCharHidden		VAL(FALSE);

// ���� ��� ������� ������
EXTERN Byte *gCharBack			VAL(NULL);

// �������� ��� �������
EXTERN ULONG gCharCode			VAL(0);

// ����� �����������
EXTERN struct letterEx *gAlt	VAL(NULL);

// ������� � ��������
EXTERN long gHitChars			VAL(0);
EXTERN long gHitPictures		VAL(0);

// ����� ������� �� ��������
EXTERN long gTargetObjectIndex	VAL(0);
EXTERN Handle gTargetObjectHandle VAL(0);

// ������ ��������
EXTERN long gSizeAlphabet		VAL(0);

// ��������� (������ "���...")
EXTERN Byte gUpper[256]			VAL({0});

// ��������  (������ "���...")
EXTERN Byte gLower[256]			VAL({0});

// ������� (������ "^...")
EXTERN Byte gVowels[256]		VAL({0});

// ������� ��������� � ����� (Words.cpp):
// ��� ����� (����������� �������)
#define CASE_UPPER	1	// ��������� �����
#define CASE_LOWER	2	// �������� �����
#define CASE_VOWEL	4	// ������� �����
#define CASE_DIGIT	8	// �����
EXTERN Byte gAlphabetTable[256]	VAL({0});

// ��������� ����� ������ � ������� ������
EXTERN Byte *gLastEOL			VAL(NULL);

// ������ �����
EXTERN Byte *gBegWord			VAL(NULL);

// ��������� ����� � �����
EXTERN Byte *gDefis				VAL(NULL);

// ��������� ��� �������� ����������� �������������
// ���������� ������. ������ TableText.cpp.

// ������������� ����� ������ ������
typedef struct {
	long ltext;			// ����� ������ ������
	Byte *text;			// ����� ������ ������
} LINE_TEXT;

// ��� ��������� ������������� ������ ��� �������
// ������������ ����� ������ ���������������
// ������������ ���������� ����� ������ � ����� �������:
EXTERN long gMaxTextLinesInOneTable	VAL(5000);

// ������ ������������ ����� ������:
EXTERN LINE_TEXT *gBegLineText	VAL(NULL);
EXTERN LINE_TEXT *gCurLineText	VAL(NULL);
EXTERN LINE_TEXT *gEndLineText	VAL(NULL);

// ���������� ������������� ������ � ����� ������ �������:
typedef struct {
	long lines;			// ���������� ����� ������ � ������
	long width;			// ������ ������ ( = ������������ �����
						// ����� ������ � ������ )
	LINE_TEXT *line;	// ���������� � ������� ������ � ������
	long row;			// � ����� ������ ������� ���������� ������
	long col;			// � ����� ������� ������� ���������� ������
} CELL_TEXT;

// ��������� �����, ����������� ��������� �� �������:
EXTERN CELL_TEXT *gTableText	VAL(NULL);

// ���������� ������� ������
EXTERN CELL_TEXT *gCellText		VAL(NULL);

// ������ ������� ��������� ����� �������
// (���������� � ��������� ������� �� ����� �������)
EXTERN long *gTableRowTops		VAL(NULL);

// ������ ������ ��������� ����� �������
// (���������� � ��������� ������� �� ����� �������)
EXTERN long *gTableRowBottoms	VAL(NULL);

// ����� ������ ������� (��� ������ ������)
EXTERN long gTableTextHeight	VAL(0);

// ����� ������ ������� (�� ������ �������)
EXTERN long gTableTextWidth		VAL(0);

// ������ ����� ������� �������. ������������ ��� ������
// ������� ��� �������� ������ �����, ������������
// � ������ ������� �������.
EXTERN long *gTableColWidths	VAL(NULL);

// ������ ����� ��������� ������� �������
// (���������� � ��������� �������� �� ������ ���� �������)
EXTERN long *gTableColLefts		VAL(NULL);

// ������ ������ ��������� ������� �������
// (���������� � ��������� �������� �� ������ ���� �������)
EXTERN long *gTableColRights	VAL(NULL);

// ��������� ����� �������� �������
// �� ��������� � �� �����������
EXTERN long gTableTextIntervalBetweenCellsYY	VAL(0);
EXTERN long gTableTextIntervalBetweenCellsXX	VAL(4);

// �������� ������� �� ������ ������
EXTERN long gTableTextLeftIndent	VAL(0);

// ������� ��������� ����������
EXTERN long gXpos				VAL(0);
EXTERN long gYpos				VAL(0);

// ������ ������������:
// 0 - ����� ������ �������� �������
// 1 - ����� ��������� �������
// 2 - ����� ��������� ������� �������
EXTERN char gTableTextSeparators[8]	VAL("");

// ����� ���������� ������
EXTERN long gTableTextOptions		VAL(
				ROUT_TABLE_TEXT_INCLUDED |
				ROUT_TABLE_TEXT_ALIGN_COLUMNS |
				0);

// ��������
EXTERN long	gPictureNumber	VAL(0);
EXTERN Byte	*gPictureData	VAL(0);	// ����� DIB ������� ���������
EXTERN long	gPictureLength	VAL(0);	// ����� DIB ������� ���������

// ������ �������� � TIFF-����� � ��������
EXTERN EDSIZE gPictureSize	VAL({0});

// ������ �������� �� ������ � twips
EXTERN EDSIZE gPictureGoal	VAL({0});

// ��� �������� ��� �������� "<page>_files". ���� �� ����������.
EXTERN char gPageFilesFolder[256]	VAL("");

// ������� ���������
#define kMaxSizeAlphabet 63
EXTERN long gAT_sizeAlphabet[LANG_TOTAL] VAL({0});
EXTERN char gAT_upper[LANG_TOTAL][kMaxSizeAlphabet+1]	VAL({0});
EXTERN char gAT_lower[LANG_TOTAL][kMaxSizeAlphabet+1]	VAL({0});
EXTERN char gAT_vowels[LANG_TOTAL][kMaxSizeAlphabet+1] VAL({0});

//*****************************************************************
// ����� ���������� ������
#undef EXTERN
#undef VAL
#undef VAL2
//*****************************************************************
// Rout_DLL.cpp

Handle MyAlloc(Word32 dwSize, Word32 dwFlag);
Handle MyReAlloc(Handle hMem,
				Word32 dwSize,
				Word32 dwFlag);
Handle MyLock(Handle hMem);
Bool32 MyUnlock(Handle hMem);
Bool32 MyFree(Handle hMem);

Handle MyOpen(char * lpName, Word32 dwFlag);
Bool32 MyClose(Handle hFile, Word32 dwFlag=0);
Word32 MyWrite(Handle hFile,
			   char * lpData,
			   Word32 dwSize);
Word32 MySeek(Handle hFile, Word32 dwBytes, Word32 dwFrom);
void MyDebugPrint(char *format,...);
void ClearError();
void NotImplemented(char *file, long line);
void WrongArgument(char *file, long line);
void NoMemory(char *file, long line);

void ErrOpenFile(char *file, long line);
void ErrWritingToFile(char *file, long line);
void ErrCloseFile(char *file, long line);
void ErrPageNotLoaded(char *file, long line);
void ErrObjectNotFound(char *file, long line);
void ErrPossibleLossOfData(char *file, long line);
void ErrPictureData(char *file, long line);
void ErrLoadAlphabet(char *file, long line);
void ErrLoadRec6List(char *file, long line);
void ErrUpdateActiveAlphabet(char *file, long line);

BOOL InitMemory(Byte *memStart, long sizeMem);
BOOL SetTableTextSeparators(char* s);

//*****************************************************************
// CodeTables.cpp
void ResetCodeTables();
BOOL UpdateActiveCodeTable();
long GetCodePage();

//*****************************************************************
// Rout.cpp
BOOL SetLanguage(long language);
BOOL SetFormat(long format);
BOOL SetActiveCode(long code);
long BrowseObjects(ULONG targetIndex);
long BrowseTables(ULONG targetIndex);

//*****************************************************************
// Browse.cpp

// �������, ���������� ��� ������ �������� ��� ������� �������
typedef BOOL (*FNROUT_BrowseFunction)(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			);

// ����� ��������
BOOL BrowsePage(FNROUT_BrowseFunction BrowseFunction,
				BOOL wantSkipTableCells,
				BOOL wantSkipParagraphs
				);

// ����� ����� �������
BOOL BrowseCells(FNROUT_BrowseFunction BrowseFunction);

// ����� �������, �������� ����� �����, � �����
// ��������� � �������� ���������
BOOL BrowseTable(FNROUT_BrowseFunction BrowseFunction);

// ����� �������, ������ � �������
// � ������������ ������� (�������, ������, ������)
BOOL BrowseParagraphs(Handle hParentObject,
			FNROUT_BrowseFunction BrowseFunction,
			BOOL wantSkipTableCells,
			BOOL wantSkipParagraphs
			);

typedef enum {
	BROWSE_PAGE_START = 1,
	BROWSE_PAGE_END,		// 2

	BROWSE_SECTION_START,	// 3
	BROWSE_SECTION_END,		// 4

	BROWSE_COLUMN_START,	// 5
	BROWSE_COLUMN_END,		// 6

	BROWSE_FRAME_START,		// 7
	BROWSE_FRAME_END,		// 8

	BROWSE_TABLE_START,		// 9
	BROWSE_TABLE_END,		// 10

	BROWSE_ROW_START,		// 11
	BROWSE_ROW_END,			// 12

	BROWSE_CELL_START,		// 13
	BROWSE_CELL_END,		// 14

	BROWSE_PARAGRAPH_START,	// 15
	BROWSE_PARAGRAPH_END,	// 16

	BROWSE_LINE_START,		// 17
	BROWSE_LINE_END,		// 18

	BROWSE_CHAR,			// 19

	BROWSE_PICTURE			// 20

} BROWSE_REASON;

//*****************************************************************
// Text.cpp
BOOL MakeText();
BOOL NewLine();
BOOL OneChar(Handle charHandle);
BOOL PutString(char *s);
BOOL PutSpaces(long lth);

//*****************************************************************
// Words.cpp
BOOL IsLetter(Byte c);
BOOL IsEOL(Byte c);
BOOL WordsControl(long reason);
BOOL WordEnd();

//*****************************************************************
// HTML.cpp
BOOL MakeHTML();

//*****************************************************************
// �� ���� �� ������� � CED.H (�� EDP.H � EDFILE.H)
#define FONT_DBLUNDERLINED 1 // ������������ ������� ������
#define FONT_HIDDEN		   2 // �������
#define FONT_BOLD          4 // ������
#define FONT_LIGHT         8
#define FONT_ITALIC       16 // ���������
#define FONT_PROTECT      32 // ����������
#define FONT_UNDERLINE    64 // ������������
#define FONT_STRIKE		 128 // �������������
#define FONT_SUPER		 256 // ������� ������
#define FONT_SUB		 512 // ������ ������
#define FONT_FOOTNOTE	1024 // ������

#define ALIGN_LEFT		2
#define ALIGN_RIGHT		4
#define ALIGN_CENTER	8
#define ALIGN_MASK		(ALIGN_LEFT | ALIGN_RIGHT | ALIGN_CENTER)

//*****************************************************************
// TableText.cpp
BOOL MakeTableText();
BOOL TableText_Prepare();
BOOL TableText_Delete();

// ����� ����������� ������������� �������:
typedef enum {
	BROWSE_TABLE_TEXT_TABLE_START = 1,
	BROWSE_TABLE_TEXT_TABLE_END,

	BROWSE_TABLE_TEXT_RECORD_START,
	BROWSE_TABLE_TEXT_RECORD_END,

	BROWSE_TABLE_TEXT_STRING

} BROWSE_TABLE_TEXT_REASON;

// �������, ���������� ��� ������ �����������
// ������������� �������
typedef BOOL (*FNROUT_BrowseTableTextFunction)(
				long reason // ��. enum BROWSE_TABLE_TEXT_REASON
				);

BOOL BrowseTableText(FNROUT_BrowseTableTextFunction
						BrowseTableTextFunction);

//*****************************************************************
// TableDBF.cpp
BOOL MakeTableDBF();

//*****************************************************************
// Pictures.cpp

// �������� �������� �� �����������
BOOL PictureFromChar(Handle charHandle);

// ������� ����� �������� �� �����������
long GetPictureNumber(Handle charHandle);

// �������� �������� � BMP-����
BOOL WritePictureToBMP_File(
				Byte *pDIB,	   // ����� DIB ������� ���������
				long lenDIB,   // ����� DIB ������� ���������
				char *filename // ��� �����
				);

//*****************************************************************
