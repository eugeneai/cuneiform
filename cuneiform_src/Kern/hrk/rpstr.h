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

////////////////////////////////////////////////////////////
// POST CORRECTION STRINGS FROM CONTAINER                 //
////////////////////////////////////////////////////////////
// O.Slavin                                               //
////////////////////////////////////////////////////////////
// Creation     : 26 Mar 1999                             //
////////////////////////////////////////////////////////////
// Modification : 26 Mar 1999                             //
////////////////////////////////////////////////////////////
// Copyright (C) Cognitive Technologies Ltd, 1999         //
// All rights reserved. This program is proprietary and   //
// a trade secret of Cognitive Technologies Limited.      //
////////////////////////////////////////////////////////////
#ifndef __RPSTR_H
   #define __RPSTR_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

   #include "ccomdefs.h"
   #include "cstrdefs.h"

#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __RPSTR__
      #define RPSTR_FUNC  FUN_EXPO
   #else
      #define RPSTR_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
   #pragma export on
#endif

#include "cttypext.h"

   RPSTR_FUNC(Bool32)  RPSTR_Init( Word16 wHeightCode , Handle hStorage);
   RPSTR_FUNC(void)    RPSTR_Done(void);
   RPSTR_FUNC(Word32)  RPSTR_GetReturnCode(void);
   RPSTR_FUNC(char*)   RPSTR_GetReturnString(Word32 dwError);
   RPSTR_FUNC(Bool32)  RPSTR_SetImportData(Word32 dwType, void * pData);
   RPSTR_FUNC(Bool32)  RPSTR_GetExportData(Word32 dwType, void * pData);

    enum RPSTRFunctionsExt
        {
//        RPSTR_FNCORRECTKEGL,
        RPSTR_FNNEWPAGE,
        RPSTR_FNCORRECTSPELL,
        RPSTR_FNCORRECTINCLINE,
        RPSTR_FNCOLLECTCAPDROP,
		RPSTR_FNNORMVERTSTR,
        RPSTR_FNCORRECTLINESPELL
        };
    enum RPSTRFunctionsImp
        {
        RPSTR_FNIMP_ALLOC,
        RPSTR_FNIMP_REALLOC,
        RPSTR_FNIMP_FREE,
        RPSTR_FNIMP_OPEN,
        RPSTR_FNIMP_CLOSE,
        RPSTR_FNIMP_READ,
        RPSTR_FNIMP_WRITE,
        RPSTR_FNIMP_LANGUAGE,
        RPSTR_Bool32_Fax100
        };

/*moved to ... module
// 1    RPSTR_FNCORRECTKEGL      correct kegl in all string
typedef Bool32 (*FNRPSTR_CorrectKegl)(Int32 version);
RPSTR_FUNC(Bool32)  RPSTR_CorrectKegl (Int32 version);
*/

// 2    RPSTR_FNNEWPAGE          init new page
typedef Bool32 (*FNRPSTR_NewPage)(void);
RPSTR_FUNC(Bool32) RPSTR_NewPage(void);
// 3    RPSTR_FNCORRECTSPELL      spelling checker
typedef Bool32 (*FNRPSTR_CorrectSpell)(Int32 version);
RPSTR_FUNC(Bool32)  RPSTR_CorrectSpell(Int32 version);
// 4    RPSTR_FNCORRECTINCLINE
typedef Bool32 (*FNRPSTR_CorrectIncline)(Int32 version);
RPSTR_FUNC(Bool32) RPSTR_CorrectIncline(Int32 version);
// 5    RPSTR_FNCOLLECTCAPDROP
typedef Bool32 (*FNRPSTR_CollectCapDrops)(Int32 version);
RPSTR_FUNC(Bool32) RPSTR_CollectCapDrops(Int32 version);
// 6    RPSTR_FNNORMVERTSTR
typedef void (*FNRPSTR_NormalizeVertStr)(void);
RPSTR_FUNC(void) RPSTR_NormalizeVertStr(void);
//7 RPSTR_FNCORRECTLINESPELL      spelling checker for given line
typedef Bool32 (*FNRPSTR_CorrectLineSpell)(CSTR_line line, Int32 line_num, CSTR_rast* re, CSTR_rast* rb, Int32* rf);
RPSTR_FUNC(Bool32) RPSTR_CorrectLineSpell(CSTR_line line, Int32 line_num, CSTR_rast* re, CSTR_rast* rb, Int32* rf);

#ifdef PPS_MAC
   #pragma export off
#endif
// error code



   #ifdef __cplusplus
            }
   #endif

#endif
