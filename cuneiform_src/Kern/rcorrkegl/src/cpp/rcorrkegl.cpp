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

// RCorrKegl.cpp : Defines the entry point for the DLL application.
//

#include <string.h>
#include "stdafx.h"
#include "rcorrkegl.h"
#include "resource.h"
#include "dpuma.h"
#include "compat_defs.h"

Bool32 CorrectKegl(Int32 version);
void kegl_snap_init();

Word16 gwHeightRC = 0;
Word16 gwLowRC = 0;
Bool32 snap_enable = TRUE;
Bool32 exit_enable = FALSE;
Bool32 gbFax100 = FALSE;
Word8  language=3;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

RCK_FUNC(Bool32) RCORRKEGL_Init(Word16 wHeightCode,HANDLE hStorage)
{
    gwHeightRC = wHeightCode;
	snap_enable = TRUE;
	exit_enable = FALSE;

	kegl_snap_init();
	LDPUMA_Init(0,NULL);

	return TRUE;
}

RCK_FUNC(Bool32) RCORRKEGL_Done()
{
	LDPUMA_Done();

	return TRUE;
}

RCK_FUNC(Word32) RCORRKEGL_GetReturnCode()
{
	if(gwLowRC == RCORRKEGL_ERR_NO) 
		return 0;

	return (gwHeightRC<<16)|(gwLowRC-RCORRKEGL_ERR_MIN);
}

RCK_FUNC(Int8*) RCORRKEGL_GetReturnString(Word32 dwError)
{
	Word16 rc = (Word16)((dwError & 0xFFFF) );
    static Int8 szBuffer[512];

    if (dwError >> 16 != gwHeightRC) gwLowRC = RCORRKEGL_ERR_NOTIMPLEMENT;

    if (rc > 0 && rc <= RCORRKEGL_ERR_MAX - RCORRKEGL_ERR_MIN)
		strcpy((char*)szBuffer, RCORRKEGL_error_name [rc]);
	else 
		return NULL;
		
	return szBuffer;
}

RCK_FUNC(Bool32) RCORRKEGL_SetImportData(Word32 dwType, void * pData)
{

  gwLowRC = RCORRKEGL_ERR_NO;
#define CASE_DATA(a,b,c)	case a: c = *(b *)pData; break
#define CASE_PDATA(a,b,c)	case a: c = (b)pData; break
	switch(dwType)
	{
	CASE_DATA(RCORRKEGL_Bool32_Fax100,Bool32,gbFax100);
	// 12.06.2002 E.P.
	CASE_DATA(RCORRKEGL_FNIMP_LANGUAGE,Word8,language);

	default:
    gwLowRC = RCORRKEGL_ERR_NOTIMPLEMENT;
		return FALSE;
	}
#undef CASE_DATA
#undef CASE_PDATA

return TRUE;
}

RCK_FUNC(Bool32) RCORRKEGL_CorrectKegl(Int32 version)
{
  return CorrectKegl(version);
}
