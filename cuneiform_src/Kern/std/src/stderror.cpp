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

static Int32 nErrCount=0;

STD_FUNC( Int32 ) stdGetErrorCount(void)
{
   return nErrCount;
}

STD_FUNC( Int32 ) stdSetErrorCount( Int32 _nErrCount )
{
   Int32 ret = nErrCount;
   nErrCount = _nErrCount;
   return ret;
}

typedef struct tagStdErrorEx     // internal usage
{
   StdError se;
   Int32    nErrNum; // ��� �������� - ���� ������� ��� ���
} _StdErrorEx;

#define _LoopLen 16
static _StdErrorEx __er_loop[_LoopLen]={0}; // ������ ����������� ��� n ��������� ������

static StdError __er_missed={ER_FORGOTTEN, "<...no details...>",0};

STD_FUNC( Int32 ) stdSetError(
   Int32 nErrorCode, char* cond, char* file,
   Int32 nline, Int32 lData )
{
   _StdErrorEx& see =  __er_loop[nErrCount % _LoopLen];
   see.se.nErrorCode = nErrorCode;
   strncpy( see.se.szCondition, SafeStr(cond), sizeof(see.se.szCondition)-1 );
   strncpy( see.se.szFile, SafeStr(file), sizeof(see.se.szFile)-1 );
   see.se.nLine = nline;
   see.se.lData = lData;

   see.nErrNum = nErrCount;

   nErrCount++;

   return nErrCount;

}

STD_FUNC( Bool32 ) stdGetError( Int32 nError, StdError* pse )
// true - ���� ������ � ����� �������:
// ���������� ������� �������������:
//
// stdSetErrorCount(0)
// ...
// if (stdGetError())   // ���� ���������������� ������
//    MyErrorProc();
{
   if (nError < 0 || nError >= nErrCount)
      return FALSE;

   if (pse)
   {
      _StdErrorEx& see =  __er_loop[nError % _LoopLen];
      if (see.nErrNum == nError) // ����������� ������ ��� �� ������
      {
         *pse =  see.se;
      }
      else
      {
         *pse =  __er_missed;
      }
   }

   return TRUE;
}

STD_FUNC( Bool32 ) stdGetLastError( StdError* pse )
// false - ���������� ������ == 0
{
   if (nErrCount<=0)
      return FALSE;
   return stdGetError(nErrCount-1, pse);
}



