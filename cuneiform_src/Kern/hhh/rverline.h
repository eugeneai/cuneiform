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

#ifndef __RVERLINE_H
#define __RVERLINE_H

#ifndef __GLOBUS_H
#include "globus.h"
#endif

#ifdef __RVERLINE__
  #define RVERLINE_FUNC  FUN_EXPO
#else
  #define RVERLINE_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
        extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif

#pragma pack (push,8)

#define RVERLINE_MAXNAME 260

#ifndef Handle
        #define Handle void *
#endif

RVERLINE_FUNC(Bool32) RVERLINE_Init(Word16 wHeightCode,Handle hStorage);
RVERLINE_FUNC(Bool32) RVERLINE_Done();
RVERLINE_FUNC(Word32) RVERLINE_GetReturnCode();
RVERLINE_FUNC(Int8 *) RVERLINE_GetReturnString(Word32 dwError);
RVERLINE_FUNC(Bool32) RVERLINE_GetExportData(Word32 dwType, void * pData);
RVERLINE_FUNC(Bool32) RVERLINE_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////

#define RVERLINE_BLOCK_TYPE CPAGE_GetInternalType("TYPE_DESC")
#define RVERLINE_ZHERTVY_LINIY CPAGE_GetInternalType("RVERLINE_ZHERTVY_LINIY")


typedef enum
{
                RVERLINE_FNRVERLINE_MarkLines = 1,
                RVERLINE_DTRVERLINE_StyleOfSearchTable,
                RVERLINE_DTRVERLINE_WhereMustSearchTable,
                RVERLINE_DTRVERLINE_DetailOfSearchTable,
                RVERLINE_DTRVERLINE_RegimeOfVerifyLines
} RVERLINE_EXPORT_ENTRIES;
/*  �������� �������  */
#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RVERLINE_FUNC(a) b c
DEC_FUN(Bool32, RVERLINE_MarkLines, (Handle hCComp, Handle hCPage));
#undef DEC_FUN

/*  �������� ������  */

/**  �������� ���������� ������������ �����.                                     **/
/***  A. ����� ������  ***/
typedef int  Regime_VerifyLines;
#define    RVL_Default          0x00000000
#define    RVL_FutuTablCorr     0x00000001
/**  ����� �������� ���������� ������������ �����.                               **/


#ifdef PPS_MAC
   #pragma export off
#endif
// error code


#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif
