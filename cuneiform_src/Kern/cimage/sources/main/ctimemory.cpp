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

// ��� ������������� ��� CFIO.DLL
#ifdef _NO_CFIO
	#undef _NO_CFIO
    //#define _NO_CFIO
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#define  CIMAGE_USE_GLOBAL_MEM
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef CIMAGE_USE_GLOBAL_MEM
#include <windows.h>
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "resource.h"
#include "ctidefines.h"
#include "ctiimage.h"
#include "ctimemory.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef _NO_CFIO
 #include "cfio.h"
#else
 #define CFIO_MAX_COMMENT       48
#endif
// extern functions
//void SetReturnCode(Word16 rc);
//Word16 GetReturnCode();
/////////////////////////////////////////////////////////////////////////////////////////////////////
//CFIO Entries
static void* (*pDAlloc)(Word32, Word32, PWord8, PWord8) = NULL;
static void* (*pAlloc)(Word32, Word32)                  = NULL;
static void  (*pFree)(void *)                           = NULL;
static void* (*pLock)(void *)                           = NULL;
static void  (*pUnlock)(void *)                         = NULL;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
Char8 cCommentBuffer[CFIO_MAX_COMMENT];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TAKE_ENTRIE(Name,Pointer,Out)     	if ( !CFIO_GetExportData(Name, (void*)(&Pointer)) ) Out= FALSE;
Bool32 InitCFIOInterface(Bool32 Status)
{
	Bool32 bRet = TRUE;

	if ( Status == TRUE )
	{
		CFIO_Init(NULL, NULL);
		
		TAKE_ENTRIE(CFIO_FNDAllocMemory, pDAlloc, bRet)
		TAKE_ENTRIE(CFIO_FNAllocMemory, pAlloc, bRet)
		TAKE_ENTRIE(CFIO_FNFreeMemory, pFree, bRet)
		TAKE_ENTRIE(CFIO_FNLockMemory, pLock, bRet)
		TAKE_ENTRIE(CFIO_FNUnlockMemory, pUnlock, bRet)
	}
	else
	{
		bRet = CFIO_Done();
	}

	return bRet;
}

void    CIMAGEComment(PChar8 Comment)
{
	Word32 Len = strlen(Comment);
	strncpy(cCommentBuffer, Comment, (Len < CFIO_MAX_COMMENT ? Len : CFIO_MAX_COMMENT - 1 ) );
}

void *	CIMAGEDAlloc(Word32 stAllocateBlock, PChar8 Comment)
{
	CIMAGEComment(Comment);
	return CIMAGEAlloc(stAllocateBlock);
}

void *	CIMAGEAlloc(Word32 stAllocateBlock)
{
	char * mem = NULL;

#ifdef _NO_CFIO

	#ifdef  CIMAGE_USE_GLOBAL_MEM

		mem = (char *)GlobalAlloc(GPTR, stAllocateBlock);

	#else
	
		mem = ::new char[stAllocateBlock];

	#endif

	if(!mem)
		SetReturnCode(IDS_CIMAGE_ERR_NO_MEMORY);
#else
	mem = (char *)CFIO_DAllocMemory(stAllocateBlock,MAF_GALL_GPTR,(Int8*)"CImage", (Int8*)cCommentBuffer);

	if(!mem)
		SetReturnCode(IDS_CIMAGE_ERR_NO_MEMORY);

#endif

	return mem;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void	CIMAGEFree(void * mem)
{
#ifdef _NO_CFIO
	
	#ifdef  CIMAGE_USE_GLOBAL_MEM

		GlobalFree(mem);

	#else

		::delete []	mem;

	#endif
#else

	CFIO_FreeMemory(mem);

#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void *    CIMAGELock( void * mem )
{
	void * pMem;
#ifdef _NO_CFIO

	#ifdef  CIMAGE_USE_GLOBAL_MEM

		return GlobalLock(mem);

	#else

		return mem;

	#endif

#else

	pMem = CFIO_LockMemory(mem);

	if ( pMem == NULL && mem != NULL )
		return mem;
	
	return pMem;

#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void     CIMAGEUnlock( void * mem )
{
#ifdef _NO_CFIO

	#ifdef  CIMAGE_USE_GLOBAL_MEM

		GlobalUnlock(mem);

	#else

		return;

	#endif

#else

	CFIO_UnlockMemory(mem);
	return;

#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle  CIMAGEOpenSave(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"wb");	
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
Handle  CIMAGEOpenRestore(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"rb");	
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  CIMAGEWrite(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fwrite(lpdata,1,size,(FILE*)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  CIMAGERead(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fread(lpdata,1,size,(FILE *)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
void    CIMAGEClose(Handle h)
{
#ifdef _NO_CFIO
	fclose((FILE*)h);
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// end of file