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

#ifndef __RLINE_H
#define __RLINE_H

#ifndef __GLOBUS_H
#include "globus.h"
#endif
/*
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"
*/
#ifdef __RLINE__
  #define RLINE_FUNC  FUN_EXPO
#else
  #define RLINE_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
        extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif

#define __XTYPES_H
#define RLINE_BLOCK_TYPE CPAGE_GetInternalType("RLINE_BLOCK_TYPE")

RLINE_FUNC(Bool32) RLINE_Init(Word16 wHeightCode,void * hStorage);
RLINE_FUNC(Bool32) RLINE_Done();
RLINE_FUNC(Word32) RLINE_GetReturnCode();
RLINE_FUNC(Int8 *) RLINE_GetReturnString(Word32 dwError);
RLINE_FUNC(Bool32) RLINE_GetExportData(Word32 dwType, void * pData);
RLINE_FUNC(Bool32) RLINE_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////

typedef enum 
{
        RLINE_FNRLINE_SearchLines =1,
        RLINE_FNRLINE_DeleteLines,
        RLINE_Bool32_NOFILLGAP3,
        RLINE_Bool32_NOHBORDER,
        RLINE_Bool32_NOVBORDER,
		RLINE_FNRLINE_LinesPass1,
		RLINE_FNRLINE_LinesPass2,
		RLINE_FNRLINE_LinesPass3
} RLINE_EXPORT_ENTRIES;


#define DEC_FUN(a,b,c) typedef a (*FN##b)c; RLINE_FUNC(a) b c

DEC_FUN(Bool32,  RLINE_SearchLines,(void* lpInPage,void* hpCLINE)); 
DEC_FUN(Bool32,  RLINE_DeleteLines,(void* lpInPage , char* lpOutDIB));
DEC_FUN(Bool32,  RLINE_LinesPass1, (Handle hCPage,Handle hCCOM,void* phCLINE,PBool32 pgneed_clean_line, Bool32 sdl, Word8 lang)); 
DEC_FUN(Bool32,  RLINE_LinesPass2, (Handle hCCOM,void* phCLINE, Handle hCPAGE)); 
DEC_FUN(Bool32,  RLINE_LinesPass3, (Handle hCPage,Word32 hCLINE, Handle hCCOM, Word8 lang)); 
//DEC_FUN(Bool32,  RLINE_DeleteLines,(void* lpInName , void* lpDIB, void** lpOutName)); 

/*
DEC_FUN();
DEC_FUN();
DEC_FUN();
*/
#undef DEC_FUN



#ifdef PPS_MAC
   #pragma export off
#endif
// error code



#ifdef __cplusplus
            }
#endif

#endif
