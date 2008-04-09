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
/*  ����       :  'VL_Resid.CPP'                                              */
/*  ���������� :  ����� ������� ���������� "RVERLINE"                         */
/*  ���������� :  ����������� ������ � ������� ������������                   */
/*----------------------------------------------------------------------------*/
#define __RVERLINE__

#include <stdio.h>
#include <windows.h>
/*  interface our  */
#include "RVerLine.H"
/*  interface my   */
#include "AM_ERR.H"
#include "AM_COMM.H"
#include "VL_RULE.H"
/*------------own objects-----------------------------------------------------*/
Word16      gwHeightRC = 0;      // ���������� ����� ���������� � ����� ������
Word16      gwLowRC    = ER_ROUGH_NONE;      // ������ � ������ ����������
HANDLE      ghStorage  = NULL;   // ��������� �� ���������
HANDLE      ghInst     = NULL;   // ��������� �� ���� ����
static Int8 szBuffer[512];               // ��� �������� ������
Handle RltVertix_VL; // �������� ������� ������� ��� ����������� �����
/*------------extern functions------------------------------------------------*/
Bool MyInit_CPage ();
/*------------own functions---------------------------------------------------*/
void   SetReturnCode (Word16 rc);
Word16 GetReturnCode ();
Bool WasInitRVERLINE ();
/*----------------------------------------------------------------------------*/
BOOL APIENTRY DllMain( HANDLE hModule, 
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
/*----------------------------------------------------------------------------*/
RVERLINE_FUNC(Bool32) RVERLINE_Init (Word16 wHeightCode, HANDLE hStorage)
{
	Word8 err8;
	Bool ret;
	if (gwHeightRC!=0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_YET_INIT;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	if (wHeightCode==0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_BAD_UNICAL_NUMBER;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	ret = AM_InitComm (wHeightCode);
	if (!ret)
	{
		err8 = (Word8)ER_ROUGH_NORMAL;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_FUNC_DPUMA;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	/*  ����������� �������� ������ �������  */
	AM_RegiVert (&RltVertix_VL, "����������� �����...", NULL);
	/*  ���������� �������� �������� ������ �������  */
	AM_MakeTreeRules_VerifLines (RltVertix_VL);
	/*  �������� ��������� ����������  */
	ret = MyInit_CPage ();
	if (!ret)
		return FALSE;
	gwHeightRC = wHeightCode;
	gwLowRC = ER_ROUGH_NONE;
	ghStorage  = hStorage;
	return TRUE;
}
/*----------------------------------------------------------------------------*/
RVERLINE_FUNC(Bool32) RVERLINE_Done()
{
	Word8 err8;
	if (gwHeightRC==0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_NOT_INIT;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	gwHeightRC = 0;
	gwLowRC = ER_ROUGH_NONE;
	ghStorage  = NULL;
	CloseAllRes ();
	AM_DoneComm ();
	return TRUE;
}
/*----------------------------------------------------------------------------*/
RVERLINE_FUNC(Word32) RVERLINE_GetReturnCode()
{
	Word8  err8;
	Word32 err32;
	if (gwHeightRC==0)
	{
		err32 = (Word32)(0);
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_NOT_INIT;
		gwLowRC |= (Word16)err8;
		err32 |= (Word32)gwLowRC;
		return err32;
	}
	if (gwLowRC==ER_ROUGH_NONE)
		return (Word32)(0);
	return (Word32)(gwHeightRC<<16)|(gwLowRC);
}
/*----------------------------------------------------------------------------*/
RVERLINE_FUNC(Int8 *) RVERLINE_GetReturnString(Word32 dwError)
{
	Word8  err8, err8_1;
	Word16 err16;
	char  Work[256];
	if (gwHeightRC==0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_NOT_INIT;
		gwLowRC |= (Word16)err8;
		return NULL;
	}
	if (dwError >> 16 != gwHeightRC)
	{
		err8 = (Word8)ER_ROUGH_OTHER_LIBRARY;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_NO_COMMENT;
		gwLowRC |= (Word16)err8;
		return NULL;
	}
	err16  = (Word16)(dwError & 0xFFFF);
	err8   = (Word8)((err16/256) & 255);
	err8_1 = (Word8)(err16 & 255);
	LoadString ((HINSTANCE)ghInst, err16, (char *)szBuffer, sizeof (szBuffer));
	switch (err8)
	{
		case ER_ROUGH_NONE :
			sprintf ((char *)szBuffer, "RVERLINE : ������ ���.");
			break;
		case ER_ROUGH_OTHER_LIBRARY :
			sprintf ((char *)szBuffer, "RVERLINE : ������ ������ ����������.");
			break;
		case ER_ROUGH_NOT_SUCH_ERROR_CODE :
			sprintf ((char *)szBuffer, "RVERLINE : ��� ������ ���� ������.");
			break;
		case ER_ROUGH_CALL_REFUSED :
			sprintf ((char *)szBuffer, "RVERLINE : ������������� ������.");
			break;
		case ER_ROUGH_NORMAL :
			sprintf ((char *)szBuffer, "RVERLINE : ������.");
			break;
		default :
			err8 = (Word8)ER_ROUGH_NOT_SUCH_ERROR_CODE;
			gwLowRC = (Word16)(err8<<8);
			err8 = (Word8)ER_DETAIL_NO_COMMENT;
			gwLowRC |= (Word16)err8;
			return NULL;
	}
	switch (err8)
	{
		case ER_ROUGH_CALL_REFUSED :
		case ER_ROUGH_NORMAL :
			Work[0] = '\0';
			switch (err8_1)
			{
				case ER_DETAIL_WAS_YET_INIT :
					sprintf (Work, " ������������� ��� ����.");
					break;
				case ER_DETAIL_WAS_NOT_INIT :
					sprintf (Work, " ������������� ��� �� ����.");
					break;
				case ER_DETAIL_BAD_UNICAL_NUMBER :
					sprintf (Work, " ������ ���������� �����.");
					break;
				case ER_DETAIL_TOO_MUCH_CALLS :
					sprintf (Work, " ������� ����� �������.");
					break;
				case ER_DETAIL_NOT_MADE_SUCH_DATA :
					sprintf (Work, " �� ���������� ����� ������.");
					break;
				case ER_DETAIL_EMPTY_FUNC :
					sprintf (Work, " �������������� ����� ������� �����������.");
					break;
				case ER_DETAIL_MAKET_FUNC :
					sprintf (Work, " �������-����� (���������� ������� ������).");
					break;
				case ER_DETAIL_BAD_PARAMETRS :
					sprintf (Work, " ������ ���������.");
					break;
				case ER_DETAIL_NO_MEMORY :
					sprintf (Work, " ��� ������.");
					break;
				case ER_DETAIL_FUNC_CPAGE :
					sprintf (Work, " ������ ��������� ������� �� 'CPAGE'.");
					break;
				case ER_DETAIL_FUNC_DPUMA :
					sprintf (Work, " ������ ��������� ������� �� 'DPUMA'.");
					break;
				case ER_DETAIL_NONE :
				case ER_DETAIL_NO_COMMENT :
				default :
					break;
			}
			strcat ((char *)szBuffer, Work);
			break;
		default :
			break;
	}
	return szBuffer;
}
/*----------------------------------------------------------------------------*/
RVERLINE_FUNC(Bool32) RVERLINE_GetExportData(Word32 dwType, void * pData)
{
	Word8 err8;
	if (gwHeightRC==0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_NOT_INIT;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	gwLowRC = ER_ROUGH_NONE;

#define CASE_FUNCTION(a)	case RVERLINE_FN##a:	*(FN##a *)pData = a; break

	switch(dwType)
	{
		CASE_FUNCTION(RVERLINE_MarkLines);
		default:
			*(Handle *)pData = NULL;
			err8 = (Word8)ER_ROUGH_CALL_REFUSED;
			gwLowRC = (Word16)(err8<<8);
			err8 = (Word8)ER_DETAIL_NOT_MADE_SUCH_DATA;
			gwLowRC |= (Word16)err8;
			return FALSE;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*/
void SetReturnCode(Word16 rc)
{
	gwLowRC = rc;
}
/*----------------------------------------------------------------------------*/
Word16 GetReturnCode()
{
	return gwLowRC;
}
/*----------------------------------------------------------------------------*/
Bool WasInitRVERLINE ()
{
	Word8 err8;
	if (gwHeightRC==0)
	{
		err8 = (Word8)ER_ROUGH_CALL_REFUSED;
		gwLowRC = (Word16)(err8<<8);
		err8 = (Word8)ER_DETAIL_WAS_NOT_INIT;
		gwLowRC |= (Word16)err8;
		return FALSE;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*/
