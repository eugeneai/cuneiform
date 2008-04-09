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

// ============================================================================
// Copyright (c) 1998 Cognitive Technology Ltd.
// Written by Peter Khlebutin
// This file creation date: 20.07.98
//
// dll_cpage.cpp : 
// ============================================================================
#define __CIMAGE__

#include <windows.h>

#include "resource.h"
#include "CTIDefines.h"
#include "CTIImage.h"

#include "CTIControl.h"

//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
Word16            gwHeightRC = 0;
Word16            gwLowRC =    0;
Handle            ghStorage =  NULL;
HINSTANCE         ghInst =     NULL;
CTIControl *      Control =    NULL;
Int32             InitCount =  0;
/////////////////////////////////////////
BOOL APIENTRY DllMain( HINSTANCE  hModule, 
                        DWORD ul_reason_for_call, 
                        LPVOID lpReserved )
{
    switch( ul_reason_for_call ) 
	{
    case DLL_PROCESS_ATTACH:
		ghInst = hModule;
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		break;
    }
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(Bool32) CIMAGE_Init(Word16 wHeightCode,Handle hStorage)
{
	gwHeightRC = wHeightCode;
	
	if ( !Control )
	{
		if ( !InitCFIOInterface(TRUE) )
		{
			SetReturnCode(IDS_CIMAGE_OTHER_DLL_NOT_INITIALIZED);
			return FALSE;
		}

		Control = new CTIControl;
	}

	if ( Control )
	{
		InitCount++;
		return TRUE;
	}

	SetReturnCode(IDS_CIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(Bool32) CIMAGE_Done()
{
	SetReturnCode(IDS_CIMAGE_ERR_NO);
	
	if ( Control )
	{
		if (--InitCount == 0)
		{
			delete Control;
			Control = NULL;
			InitCFIOInterface(FALSE);
		}
		return TRUE;
	}
	
	SetReturnCode(IDS_CIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(Word32) CIMAGE_GetReturnCode()
{
	if ( !gwLowRC )
		return 0;
	
	return (Word32)(gwHeightRC<<16)|(gwLowRC - IDS_CIMAGE_ERR_NO);
}
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(PInt8) CIMAGE_GetReturnString(Word32 dwError)
{
	Word16 rc = (Word16)(dwError & 0xFFFF) + IDS_CIMAGE_ERR_NO;
	static Char8 szBuffer[512];

	if( dwError >> 16 != gwHeightRC)
		gwLowRC = IDS_CIMAGE_ERR_NOTIMPLEMENT;

	if( rc >= IDS_CIMAGE_ERR_NO )
		LoadString(ghInst,rc,(char *)szBuffer,sizeof(szBuffer));
	else
		return NULL;

	return (PInt8)szBuffer;
}
//////////////////////////////////////////////////////////////////////////////////
//
#define CASE_FUNCTION(a)	case CIMAGE_FN_##a:	*(FNCIMAGE##a *)pData = CIMAGE_##a; break
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(Bool32) CIMAGE_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

	gwLowRC = 0;


	switch(dwType)
	{
	CASE_FUNCTION(WriteCallbackImage);
	CASE_FUNCTION(GetCallbackImage);
	CASE_FUNCTION(WriteDIB);
	CASE_FUNCTION(ReadDIB);
	CASE_FUNCTION(GetData);
	CASE_FUNCTION(GetDIBData);
	CASE_FUNCTION(ReplaceData);
	CASE_FUNCTION(GetImageInfo);
	CASE_FUNCTION(DeleteImage);
	CASE_FUNCTION(FreeCopedDIB);
	CASE_FUNCTION(FreeBuffers);
	CASE_FUNCTION(Reset);
	CASE_FUNCTION(AddReadCloseRects);
	CASE_FUNCTION(RemoveReadCloseRects);
	CASE_FUNCTION(AddWriteCloseRects);
	CASE_FUNCTION(RemoveWriteCloseRects);
	
	default:
		*(Handle *)pData = NULL;
		gwLowRC = IDS_CIMAGE_ERR_NOTIMPLEMENT;
		rc = FALSE;
	}

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
CIMAGE_FUNC(Bool32) CIMAGE_SetImportData(Word32 dwType, void * pData)
{
	BOOL rc = FALSE;
	gwLowRC = IDS_CIMAGE_ERR_NOTIMPLEMENT;

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
void SetReturnCode(Word16 rc)
{
	if ( rc == IDS_CIMAGE_ERR_NO || gwLowRC == IDS_CIMAGE_ERR_NO )
		gwLowRC = rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word16 GetReturnCode()
{
	return gwLowRC;
}
//////////////////////////////////////////////////////////////////////////////////
//end of file