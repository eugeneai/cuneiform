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

#ifndef __MMX_H
   #define __MMX_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif
   #include "evndefs.h"
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __MMX__
      #define MMX_FUNC  FUN_EXPO
   #else
      #define MMX_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
   #pragma export on
#endif

// for R35.dll
MMX_FUNC(Word32)    MMX_scalar(Word32 _EAX, Word32 _EDX);
MMX_FUNC(Word32)    MMX_scalar16_(Word32  _EAX, Word32 _EDX);
MMX_FUNC(void)      MMX_open_image(Word16 *_EAX);
MMX_FUNC(void)      MMX_close_image(void);
MMX_FUNC(Word32)    MMX_scalar_sq(Word16 *_EAX,Int32 _ECX);
MMX_FUNC(void)      MMX_scale( Word16 *_EAX, Int32 _ECX, Int32 _EDX);
MMX_FUNC(void)      MMX_binarize_16x16(Word16 *rin,Word8 *rout);

// for NET.dll
MMX_FUNC(Word32)    MMX_scalarUni (Int16 * _EAX, Int16 * _EDX, Int32 num);
MMX_FUNC(Word32)    MMX_scalar16 (Int16 * _EAX, Int16 * _EDX);
MMX_FUNC(Word32)    MMX_scalar36 (Int16 * _EAX, Int16 * _EDX);

// for  GRA.dll
MMX_FUNC(void)      MMX_addshab_cykl(int * src, int cg, signed char * dst, int num);
MMX_FUNC(void)      MMX_addshab(int * src, int cg, signed char * dst);

// for IND.dll
MMX_FUNC(void)      MMX_ind_setup_table(Word32 *bit_cnt0);
MMX_FUNC(Bool32)    MMX_anding(Int32 *image,Word16 *etalons,Int32 L);
MMX_FUNC(void)      MMX_open( Int32 *image);
MMX_FUNC(void)      MMX_close(void);

   #ifdef __cplusplus
            }
   #endif

#endif
