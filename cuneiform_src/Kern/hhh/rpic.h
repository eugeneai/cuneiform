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

#ifndef __RPIC_H
#define __RPIC_H

#ifndef __GLOBUS_H
#include "globus.h"
#endif
/*
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"
*/
#ifdef __RPIC__
  #define RPIC_FUNC  FUN_EXPO
#else
  #define RPIC_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#pragma pack (push,8)


RPIC_FUNC(Bool32) RPIC_Init(Word16 wHeightCode,Handle hStorage);
RPIC_FUNC(Bool32) RPIC_Done();
RPIC_FUNC(Word32) RPIC_GetReturnCode();
RPIC_FUNC(Int8 *) RPIC_GetReturnString(Word32 dwError);
RPIC_FUNC(Bool32) RPIC_GetExportData(Word32 dwType, void * pData);
RPIC_FUNC(Bool32) RPIC_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////


typedef enum
{
		RPIC_FNRPIC_SearchPictures
} RPIC_EXPORT_ENTRIES;


#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RPIC_FUNC(a) b c
DEC_FUN(Bool32, RPIC_SearchPictures,(Handle hCCOM, Handle hCCOM_big,Handle hCPAGE));
#undef DEC_FUN

/*
typedef void   (*FNRPIC_ProgressStart)( void );
typedef	Bool32 (*FNRPIC_ProgressStep)(Word32 perc);
typedef	void   (*FNRPIC_ProgressFinish)( void );
*/

struct _RPIC_Comp_Rect
{
	Int16 upper;                   // upper boundary of component
	Int16 left;                    // left boundary of component
	Int16 h;                       // height of component
	Int16 w;                       // width of component
};
typedef struct _RPIC_Comp_Rect RPIC_Comp_Rect;


#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif
