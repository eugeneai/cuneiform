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

#include "stdafx.h"
#if defined(__PUMA__)

#include <io.h>
#include <stdio.h>
#include "puma.h"
#include "tigerdef.h"

extern FNPROGRESS_START fnProgressStart;
extern FNPROGRESS_STOP  fnProgressStop;
extern FNPROGRESS_STEP  fnProgressStep;


#define PUMANAME     "APUMA.DLL"


static void ProgressStart( void )
{
    fnProgressStart();
	g_pRecognition->Fire_ProgressStart();
}
static void ProgressFinish( void )
{
    fnProgressStop();
	g_pRecognition->Fire_ProgressFinish();
}
static Bool32 ProgressStep( Word32 swStageNumber,const char* StageName, Word32 swPercent )
{
	USES_CONVERSION;
    return fnProgressStep(swStageNumber,(char *)StageName,swPercent) &
		(Bool32)g_pRecognition->Fire_ProgressStep(swStageNumber,T2OLE((char *)StageName),swPercent);
}


char * _GetVersion()
{
	return LPUMA_GetVersion();
}

short _GetLanguage()
{
	short rc = 0;

	rc = (short)LPUMA_GetLanguage();

	return rc;
}

Bool32 _SetSpecialProject(long nSpecPrj)
{
	Bool32 rc = 0;

	rc = (Bool32)LPUMA_SetSpecialProject((Word8)nSpecPrj);

	return rc;
}

void _SetLanguage(short newVal)
{
	LPUMA_SetLanguage((Word32)newVal);
}

long _Status()
{
	long rc = 0;
	rc = LPUMA_GetReturnCode();
	return rc;
}

char * _ErrorMessage(long rc)
{
	static char szStr[2048];
	sprintf(szStr,"<0x%08X>: %s",rc,LPUMA_GetReturnString((Word32)rc ));
	return szStr;
}


BOOL _Load(CRecognition * pThis)
{
	HINSTANCE hInstance = GetModuleHandle(PUMANAME);
	char szFullPath[_MAX_PATH];
	GetModuleFileName(hInstance,szFullPath,sizeof(szFullPath));
	char * p = strstr(strupr(szFullPath),PUMANAME);
	if(p)
		*p='\0';

	BOOL rc = LPUMA_Load(szFullPath);

	g_pRecognition = pThis;
	if(!rc)
	{
		g_pRecognition->SetError(_ErrorMessage(_Status()));
		return rc;
	}

	if(rc)
		LPUMA_SetProgressFunction(ProgressStart,ProgressStep,ProgressFinish);

	return rc;
}

void _Unload()
{
	LPUMA_Unload();
}


BOOL _Open(char * hDIB, char * FileName)
{
	BOOL rc = FALSE;

	_Close( );
	if(hDIB==0)
	{
		g_pRecognition->SetError(IDS_ERROR_DIBISNULL);
		return FALSE;
	}
	rc = LPUMA_XOpen(hDIB, FileName);
	return rc;
}

BOOL _Close()
{
	return LPUMA_XClose();
}

BOOL _Recognition()
{
return  _FinalRecognition();
}

BOOL _Save(void * hEdPage, char * lpFileName,long format, long code, Bool32 bAppend)
{
	BOOL rc = FALSE;

	LPUMA_SetBold(g_bBold);
	LPUMA_SetItalic(g_bItalic);
	LPUMA_SetSize(g_bSize);
	LPUMA_SetFormat(g_bFormat);
	LPUMA_SetSerifName(g_strSerifName);
	LPUMA_SetSansSerifName(g_strSansSerifName);
	LPUMA_SetCourierName(g_strCourierName);

	rc = LPUMA_Save(hEdPage, lpFileName,format,code,bAppend);
	if(!rc)
		g_pRecognition->SetError(_ErrorMessage(_Status()));

	return rc;
}

Word32 _SaveToMemory(Handle hEdPage, Int32 format, Int32 code, char * lpMem, Word32 size )
{
	BOOL rc = 0;

	LPUMA_SetBold(g_bBold);
	LPUMA_SetItalic(g_bItalic);
	LPUMA_SetSize(g_bSize);
	LPUMA_SetFormat(g_bFormat);
	LPUMA_SetSerifName(g_strSerifName);
	LPUMA_SetSansSerifName(g_strSansSerifName);
	LPUMA_SetCourierName(g_strCourierName);

	rc = LPUMA_SaveToMemory(hEdPage,format, code, lpMem, size);
	if(!rc)
		g_pRecognition->SetError(_ErrorMessage(_Status()));

	return rc;
}

BOOL _PageAnalysis(BOOL bUpdateCPAGE)
{
	BOOL rc = FALSE;

	LPUMA_SetSpeller(g_bSpeller);
	LPUMA_SetOneColumn(g_bOneColumn);
	LPUMA_SetFax100(g_bFax100);
	LPUMA_SetDotMatrix(g_bDotMatrix);
	LPUMA_SetPictures(g_nPicture);
	LPUMA_SetTables(g_nTable);

	rc = LPUMA_XPageAnalysis();
	if(!rc)
	{
		DWORD status = _Status();
		if(status)
			g_pRecognition->SetError(_ErrorMessage(status));
	}
	return rc;
}

BOOL _FinalRecognition()
{
BOOL rc = FALSE;

	LPUMA_SetSpeller(g_bSpeller);
	LPUMA_SetOneColumn(g_bOneColumn);
	LPUMA_SetFax100(g_bFax100);
	LPUMA_SetDotMatrix(g_bDotMatrix);
	LPUMA_SetPictures(g_nPicture);
	LPUMA_SetTables(g_nTable);
	LPUMA_SetFormatMode(g_nFormat);
	LPUMA_SetUnrecogChar(g_btUnrecogChar);

	LPUMA_SetBold(g_bBold);
	LPUMA_SetItalic(g_bItalic);
	LPUMA_SetSize(g_bSize);
	LPUMA_SetFormat(g_bFormat);
	LPUMA_SetSerifName(g_strSerifName);
	LPUMA_SetSansSerifName(g_strSansSerifName);
	LPUMA_SetCourierName(g_strCourierName);

	rc = LPUMA_XFinalRecognition();
	if(!rc)
	{
		DWORD status = _Status();
		if(status)
			g_pRecognition->SetError(_ErrorMessage(status));
	}

return rc;
}

long	_EnumFormats(long prev)
{
	return LPUMA_EnumFormats((Int32)prev);
}

long	_EnumCodes(long f,long prev)
{
	return (long)LPUMA_EnumCodes((Int32)f,(Int32)prev);
}

short  _EnumLanguage(short PrevLang)
{
	short rc = -1;
	rc = (short)LPUMA_EnumLanguages((Int32)PrevLang);
	return rc;
}

long	_EnumFormatMode(long nPrev)
{
	long rc = -1;
	rc = LPUMA_EnumFormatMode(nPrev);
	return rc;
}

long	_EnumTableMode(long nPrev)
{
	long rc = -1;
	rc = LPUMA_EnumTable(nPrev);
	return rc;
}

long	_EnumPictureMode(long nPrev)
{
	long rc = -1;
	rc = LPUMA_EnumPicture(nPrev);
	return rc;
}

BOOL	_GetRotateDIB(long * phDIB, long * x0, long * y0)
{
	BOOL rc = FALSE;
	Point32 p = {0,0};

	rc = LPUMA_XGetRotateDIB((void**)phDIB,&p);

	*x0 = p.x;
	*y0 = p.y;

	return rc;
}

void	_RenameImageName(char * FileName)
{
	LPUMA_RenameImageName(FileName);
}

#endif
