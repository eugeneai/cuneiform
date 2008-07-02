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

/*  interface my        */

#ifndef __SMetric_H
	#define __SMetric_H
	#include "cttypes.h"

#ifndef __GLOBUS_H
	#include "globus.h"
#endif

#ifdef __SMetric__
	#define SMetric_FUNC  FUN_EXPO
#else
	#define SMetric_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
        extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif

#pragma pack (push,8)

#ifndef Handle
        #define Handle void *
#endif

SMetric_FUNC(Bool32) SMetric_Init(Word16 wHeightCode,Handle hStorage);
SMetric_FUNC(Bool32) SMetric_Done();
SMetric_FUNC(Word32) SMetric_GetReturnCode();
SMetric_FUNC(Int8 *) SMetric_GetReturnString(Word32 dwError);
SMetric_FUNC(Bool32) SMetric_GetExportData(Word32 dwType, void * pData);
SMetric_FUNC(Bool32) SMetric_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////

#define SMetric_BLOCK_TYPE CPAGE_GetInternalType("TYPE_DESC")


typedef enum
{
                SMetric_FNSMetric_FindMainSkew = 1,
                SMetric_DTSMetric_AnyOne,
				SMetric_ResolX,	// ��� ������� ���������� �� x (� Import Int32 � Export Int32*)
				SMetric_ResolY  // ��� ������� ���������� �� y (� Import Int32 � Export Int32*)
} SMetric_EXPORT_ENTRIES;
/*  �������� �������  */
#define DEC_FUN(a,b,c) typedef a (*FN##b)c; SMetric_FUNC(a) b c
DEC_FUN(Bool32, SMetric_FindMainSkew, (void *vB, char *cWork, int SizeWork, Int32 *pSkew, Int32 *pSkewLocVerLin, Rect16 *pRcReg, Int32 SkewReg, char *pStr, Bool CalcMuchSkew, Bool TalkMuchSkew));

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
