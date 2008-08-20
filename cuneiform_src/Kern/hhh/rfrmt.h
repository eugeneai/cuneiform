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

#ifndef __RFRMT_H
#define __RFRMT_H

#ifndef __GLOBUS_H
#include "globus.h"
#endif

#ifdef __RFRMT__
  #define RFRMT_FUNC  FUN_EXPO
#else
  #define RFRMT_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#pragma pack (push,8)

#define RFRMT_MAXNAME 260

RFRMT_FUNC(Bool32) RFRMT_Init(Word16 wHeightCode,Handle hStorage);
RFRMT_FUNC(Bool32) RFRMT_Done();
RFRMT_FUNC(Word32) RFRMT_GetReturnCode();
RFRMT_FUNC(Int8 *) RFRMT_GetReturnString(Word32 dwError);
RFRMT_FUNC(Bool32) RFRMT_GetExportData(Word32 dwType, void * pData);
RFRMT_FUNC(Bool32) RFRMT_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////


typedef enum
{
		RFRMT_FNRFRMT_Formatter = 1,
		RFRMT_FNRFRMT_SaveRtf,
		RFRMT_Bool32_Bold,
		RFRMT_Bool32_Italic,
		RFRMT_Bool32_Size,
		RFRMT_Word32_Format,
		RFRMT_char_SerifName,
		RFRMT_char_SansSerifName,
		RFRMT_char_CourierName,
		RFRMT_Word8_UnRecogSymbol,
		RFRMT_Word32_Language
} RFRMT_EXPORT_ENTRIES;


#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RFRMT_FUNC(a) b c

DEC_FUN(Bool32,  RFRMT_Formatter,(char * lpInputFileName , Handle* PtrEdTree));
DEC_FUN(Bool32,  RFRMT_SaveRtf,(char * lpOutputFileName,Word32 code));

#undef DEC_FUN



#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif
