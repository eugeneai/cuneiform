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

/**********  ���������  ****************************************************************************/
/*  �����,                                                                                         */
/*  �����������                                                                                    */
/*  ������     : ������� �������                                                                  */
/*  ��������   :  20.10.00                                                                         */
/*  ����       :  'RSMemory.cpp'                                                                   */
/*  ���������� :                                                                                   */
/*  ���������� :                                                                                   */
/*  �����������:                                                                                   */
/*                                                                                                 */
/*-------------------------------------------------------------------------------------------------*/
// ��� ������������� ��� CFIO.DLL
// �� ���� RSDefines.h
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#define  RSTUFF_USE_GLOBAL_MEM
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef RSTUFF_USE_GLOBAL_MEM
#include <windows.h>
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "resource.h"
#include "rsdefines.h"
#include "rsmemory.h"
#include "rsfunc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef _NO_CFIO
 #include "cfio.h"
#else
 #define CFIO_MAX_COMMENT       48
#endif
// extern functions
//void SetReturnCode_rstuff(Word16 rc);
//Word16 GetReturnCode_rstuff();
/////////////////////////////////////////////////////////////////////////////////////////////////////
//CFIO Entries
static void* (*pDAlloc)(Word32, Word32, PWord8, PWord8) = NULL;
static void* (*pAlloc)(Word32, Word32)                  = NULL;
static void  (*pFree)(void *)                           = NULL;
static void* (*pLock)(void *)                           = NULL;
static void  (*pUnlock)(void *)                         = NULL;

Word8* Buffer=NULL;
Word8* WorkMem=NULL;
int BufferSize=0;
int WorkMemSize=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define TAKE_ENTRIE(Name,Pointer,Out)     	if ( !CFIO_GetExportData(Name, (void*)(&Pointer)) ) Out= FALSE;
Bool32 InitCFIOInterface(Bool32 Status)
{
	Bool32 bRet = TRUE;

#ifndef _NO_CFIO

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

#endif //_NO_CFIO

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define RSTUFF
Char8 cCommentBuffer[CFIO_MAX_COMMENT];

void    RSTUFFComment(PChar8 Comment)
{
	Word32 Len = strlen(Comment);
	strncpy(cCommentBuffer, Comment, (Len < CFIO_MAX_COMMENT ? Len : CFIO_MAX_COMMENT - 1 ) );
}

void *	RSTUFFDAlloc(Word32 stAllocateBlock, PChar8 Comment)
{
	RSTUFFComment(Comment);
	return RSTUFFAlloc(stAllocateBlock);
}

void *	RSTUFFAlloc(Word32 stAllocateBlock)
{
	char * mem = NULL;

#ifdef _NO_CFIO

	#ifdef  RSTUFF_USE_GLOBAL_MEM

		mem = (char *)GlobalAlloc(GPTR, stAllocateBlock);

	#else

		mem = ::new char[stAllocateBlock];
		memset(mem, 0, stAllocateBlock );

	#endif

	if(!mem)
		SetReturnCode_rstuff((Word16)IDS_RSTUFF_ERR_NO_MEMORY);
#else

	mem = (char *)CFIO_DAllocMemory(stAllocateBlock,MAF_GALL_GPTR,(Int8*)"RSTUFF", (Int8*)cCommentBuffer);

	if(!mem)
		SetReturnCode_rstuff((Word16)IDS_RSTUFF_ERR_NO_MEMORY);

#endif

	return mem;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void	RSTUFFFree(void * mem)
{
#ifdef _NO_CFIO

	#ifdef  RSTUFF_USE_GLOBAL_MEM

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
void *    RSTUFFLock( void * mem )
{
#ifdef _NO_CFIO

	#ifdef  RSTUFF_USE_GLOBAL_MEM

		return GlobalLock(mem);

	#else

		return mem;

	#endif

#else

	void * pMem;

	pMem = CFIO_LockMemory(mem);

	if ( pMem == NULL && mem != NULL )
		return mem;

	return pMem;

#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void     RSTUFFUnlock( void * mem )
{
#ifdef _NO_CFIO

	#ifdef  RSTUFF_USE_GLOBAL_MEM

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
Handle  RSTUFFOpenSave(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"wb");
#else
	rc = (Handle)fopen(lpName,"wb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
Handle  RSTUFFOpenRestore(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"rb");
#else
	rc = (Handle)fopen(lpName,"rb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RSTUFFWrite(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fwrite(lpdata,1,size,(FILE*)h);
#else
	rc = fwrite(lpdata,1,size,(FILE*)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RSTUFFRead(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fread(lpdata,1,size,(FILE *)h);
#else
	rc = fread(lpdata,1,size,(FILE *)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
void    RSTUFFClose(Handle h)
{
#ifdef _NO_CFIO
	fclose((FILE*)h);
#else
	fclose((FILE*)h);
#endif
}

void GiveMainBuff (void **vvBuff, int *Size)
{
	*vvBuff = Buffer;
	*Size = BufferSize;
}
void GiveWorkBuff (char **ccBuff, int *Size)
{
	*ccBuff = (char*)WorkMem;
	*Size = WorkMemSize;
}

void SetMainBuff(void *vBuff, int Size)
{
	Buffer=(Word8*)vBuff;
	BufferSize=Size;
}

void SetWorkBuff(void *vBuff, int Size)
{
	WorkMem=(Word8*)vBuff;
	WorkMemSize=Size;
}

void ReSetMem()
{
	Buffer=NULL;
	BufferSize=0;
	WorkMem=NULL;
	WorkMemSize=0;
}

/////////////////////////////////////////////////////////////////////////////////////////
// end of file
