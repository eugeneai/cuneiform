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

#include "internal.h"
#pragma hdrstop


#include "std.h"

#ifdef __BORLANDC__
#include "alloc.h"
#include "dos.h"
#endif

#ifdef _DEBUG
   static Int32 _stdMallocCounter=0;
   static Int32 _stdReallocCounter=0;
   static Int32 _stdFreeCounter=0;

   class __TestStdMem
   {
   public:
      ~__TestStdMem()
         {
#ifndef _NO_MEM_REPORT
			assert( _stdMallocCounter == _stdFreeCounter );
#endif
	  };
   };
   static __TestStdMem tester;

#endif // _DEBUG

STD_FUNC( void )  stdGetMemInfo( StdMemInfo* pMemInf )
{
   if (pMemInf)
   {
#ifdef _DEBUG
      pMemInf->nMallocCnt = _stdMallocCounter;
      pMemInf->nFreeCnt = _stdFreeCounter;
      pMemInf->nReallocCnt = _stdReallocCounter;
#endif // _DEBUG
   }
}


STD_FUNC( void* ) stdMalloc( Int32 size )
{
#if 0
   void * res = malloc(size);

#ifdef _DEBUG
   if (res==NULL)
   {
      CONSOLE("stdMalloc(%d)=>NULL {%d}", size, _stdMallocCounter);
   }
   else
   {
      _stdMallocCounter++; // need free later
   }
#endif

   return res;
#endif
   return malloc(size);
};

STD_FUNC( void* )  stdRealloc( void* old_ptr, Int32 new_size, Int32 old_size )
{

#ifdef _DEBUG
   _stdReallocCounter++;
      if (res==NULL)
      {
         CONSOLE("stdRealloc(%d)=>NULL {%d}", new_size, _stdReallocCounter);
         if (old_ptr != NULL && new_size == 0)   // <=> free
            _stdFreeCounter++;
      }
      else
      {
         if (old_ptr == NULL) // <=> malloc
            _stdMallocCounter++;
      }
#endif
      return realloc(old_ptr, new_size);
}

STD_FUNC( void  ) stdFree( void* ptr )
{
   if (ptr==NULL)
      return;
   free(ptr);
#ifdef _DEBUG
   _stdFreeCounter++;
#endif
};

STD_FUNC( void  ) stdFreeX( void** pptr )
{
#ifdef _DEBUG
   assert(pptr);
#endif
   if (*pptr)
   {
      stdFree(*pptr);
      *pptr = NULL;
   };
}

STD_FUNC( void* ) stdMemcpy( void* dest , void* src , Int32 copy_count )
{

#ifdef _DEBUG
   assert(dest);
   assert(src);
#endif

   return memcpy(dest, src, copy_count);
}
