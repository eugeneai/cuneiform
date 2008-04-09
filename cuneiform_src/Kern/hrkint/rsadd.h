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
// ANALIZER OF THE CELL OF TABLES                         //
////////////////////////////////////////////////////////////
// O.Slavin                                               //
////////////////////////////////////////////////////////////
// Creation     : 24 Seb 1999                             //
////////////////////////////////////////////////////////////

#ifndef __RAGR_H
   #define __RAGR_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

#include "cttypext.h"
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __RSADD__
      #define RSADD_FUNC  FUN_EXPO
   #else
      #define RSADD_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
   #pragma export on
#endif

enum RSADDFunctionsExt
        {
        RSADD_TAKE,
		RSADD_GETALIASES,
		RSADD_GETALIASCLASS,
		RSADD_KILL_DUSTS,
		RSADD_SETRSTR
		};

RSADD_FUNC(Bool32)  RSADD_Init( Word16 wHeightCode, Handle hStorage );
RSADD_FUNC(void)    RSADD_Done(void);
RSADD_FUNC(Word32)  RSADD_GetReturnCode(void);
RSADD_FUNC(char*)   RSADD_GetReturnString(Word32 dwError);
RSADD_FUNC(Bool32)  RSADD_SetImportData(Word32 dwType, void * pData);
RSADD_FUNC(Bool32)  RSADD_GetExportData(Word32 dwType, void * pData);

// 1	RSADD_TAKE			������� ������� ������� ���� �����
typedef Bool32  (*FNRSADD_take)(CSTR_line lrus,CSTR_line leng);
RSADD_FUNC(Bool32)  RSADD_take(CSTR_line lrus,CSTR_line leng);
// 2	RSADD_GETALIASES	������ ����������� ��������
typedef Word8*  (*FNRSADD_get_aliases)( Word8 letter,   Word8 language, Word8 alias_class);
RSADD_FUNC(Word8*)  RSADD_get_aliases( Word8 letter,   Word8 language, Word8 alias_class);
// 3	RSADD_GETALIASCLASS	����� ����������� ��������
#define RSADD_as_none       0
#define RSADD_as_equal      1
#define RSADD_as_alias      2
#define RSADD_as_similar    4
typedef Word8   (*FNRSADD_get_alias_class)(Word8 letter,Word8 language);
RSADD_FUNC(Word8)   RSADD_get_alias_class(Word8 letter,Word8 language);
// 4 RSADD_KILL_DUSTS		���������� ������ �����
typedef void    (*FNRSADD_kill_dusts)(CSTR_line lrus);
RSADD_FUNC(void )   RSADD_kill_dusts(CSTR_line lrus);
// 5 RSADD_SETRSTR			���� ���������� � ������� �� �-�� RSTR
typedef void    (*FNRSADD_SetRSTR)( Word8 status,Word8 camera, 
                                Handle monitor_ori,
                                Handle activity,
                                Handle show_text);
RSADD_FUNC(void) RSADD_SetRSTR( Word8 status,Word8 camera, 
                                Handle monitor_ori,
                                Handle activity,
                                Handle show_text);
   #ifdef __cplusplus
            }
   #endif

#endif