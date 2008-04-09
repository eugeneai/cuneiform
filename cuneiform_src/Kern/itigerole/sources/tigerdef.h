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

#ifndef __TIGERDEF_H__
#define __TIGERDEF_H__

#ifdef __EXTERN_INIT__
	#define EXTERN
	#define VAL(a) = a
	#define VAL2(a,b) = { a,b }
#else
	#define EXTERN extern 
	#define VAL(a) 
	#define VAL2(a,b)
#endif

#include "Tiger.h"
#include "Recognition.h"
#include "cpage.h"
#include "dpuma.h"


#if defined(__TIGER__)
	#define _ENGINE_	TIGER
#elif defined(__PUMA__)
	#define _ENGINE_	PUMA
#else
	#error Unknown defined: __TIGER__ or __PUMA__ !
#endif

EXTERN UINT g_uiLanguage				VAL(7);

EXTERN Bool32 g_bSpeller					VAL(TRUE);
EXTERN Bool32 g_bOneColumn				VAL(FALSE);
EXTERN Bool32 g_bFax100					VAL(FALSE);
EXTERN Bool32 g_bDotMatrix				VAL(FALSE);

EXTERN char g_strUserDictName[_MAX_PATH] VAL("");

EXTERN Bool32 g_bBold						VAL(TRUE);
EXTERN Bool32 g_bItalic					VAL(TRUE);
EXTERN Bool32 g_bSize						VAL(TRUE);
EXTERN Bool32 g_bFormat					VAL(TRUE);

EXTERN char g_strSerifName[_MAX_PATH]		VAL("Times New Roman");
EXTERN char g_strSansSerifName[_MAX_PATH] VAL("Arial");
EXTERN char g_strCourierName[_MAX_PATH]	VAL("Courier New");

EXTERN Word32 g_nPicture				VAL(1);
EXTERN Word32 g_nTable					VAL(1);
EXTERN Word32 g_nFormat					VAL(1);

EXTERN char g_strFileName[_MAX_PATH]	VAL("");
EXTERN char g_strTempEdName[_MAX_PATH]	VAL("temp.ed");
EXTERN char g_btUnrecogChar				VAL('~');

EXTERN CRecognition * g_pRecognition	VAL(NULL);

// used by __TIGER__ mode
EXTERN Handle	g_hPage					VAL(NULL);
EXTERN char * g_pDIB					VAL(NULL);
// end
EXTERN CRITICAL_SECTION Critical;


/////////////////////////////////////////////////////////////
typedef int (*FNPROGRESS_STEP)(unsigned long dStep, char * lpStepName, unsigned long dPercent);
typedef int (*FNPROGRESS_START)();
typedef int (*FNPROGRESS_STOP)();

char *  _GetVersion( void );
short	_GetLanguage( void );
Bool32  _SetSpecialProject(long nSpecPrj);
void	_SetLanguage(short newVal);
long	_Status( void );
char *	_ErrorMessage(long rc);
BOOL	_Load( CRecognition * pThis );
void	_Unload( void );
short	_EnumLanguage(short PrevLang);
long	_EnumFormatMode(long nPrev);
long	_EnumTableMode(long nPrev);
long	_EnumPictureMode(long nPrev);

BOOL	_Open(char * pDIB, char * FileName);
BOOL	_Close( );
//BOOL	_Recognition( );
BOOL	_Save(void * hEdPage,  char * lpFileName,long format, long code, Bool32 bAppend);
BOOL	_PageAnalysis(BOOL bUpdateCPAGE );
BOOL	_FinalRecognition( );
long	_EnumFormats(long prev);
long	_EnumCodes(long format,long prev);
BOOL	_GetRotateDIB(long * phDIB, long * x0, long * y0);
void	_RenameImageName(char * FileName);
Word32	_SaveToMemory(Handle hEdPage, Int32 format, Int32 code, char * lpMem, Word32 size );



///////////////////////////////////////////////////////////////
char *	_GetTempPath( void );


#endif
