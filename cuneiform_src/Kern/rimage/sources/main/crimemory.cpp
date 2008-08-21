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
//#define  RIMAGE_USE_GLOBAL_MEM
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef RIMAGE_USE_GLOBAL_MEM
#include <windows.h>
#endif
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "resource.h"
#include "cridefines.h"
#include "criimage.h"
#include "crimemory.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef _NO_CFIO
 #include "cfio.h"
#else
 #define CFIO_MAX_COMMENT       48
#endif
// extern functions
//void SetReturnCode_rimage(Word16 rc);
//Word16 GetReturnCode_rimage();
/////////////////////////////////////////////////////////////////////////////////////////////////////
//CFIO Entries
static void* (*pDAlloc)(Word32, Word32, PWord8, PWord8) = NULL;
static void* (*pAlloc)(Word32, Word32)                  = NULL;
static void  (*pFree)(void *)                           = NULL;
static void* (*pLock)(void *)                           = NULL;
static void  (*pUnlock)(void *)                         = NULL;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define RIMAGE
Char8 cCommentBuffer[CFIO_MAX_COMMENT];

void    RIMAGEComment(PChar8 Comment)
{
	Word32 Len = strlen(Comment);
    Len = Len < CFIO_MAX_COMMENT ? Len : CFIO_MAX_COMMENT - 1 ;
	strncpy(cCommentBuffer, Comment, Len );
    cCommentBuffer[Len] = 0x0;
}

void *	RIMAGEDAlloc(Word32 stAllocateBlock, PChar8 Comment)
{
	RIMAGEComment(Comment);
	return RIMAGEAlloc(stAllocateBlock);
}

void *	RIMAGEAlloc(Word32 stAllocateBlock) {
	return malloc(stAllocateBlock);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void	RIMAGEFree(void * mem) {
	free(mem);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void *    RIMAGELock( void * mem ) {
	return mem;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void     RIMAGEUnlock( void * mem ) {
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle  RIMAGEOpenSave(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"wb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
Handle  RIMAGEOpenRestore(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"rb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RIMAGEWrite(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fwrite(lpdata,1,size,(FILE*)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RIMAGERead(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fread(lpdata,1,size,(FILE *)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
void    RIMAGEClose(Handle h)
{
#ifdef _NO_CFIO
	fclose((FILE*)h);
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// end of file
