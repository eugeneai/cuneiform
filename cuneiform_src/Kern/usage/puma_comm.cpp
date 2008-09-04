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

/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  18.12.00                                                    */
/*  ����       :  'Pum_COMM.CPP'                                              */
/*  ���������� :  ���������� � ������ ����������� �������� ������� (PUMA)     */
/*                ���� ������������ � �������������� ����� ���� ���������     */
/*                ��� ������� ������� �����/������.                           */
/*  ���������� :  ����� � ��������.                                           */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
/*#include <windows.h>*/
/*  interface our-other  */
#include "dpuma.h"
/*  interface my        */
#define _AM_Comm_
#include "am_comm.h"  // Own functions
#include "un_err.h"
/*------------own objects-----------------------------------------------------*/
static Word32 wRltMainCode;
#define     MaxResCodes   3
static FILE *fRes[MaxResCodes];
static int   cRes[MaxResCodes];
/*----------------------------------------------------------------------------*/
FILE * MyOpenFile (int k, char *pFile)
{
	char Name[256], a[256];
	strcpy (Name, pFile);
	a[0] = '0' + (char)k;
	a[1] = '\0';
	strcat (Name, a);
	strcpy (a, ".txt");
	strcat (Name, a);
	return fopen (Name, "a");
}
/*----------------------------------------------------------------------------*/
int AM_OpenRes_rv_fte (int Code, char *pFile)
{
	int i, k;
	for (i=0, k=-1; i<MaxResCodes; i++)
	{
		if ((fRes[i]!=NULL)&&(cRes[i]==Code))
			return RV_TRUE;
		if ((fRes[i]!=NULL)||(cRes[i]!=-1))
			continue;
		k = i;
		break;
	}
	if (k==-1)
		return RV_EMPTY;
	fRes[k] = MyOpenFile (k, pFile);
	if (fRes[k]==NULL)
		return RV_FALSE;
	cRes[k] = Code;
	return RV_TRUE;
}
/*----------------------------------------------------------------------------*/
int AM_SaveRes_rv_fte (int Code, char *pFile)
{
	int i, k;
	for (i=0, k=-1; i<MaxResCodes; i++)
	{
		if ((fRes[i]==NULL)||(cRes[i]!=Code))
			continue;
		k = i;
		break;
	}
	if (k==-1)
		return RV_FALSE;
	fclose (fRes[k]);
	fRes[k] = MyOpenFile (k, pFile);
	if (fRes[k]==NULL)
		return RV_FALSE;
	return RV_TRUE;
}
/*----------------------------------------------------------------------------*/
int AM_WriteRes_rv_fte (int Code, const char *pStr)
{
	int i, k;
	for (i=0, k=-1; i<MaxResCodes; i++)
	{
		if ((fRes[i]==NULL)||(cRes[i]!=Code))
			continue;
		k = i;
		break;
	}
	if (k==-1)
		return RV_FALSE;
	fprintf (fRes[k], "%s", pStr);
	return RV_TRUE;
}
/*----------------------------------------------------------------------------*/
void CloseAllRes ()
{
	int i;
	for (i=0; i<MaxResCodes; i++)
	{
		if (fRes[i]==NULL)
			continue;
		fclose (fRes[i]);
		fRes[i] = NULL;
		cRes[i] =-1;
	}
}
/*----------------------------------------------------------------------------*/
Bool AM_InitComm (Word16 wRltOwnCode)
{
	int i;
	wRltMainCode = (Word32)(wRltOwnCode<<16);
	LDPUMA_Init(0,NULL);
	AM_Console = (FN_AM_Console)LDPUMA_Console;
	AM_ConsolN = (FN_AM_Console)LDPUMA_ConsoleN;
	AM_MessageBoxOk = LDPUMA_MessageBoxOk;
	for (i=0; i<MaxResCodes; i++)
	{
		fRes[i] = NULL;
		cRes[i] = -1;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*/
void AM_DoneComm ()
{
	Bool ret;
	ret = LDPUMA_Done();
	return;
}
/*----------------------------------------------------------------------------*/
Word32 AM_GetOperCode (Word16 wLocCode)
{
	return (wRltMainCode|(wLocCode<<16));
}
/*----------------------------------------------------------------------------*/
void AM_RegiVert (Handle owner, char *lpName, Handle parent)
{
	LDPUMA_Registry (owner, lpName, parent);
}
/*----------------------------------------------------------------------------*/
void AM_RegiVari (Handle owner, char *lpName, void *lpData, char *lpType)
{
	LDPUMA_RegVariable (owner, lpName, lpData, lpType);
}
/*----------------------------------------------------------------------------*/
void AM_RegiHelp (Handle owner, char *lpName, Bool32 bAppend)
{
	LDPUMA_RegistryHelp (owner, lpName, bAppend);
}
/*----------------------------------------------------------------------------*/
Word32  AM_WaitUserInput (Handle owner, Handle wnd)
{
	return LDPUMA_WaitUserInput (owner, wnd);
}
/*----------------------------------------------------------------------------*/
void  AM_DrawLine (Handle wnd, Point16 *start, Point16 *end, Int32 skew, Word32 rgb, Int16 pen, Word32 key)
{
	LDPUMA_DrawLine (wnd, start, end, skew, rgb, pen, key);
}
/*----------------------------------------------------------------------------*/
void  AM_DrawRect (Handle wnd, Rect16 *pRc, Int32 skew, Word32 rgb, Int16 pen, Word32 key)
{
	LDPUMA_DrawRect (wnd, pRc, skew, rgb, pen, key);
}
/*----------------------------------------------------------------------------*/
void  AM_DeleteLines (Handle wnd, Word32 key)
{
	LDPUMA_DeleteLines (wnd, key);
}
/*----------------------------------------------------------------------------*/
void  AM_DeleteRects (Handle wnd, Word32 key)
{
	LDPUMA_DeleteRects (wnd, key);
}
/*----------------------------------------------------------------------------*/
Bool16 AM_Skip (Handle owner)
{
	return LDPUMA_Skip (owner);
}
/*----------------------------------------------------------------------------*/
Handle AM_CreateWindow (const char *lpTitle, void *lpDib)
{
	return LDPUMA_CreateWindow (lpTitle, lpDib);
}
/*----------------------------------------------------------------------------*/
Handle AM_GetWindowHandle (char *name)
{
	return LDPUMA_GetWindowHandle (name);
}
/*----------------------------------------------------------------------------*/
char * AM_GetFileName (Handle wnd)
{
	return LDPUMA_GetFileName (wnd);
}
/*----------------------------------------------------------------------------*/
/*void AM_Console (const char *message, ...)
{
	int rc = 0;
	if (LDPUMA_Console)
	{
		va_list marker;
		va_start (marker, message);
		rc = LDPUMA_Console (message, marker);
		va_end (marker);
	}
//	return rc;
}*/
/*----------------------------------------------------------------------------*/
