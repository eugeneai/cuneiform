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
#ifndef RLING_SECONDARY
  #define __RLING__
#else
  #define __RLINGS__
#endif

#include <windows.h>

#include "resource.h"
#include "RLControl.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ��� ������ ����� (������ ��� ������)   
#if !defined ( RLING_SECONDARY ) //& defined (RLING_MASTER)
  #define RLING_SECONDARY
  #include "CRLing.h"
  #undef RLING_SECONDARY
#endif
#include "CRLing.h"
//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
Word16            gwHeightRC = 0;
Word16            gwLowRC = 0;
Handle            ghStorage = NULL;
Handle            ghInst =  NULL;
CRLControl *      Control = NULL;
///////////////////////////////////////////////////////////////////////////////////
void SetReturnCode(Word16 rc);
Word16 GetReturnCode();
///////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY DllMain( HINSTANCE hModule, 
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
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_Init(Word16 wHeightCode,Handle hStorage)
#else
RLINGS_FUNC(Bool32) RLINGS_Init(Word16 wHeightCode,Handle hStorage)
#endif 
{
	gwHeightRC = wHeightCode;
	
	Control = new CRLControl;

	if ( Control )
#if defined ( __RLING__ )
		return RLINGS_Init(wHeightCode, hStorage);
#else
		return TRUE;
#endif

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32)RLING_Done()
#else
RLINGS_FUNC(Bool32)RLINGS_Done()
#endif
{
	delete Control;

#if defined ( __RLING__ )
		return RLINGS_Done();
#else
		return TRUE;
#endif
}
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Word32) RLING_GetReturnCode()
#else
RLINGS_FUNC(Word32) RLINGS_GetReturnCode()
#endif
{
	if ( !gwLowRC )
		return 0;

#if defined ( __RLING__ )
	if ( gwLowRC == IDS_RLING_ERR_NO )
		return RLINGS_GetReturnCode();
#endif
	
	return (Word32)(gwHeightRC<<16)|(gwLowRC - IDS_RLING_ERR_NO);
}
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Int8 *) RLING_GetReturnString(Word32 dwError)
#else
RLINGS_FUNC(Int8 *) RLINGS_GetReturnString(Word32 dwError)
#endif
{
	Word16 rc = (Word16)(dwError & 0xFFFF) + IDS_RLING_ERR_NO;
	static Int8 szBuffer[512];

	if( dwError >> 16 != gwHeightRC)
		gwLowRC = IDS_RLING_ERR_NOTIMPLEMENT;

	if( rc >= IDS_RLING_ERR_NO )
		LoadString((HINSTANCE)ghInst,rc,(char *)szBuffer,sizeof(szBuffer));
	else
		return NULL;

	return szBuffer;
}
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
  #define CASE_FUNCTION(a)	case RLING_FN_##a:	*(FNRLING##a *)pData = RLING_##a; break
#else
  #define CASE_FUNCTION(a)	case RLINGS_FN_##a:	*(FNRLINGS##a *)pData = RLINGS_##a; break
#endif
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_GetExportData(Word32 dwType, void * pData)
#else
RLINGS_FUNC(Bool32) RLINGS_GetExportData(Word32 dwType, void * pData)
#endif
{
	Bool32 rc = TRUE;

	gwLowRC = 0;


	switch(dwType)
	{
	CASE_FUNCTION(IsDictonaryAvailable);
	CASE_FUNCTION(LoadDictonary);
	CASE_FUNCTION(LoadSecDictonary);
	CASE_FUNCTION(UnloadDictonary);
	CASE_FUNCTION(UnloadSecDictonary);
	CASE_FUNCTION(LoadUserDictonary);
	CASE_FUNCTION(LoadSecUserDictonary);
	CASE_FUNCTION(UnloadUserDictonary);
	CASE_FUNCTION(UnloadSecUserDictonary);
	CASE_FUNCTION(CheckWord);
	CASE_FUNCTION(CheckSecWord);
	CASE_FUNCTION(CheckED);
	CASE_FUNCTION(CheckSecED);
    /*
	CASE_FUNCTION(CorrectWord);
	CASE_FUNCTION(CorrectSecWord);
	CASE_FUNCTION(CorrectHypWord);
	CASE_FUNCTION(CorrectSecHypWord);
	CASE_FUNCTION(GetCorrectedRectElement);
	CASE_FUNCTION(GetSecCorrectedRectElement);
	CASE_FUNCTION(GetCorrectedVersElement);
	CASE_FUNCTION(GetSecCorrectedVersElement);
	*/
	default:
		*(Handle *)pData = NULL;
		gwLowRC = IDS_RLING_ERR_NOTIMPLEMENT;
		rc = FALSE;
	}

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_SetImportData(Word32 dwType, void * pData)
#else
RLINGS_FUNC(Bool32) RLINGS_SetImportData(Word32 dwType, void * pData)
#endif
{
	BOOL rc = FALSE;
	gwLowRC = IDS_RLING_ERR_NOTIMPLEMENT;

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
void SetReturnCode(Word16 rc)
{
	if ( rc == IDS_RLING_ERR_NO || gwLowRC == IDS_RLING_ERR_NO )
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