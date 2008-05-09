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
// Written by Peter Khlebutin
// This file creation date: 20.07.98
//
// frmtdll.cpp : 
// ============================================================================

/*#include <windows.h>*/
#include "resource.h"
#define __RFRMT__
#define __RFRMT_EXTERN__
#include "rfrmt.h"
#include "dpuma.h"
#include "pumadef.h"
#include "rfrmt_prot.h"
#include "compat_defs.h"

//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
static Word16     gwHeightRC = 0;
static Word16     gwLowRC    = 0;
static HANDLE     ghStorage  = NULL;
static HINSTANCE  ghInst     = NULL;
Bool32     gbBold     = TRUE;
Bool32     gbItalic   = TRUE; 
Bool32     gbSize     = TRUE;
Word32     gnFormat	  = 1;    // 0 - �� �������������
							  // 1 - ������������� � �������� �  ���������
							  // 2 - ������ ������
char * gpSerifName	  = "MS Serif Cyr";
char * gpSansSerifName= "MS Sans Serif Cyr";
char * gpCourierName  = "Courier Cyr";
char   UnRecogSymbol  = '~';
Word32 gnLanguage = LANG_RUSENG;

/////////////////////////////////////////
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

///////////////////////////////////////////////////////////////
//Handle hUseCLine;

RFRMT_FUNC(Bool32) RFRMT_Init(Word16 wHeightCode,HANDLE hStorage)
{
 LDPUMA_Init(0,NULL);
 LDPUMA_Registry(&hDebugRoot,SNAP_ROOT_CONVERTERS,NULL);
 LDPUMA_Registry(&hDebugMy,"������� ��������������",hDebugRoot);

 LDPUMA_Registry(&hDebugKegl,"����� �� ��������",hDebugMy);
 LDPUMA_RegistryHelp(hDebugKegl,"��� ����� ������������� ��� ������������� ������� ����� ��� ��������������",FALSE);

 LDPUMA_Registry(&hDebugFrame,"��� ��������� ������",hDebugMy);
 LDPUMA_RegistryHelp(hDebugFrame,"��� ����� ������������� ��� �������������� ��������",FALSE);

 LDPUMA_Registry(&hDebugAlign,"������� ������������ ���������",hDebugMy);
 LDPUMA_RegistryHelp(hDebugAlign,"������� ������������ ���������",FALSE);

 LDPUMA_Registry(&hDebugLineTransfer,"������ �� ����������",hDebugMy);
 LDPUMA_RegistryHelp(hDebugLineTransfer,"������ �� ����������",FALSE);

 LDPUMA_Registry(&hDebugProfile,"������ ������� ������.",hDebugMy);
 LDPUMA_RegistryHelp(hDebugProfile,"������ ������� ������.",FALSE);
 LDPUMA_Registry(&hDebugProfStart,"������ ������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfStart,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfTable,"�������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfTable,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfCell,"������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfCell,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfTmp,"Tmp",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfTmp,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfEndTable,"����� �������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfEndTable,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfWrite,"������ �������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfWrite,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfWriteRow,"������ ������ �������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfWriteRow,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfWriteCell,"������ ������ �������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfWriteCell,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfWriteChar,"������ �������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfWriteChar,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hDebugProfEnd,"����� ������",hDebugProfile);
 LDPUMA_RegistryHelp(hDebugProfEnd,"������ ������� ������.",FALSE);

 LDPUMA_Registry(&hTest,"���� ������ ������ ��������",hDebugMy);
 LDPUMA_Registry(&hTestDIBData,"�������� �������� ��������",hTest);

 LDPUMA_Registry(&hTestTurn,"�������� �� 90\180",hTest);
 LDPUMA_Registry(&hTestRotate,"�������� �� ����� ����",hTest);
 
 LDPUMA_Registry(&hTestWriteMetafile,"������ � ��������",hTest);
 LDPUMA_Registry(&hTestGetMaskDIB,"��������� �������������� DIB",hTest);
 
 LDPUMA_Registry(&hTestWriteED,"������ � ED",hTest);
 LDPUMA_Registry(&hTestEnd,"� ����� �������",hTest);
 LDPUMA_Registry(&hTestDeleteImage,"�������� ��������� �����������",hTest);

// LDPUMA_Registry (&hUseCLine,"������ � ����������� �����", NULL);


 gwHeightRC = wHeightCode;

 return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RFRMT_FUNC(Bool32) RFRMT_Done()
{
 LDPUMA_Done();
 return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RFRMT_FUNC(Word32) RFRMT_GetReturnCode()
{
 Word32 rc = 0;
 
 if((gwLowRC - IDS_ERR_NO)>0)
	rc = (Word32)(gwHeightRC<<16)|(gwLowRC - IDS_ERR_NO);

 return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RFRMT_FUNC(Int8 *) RFRMT_GetReturnString(Word32 dwError)
{
 Word16 rc = (Word16)(dwError & 0xFFFF) + IDS_ERR_NO;
 static Int8 szBuffer[512];

 if( dwError >> 16 != gwHeightRC)
	gwLowRC = IDS_ERR_NOTIMPLEMENT;

 if( rc >= IDS_ERR_NO )
	LoadString(ghInst,rc,(char *)szBuffer,sizeof(szBuffer));
 else
	return NULL;

 return szBuffer;
}
//////////////////////////////////////////////////////////////////////////////////
//
RFRMT_FUNC(Bool32) RFRMT_GetExportData(Word32 dwType, void * pData)
{
 Bool32 rc = TRUE;

 gwLowRC = 0;

#define CASE_FUNCTION(a)	case RFRMT_FN##a:	*(FN##a *)pData = a; break
#define CASE_DATA(a,b,c)	case a: *(b *)pData = c; break

 switch(dwType)
 {
    CASE_FUNCTION(RFRMT_Formatter);
	CASE_FUNCTION(RFRMT_SaveRtf);
	CASE_DATA(RFRMT_Bool32_Bold,Bool32,gbBold);
	CASE_DATA(RFRMT_Bool32_Italic,Bool32,gbItalic);
	CASE_DATA(RFRMT_Bool32_Size,Bool32,gbSize);
	CASE_DATA(RFRMT_Word8_UnRecogSymbol,Word8,UnRecogSymbol);

	default:
	*(Handle *)pData = NULL;
	gwLowRC = IDS_ERR_NOTIMPLEMENT;
	rc = FALSE;
 }
#undef CASE_DATA
#undef CASE_FUNCTION

return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RFRMT_FUNC(Bool32) RFRMT_SetImportData(Word32 dwType, void * pData)
{
 Bool32 rc = TRUE;

 gwLowRC = 0;

#define CASE_DATA(a,b,c)	case a: c = *(b *)pData; break
#define CASE_PDATA(a,b,c)	case a: c = (b)pData; break
 switch(dwType)
 {
	CASE_DATA(RFRMT_Bool32_Bold,Bool32,gbBold);
	CASE_DATA(RFRMT_Bool32_Italic,Bool32,gbItalic);
	CASE_DATA(RFRMT_Bool32_Size,Bool32,gbSize);
	CASE_DATA(RFRMT_Word32_Format,Word32,gnFormat);
	CASE_PDATA(RFRMT_char_SerifName,char *,gpSerifName);
	CASE_PDATA(RFRMT_char_SansSerifName,char *,gpSansSerifName);
	CASE_PDATA(RFRMT_char_CourierName,char *,gpCourierName);
	CASE_DATA(RFRMT_Word8_UnRecogSymbol,Word8,UnRecogSymbol);
	CASE_DATA(RFRMT_Word32_Language,Word32,gnLanguage);// !!!Art - ���� ������������� ����������� ��� ��������� � ��������
	 default:
		gwLowRC = IDS_ERR_NOTIMPLEMENT;
		rc = FALSE;
 }
#undef CASE_DATA
#undef CASE_PDATA

return rc;
}

void SetReturnCode(Word16 rc)
{
 gwLowRC = rc;
}

Word16 GetReturnCode()
{
 return gwLowRC;
}
//////////////////////////////////////////////////////////////////////////////////
//end of file
