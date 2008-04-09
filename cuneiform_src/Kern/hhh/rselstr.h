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

#ifndef __RSELSTR_H
#define __RSELSTR_H

#include "Ccomdefs.h"
#include "cpage.h"

#ifndef __GLOBUS_H
#include "globus.h"
#endif

#ifdef __RSELSTR__
  #define RSELSTR_FUNC  FUN_EXPO
#else
  #define RSELSTR_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
	extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif
// 
#pragma pack (push,8)

#define RSELSTR_MAXNAME 260




RSELSTR_FUNC(Bool32) RSELSTR_Init(Word16 wHeightCode,Handle hStorage);
RSELSTR_FUNC(Bool32) RSELSTR_Done();
RSELSTR_FUNC(Word32) RSELSTR_GetReturnCode();
RSELSTR_FUNC(Int8 *) RSELSTR_GetReturnString(Word32 dwError);
RSELSTR_FUNC(Bool32) RSELSTR_GetExportData(Word32 dwType, void * pData);
RSELSTR_FUNC(Bool32) RSELSTR_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////
typedef struct struct_CHSTR_Objects
{
	Word8 ImageName[CPAGE_MAXNAME];
	Rect16 Rc;
	Bool32 type_vert;
	Bool32 type_neg;
	Int32 block_number;
} CHSTR_Objects;



typedef enum
{
		RSELSTR_FNRSELSTR_ExtractTextStrings = 1,
		RSELSTR_FNRSELSTR_ProgressStart,
		RSELSTR_FNRSELSTR_ProgressStep,
		RSELSTR_FNRSELSTR_ProgressFinish,
		RSELSTR_FNRSELSTR_PutObjects,
		RSELSTR_FNRSELSTR_CutStr,
        RSELSTR_FNRSELSTR_RotateRaster,
        RSELSTR_FNRSELSTR_UnRotateRect,
	    RSELSTR_FNRSELSTR_CleanStr,
		RSELSTR_FNRSELSTR_TestForVertical,
		RSELSTR_FNRSELSTR_CutCompInTableZones

} RSELSTR_EXPORT_ENTRIES;

/*  �������� �������  */

#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RSELSTR_FUNC(a) b c

DEC_FUN(Bool32, RSELSTR_ExtractTextStrings,(Handle hCCOM,Handle hCPAGE));
DEC_FUN(Bool32, RSELSTR_PutObjects, (Handle hCPage,Handle hCCOM,CHSTR_Objects* pObjects,int nObjects)); 
DEC_FUN(Bool32, RSELSTR_CutStr, (Rect16** ppRc,int& nRc,int& len_mas_Rc,Word8* pRast,int DPIX,int DPIY,int str_w)); 
DEC_FUN(Bool32, RSELSTR_RotateRaster, (Word8* pmasp,int skew,Rect16* Rc,Int16* begx,Int16* movey,Word8* flmovey,int betw_str));
DEC_FUN(Bool32, RSELSTR_UnRotateRect, (int skew,Rect16* pRc,int nRc,Rect16 Rc,Int16* begx,Int16* movey,Word8* flmovey,int* hi));
DEC_FUN(void, RSELSTR_CleanStr, (Rect16* pN,CCOM_comp** pC,int& nN,int top,int left,int h,int w,int skew,Bool32 vertical));
DEC_FUN(Bool32, RSELSTR_TestForVertical, (CCOM_handle hCCOM,Handle hCPage,Rect16 RC,Bool32 neg,int param));
DEC_FUN(void, RSELSTR_CutCompInTableZones, (Handle hCPAGE,CCOM_handle hCCOM));

#undef DEC_FUN

typedef void   (*FNRSELSTR_ProgressStart)( void );
typedef	Bool32 (*FNRSELSTR_ProgressStep)(Word32 perc);
typedef	void   (*FNRSELSTR_ProgressFinish)( void );


#ifdef PPS_MAC
   #pragma export off
#endif
// error code


#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif
