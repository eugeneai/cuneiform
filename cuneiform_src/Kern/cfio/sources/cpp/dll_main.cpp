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

//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//                                                                              //
//                    Cognitive Technologies Ltd.                               //
//                                                                              //
//                    Data Storage Container                                    //
//                                                                              //
//                                                                              //
//                                                                              //
//                                                                              //
//                    started at 25 may 1998                                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////
#define __CFIO__
//#define CFIO_USE_WIN32_API
#include "ctccontrol.h"
//#undef CFIO_USE_WIN32_API

#include "compat_defs.h"

//////////////////////////////////////////////////////////////////GLOBAL 
void SetReturnCode_cfio(Word16 rc);
//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
static Word16            wHeightRC =                         0;
static Word16            wLowRC =                            0;
static Handle            hInst =                             NULL;
CTCControl *      Control_ctc =                           NULL;
static Int32             InitCount =                         0;
static Bool32            InitDone =                          FALSE;
//////////////////////////////////////////////////////////////////////////////////
//
BOOL APIENTRY DllMain( Handle hModule, 
                        DWORD ul_reason_for_call, 
                        LPVOID lpReserved )
{
    switch( ul_reason_for_call ) 
	{
    case DLL_PROCESS_ATTACH:
		hInst = hModule;
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
CFIO_FUNC(Bool32) CFIO_Init(Word16 wHeightCode,Handle hStorage)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if ( !Control_ctc )
	{
		Control_ctc = new CTCControl;
		wHeightRC = wHeightCode;
	}
	
	if ( Control_ctc )
	{
		InitCount++;
		return TRUE;
	}

	SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_Done()
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if ( Control_ctc )
	{
		if (--InitCount == 0)
		{
			delete Control_ctc;
			Control_ctc = NULL;
		}
		return InitDone = TRUE;
	}
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
	}
	
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_GetReturnCode()
{
	return (wHeightRC<<16)|(wLowRC - IDS_ERR_MIN);
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Int8 *) CFIO_GetReturnString(Word32 dwError)
{
	Word16 rc = (Word16)(dwError & 0xFFFF) + IDS_ERR_MIN;
	static Int8 szBuffer[512];

	if( dwError >> 16 != wHeightRC)
		wLowRC = IDS_ERR_NOTIMPLEMENT;

	if( rc > IDS_ERR_MIN && rc < IDS_ERR_MAX )
		LoadString((HINSTANCE)hInst,rc,(char *)szBuffer,sizeof(szBuffer));
	else
		return NULL;

	return szBuffer;
}
//////////////////////////////////////////////////////////////////////////////////
//
void SetReturnCode_cfio(Word16 rc)
{
	if ( rc == IDS_CFIO_ERR_NO || wLowRC == IDS_CFIO_ERR_NO )
		wLowRC = rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word16 GetReturnCode_cfio()
{
	return wLowRC;
}
//////////////////////////////////////////////////////////////////////////////////
//
#define CASE_FUNCTION(a)	case CFIO_FN##a:	*(FNCFIO##a *)pData = CFIO_##a; break
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	wLowRC = 0;
	switch(dwType)
	{
	case CFIO_PCHAR_TEMPORARY_FOLDER:
		rc = Control_ctc->GetFolder(CFIO_TEMP_FOLDER, (char *)pData);
		break;

	case CFIO_PCHAR_STORAGE_FOLDER:
		rc = Control_ctc->GetFolder(CFIO_FILE_FOLDER, (char *)pData);
		break;

	case CFIO_PCHAR_FILE_FOLDER:
		rc = Control_ctc->GetFolder(CFIO_STORAGE_FOLDER, (char *)pData);
		break;

	CASE_FUNCTION(OpenStorage);
	CASE_FUNCTION(CloseStorage);
	CASE_FUNCTION(DeleteStorage);
	CASE_FUNCTION(WriteFileToStorage);
	CASE_FUNCTION(ReadFileFromStorage);
	CASE_FUNCTION(OpenFreeFile);
	CASE_FUNCTION(CloseFreeFile);
	CASE_FUNCTION(WriteToFile);
	CASE_FUNCTION(ReadFromFile);
	CASE_FUNCTION(SeekFilePointer);
	CASE_FUNCTION(TellFilePointer);
	CASE_FUNCTION(FlushFile);
	CASE_FUNCTION(AllocMemory);
	CASE_FUNCTION(DAllocMemory);
	CASE_FUNCTION(ReAllocMemory);
	CASE_FUNCTION(FreeMemory);
	CASE_FUNCTION(LockMemory);
	CASE_FUNCTION(UnlockMemory);
	CASE_FUNCTION(WriteMemoryToFile);
	CASE_FUNCTION(ReadMemoryFromFile);
	CASE_FUNCTION(WriteMemoryToStorage);
	CASE_FUNCTION(ReadMemoryFromStorage);
  default:
		*(char **)pData = NULL;
		wLowRC = IDS_ERR_NOTIMPLEMENT;
		rc = FALSE;
	}
return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_SetImportData(Word32 dwType, void * pData)
{
	Word32      Folder;

	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	wLowRC = 0;
	switch(dwType)
	{
	case CFIO_PCHAR_TEMPORARY_FOLDER:
		Folder = CFIO_TEMP_FOLDER;
		break;

	case CFIO_PCHAR_STORAGE_FOLDER:
		Folder = CFIO_FILE_FOLDER;
		break;

	case CFIO_PCHAR_FILE_FOLDER:
		Folder = CFIO_STORAGE_FOLDER;
		break;

	default:
		wLowRC = IDS_ERR_NOTIMPLEMENT;
		return FALSE;
	}
return Control_ctc->SetFolder(Folder, (char *)pData);
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_OpenStorage(PInt8 lpName, Word32 dwTypes)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->OpenStorage((PChar8)lpName, dwTypes);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_CloseStorage(Handle  hStorage, Word32  dwFlag)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->CloseStorage(hStorage, dwFlag);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_DeleteStorage (PInt8 lpName)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->DeleteStorage((PChar8)lpName);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_WriteFileToStorage (Handle hStorage, Handle hFile, PInt8 lpNameInStorage)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->WriteFileToStorage(hStorage, hFile, (PChar8)lpNameInStorage);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_ReadFileFromStorage (Handle hStorage, PInt8 lpName)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->ReadFileFromStorage(hStorage, (PChar8)lpName);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_OpenFreeFile(Handle hStorage, PInt8 lpName, Word32 dwFlag)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->OpenFile(hStorage, (PChar8)lpName, dwFlag);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_CloseFreeFile(Handle hFile, Word32 dwFlag)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->CloseFile(hFile, dwFlag);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_WriteToFile (Handle hFile, PInt8 lpData, Word32 dwSize)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->WriteFile(hFile, lpData, dwSize);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_ReadFromFile (Handle hFile, PInt8 lpData, Word32 dwSize)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->ReadFromFile(hFile, lpData, dwSize);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_SeekFilePointer (Handle hFile, Word32 dwBytes, Word32 dwFrom)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Seek(hFile, dwBytes, dwFrom);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_TellFilePointer (Handle hFile)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Tell(hFile);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_FlushFile(Handle hFile)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Flush(hFile);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_AllocMemory (Word32 dwSize, Word32 dwFlag)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Alloc(dwSize, dwFlag,"CFIO general memory block","no comment");
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_DAllocMemory (Word32 dwSize, Word32 dwFlag, Int8* cOwner, Int8* Comment)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Alloc(dwSize, dwFlag, (PChar8)cOwner, (PChar8)Comment);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_ReAllocMemory (Handle hMemory, Word32 dwSize, Word32 dwFlag)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->ReAlloc(hMemory, dwSize, dwFlag);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_FreeMemory(Handle hMem)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Free(hMem);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Handle) CFIO_LockMemory(Handle hMem)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Lock(hMem);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Bool32) CFIO_UnlockMemory(Handle hMem)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->Unlock(hMem);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_WriteMemoryToFile(Handle hMem, PInt8 lpName)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->WriteMemToFile(hMem, (PChar8)lpName);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_ReadMemoryFromFile(PInt8 lpName, Handle * phMem)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->ReadMemFromFile((PChar8)lpName, phMem);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_WriteMemoryToStorage(Handle hMem, Handle hStorage, PInt8 lpName)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->WriteMemToStorage(hMem, hStorage, (PChar8)lpName);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
CFIO_FUNC(Word32) CFIO_ReadMemoryFromStorage(Handle hStorage, PInt8 lpName, Handle * phMem)
{
	SetReturnCode_cfio(IDS_CFIO_ERR_NO);
	
	if( Control_ctc )
		return Control_ctc->ReadMemFromStorage(hStorage, (PChar8)lpName, phMem);
	else
	{
		if (InitDone)
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_DONE);
		else
			SetReturnCode_cfio(IDS_CFIO_ERR_CONTAINER_NOT_INITIALIZED);
		return FALSE;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//end of file
