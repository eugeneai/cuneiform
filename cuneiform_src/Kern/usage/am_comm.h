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
/*  ��������   :  06.09.00                                                    */
/*  ����       :  'AM_COMM.H'                                                 */
/*  ���������� :  ��������� ���� ������������ � �������������� ����� ����     */
/*                ��������� ��� ������� ������� �����/������.                 */
/*  ���������� :  ����� � �������� � ������.                                  */
/*----------------------------------------------------------------------------*/
#include "cttypes.h"
#ifndef Handle
	#define Handle void *
#endif
typedef int (*FN_AM_Console) (const char * lpFormat,...);
typedef int (*FN_AM_ConsolN) (const char * lpFormat,...);
typedef void (*FN_AM_MessageBoxOk) (const char * lpFormat,...);
/*------------own functions---------------------------------------------------*/
int AM_OpenRes_rv_fte (int Code, char *pFile);
int AM_SaveRes_rv_fte (int Code, char *pFile);
int AM_WriteRes_rv_fte (int Code, const char *pStr);
void CloseAllRes ();
Bool   AM_InitComm (Word16 wRltOwnCode);
void AM_DoneComm ();
Word32 AM_GetOperCode (Word16 wLocCode);
void   AM_RegiVert (Handle owner, char *lpName, Handle parent);
void   AM_RegiVari (Handle owner, char *lpName, void *lpData, char *lpType);
void AM_RegiHelp (Handle owner, char *lpName, Bool32 bAppend);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Word32 AM_WaitUserInput (Handle owner, Handle wnd);
void   AM_DrawLine (Handle wnd, Point16 *start, Point16 *end, Int32 skew, Word32 rgb, Int16 pen, Word32 key);
void   AM_DrawRect (Handle wnd, Rect16 *pRc, Int32 skew, Word32 rgb, Int16 pen, Word32 key);
void   AM_DeleteLines (Handle wnd, Word32 key);
void   AM_DeleteRects (Handle wnd, Word32 key);
Bool16 AM_Skip (Handle owner);
#ifdef _AM_Comm_
	FN_AM_Console AM_Console;
	FN_AM_ConsolN AM_ConsolN;
	FN_AM_MessageBoxOk AM_MessageBoxOk;
#else
	extern FN_AM_Console AM_Console;
	extern FN_AM_ConsolN AM_ConsolN;
	extern FN_AM_MessageBoxOk AM_MessageBoxOk;
#endif
Handle AM_CreateWindow (const char *lpTitle, void *lpDib);
Handle AM_GetWindowHandle (char *name);
char * AM_GetFileName (Handle wnd);
/*----------------------------------------------------------------------------*/
