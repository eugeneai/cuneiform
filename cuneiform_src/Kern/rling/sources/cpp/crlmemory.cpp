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
#ifndef _NO_CFIO
	#define _NO_CFIO
#endif

/*#define  RLING_USE_GLOBAL_MEM*/

#ifdef RLING_USE_GLOBAL_MEM
#include <windows.h>
#endif

#include "resource.h"
#include "crldefines.h"
#include "crlmemory.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef _NO_CFIO
#include "cfio.h"
#endif

// extern functions
//void SetReturnCode_rling(Word16 rc);
//Word16 GetReturnCode_rling();

/////////////////////////////////////////////////////////////////////////////////////////////////////
//memory Allocator for RLING module
void *	RLINGAlloc(Word32 stAllocateBlock)
{
    /* JussiP: disabled all this, since it seems to be legacy from Win16 days. Just use malloc.
	char * mem = NULL;

#ifdef _NO_CFIO

  #ifdef  RLING_USE_GLOBAL_MEM
	mem = (char *)GlobalAlloc(GPTR, stAllocateBlock);
  #else
	mem = ::new char[stAllocateBlock];
  #endif

	if(!mem)
		SetReturnCode_rling(IDS_RLING_ERR_NO_MEMORY);
#else

	mem = (char *)AllocMemory(1024,MAF_GALL_GPTR);

	if(!mem)
		SetReturnCode_rling(IDS_RLING_ERR_NO_MEMORY);

#endif

	return mem;
	*/
    return malloc(stAllocateBlock);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void	RLINGFree(void * mem)
{
    /*
#ifdef _NO_CFIO

  #ifdef  RLING_USE_GLOBAL_MEM
	GlobalFree(mem);
  #else
	::delete []	mem;
  #endif

#else

	FreeMemory(mem);

#endif
*/
    free(mem);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void *    RLINGLock( void * mem )
{
#ifdef _NO_CFIO

	return mem;

#else

	return LockMemory(mem);

#endif
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
void     RLINGUnlock( void * mem )
{
#ifdef _NO_CFIO

	return;

#else

	UnlockMemory(mem);
	return;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle  RLINGOpenSave(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"wb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
Handle  RLINGOpenRestore(char * lpName)
{
	Handle rc = NULL;
#ifdef _NO_CFIO
	rc = (Handle)fopen(lpName,"rb");
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RLINGWrite(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fwrite(lpdata,1,size,(FILE*)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
unsigned int  RLINGRead(Handle h,void * lpdata,unsigned int size)
{
	Word32 rc = 0;
#ifdef _NO_CFIO
	rc = fread(lpdata,1,size,(FILE *)h);
#endif
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////
//
void    RLINGClose(Handle h)
{
#ifdef _NO_CFIO
	fclose((FILE*)h);
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////
// end of file
