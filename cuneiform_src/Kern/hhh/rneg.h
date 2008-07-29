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

#ifndef __RNEG_H
#define __RNEG_H

#ifndef __GLOBUS_H
#include "globus.h"
#endif

#ifdef __RNEG__
  #define RNEG_FUNC  FUN_EXPO
#else
  #define RNEG_FUNC  FUN_IMPO
#endif

#define RNEG_MAXNAME 260
#define Max_Str_Count 1000

struct NegTemp
{
  int vertical;
  int left;
  int oldleft;
  int top;
  int w;
  int h;
  Int32 hStrCCOM;
  Rect16 prc[Max_Str_Count];
  int nRc;
  int fl_rotate;
  Int16 phi[Max_Str_Count];
};

#ifdef __cplusplus
        extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif

#pragma pack (push,8)


//#ifndef Handle
 //       #define Handle void *
//#endif

RNEG_FUNC(Bool32) RNEG_Init(Word16 wHeightCode,Handle parent);
RNEG_FUNC(Bool32) RNEG_Done();
RNEG_FUNC(Word32) RNEG_GetReturnCode();
RNEG_FUNC(Int8 *) RNEG_GetReturnString(Word32 dwError);
RNEG_FUNC(Bool32) RNEG_GetExportData(Word32 dwType, void * pData);
RNEG_FUNC(Bool32) RNEG_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////




typedef enum
{
                RNEG_FNRNEG_RecogNeg = 1,
				RNEG_FNRNEG_TestForNegative
} RNEG_EXPORT_ENTRIES;

typedef Int32  CCOM_handle;

/*  �������� �������  */
#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RNEG_FUNC(a) b c
DEC_FUN(void, RNEG_RecogNeg, (CCOM_handle hCComp, Handle hCPage,Word8* pImageName,int skew));
DEC_FUN(Bool32, RNEG_TestForNegative, (CCOM_handle hCComp, Handle hCPage,Word8* pImageName,Rect16 Rc));

#undef DEC_FUN



#ifdef PPS_MAC
   #pragma export off
#endif
// error code


#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif
