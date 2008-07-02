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

#ifndef __MSK_H
   #define __MSK_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

   /*#include "mskdefs.h"*/
   #include "memfunc.h"
   #include "recdefs.h" 

   #ifdef __MSK__
      #define MSK_FUNC  FUN_EXPO
   #else
      #define MSK_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

  MSK_FUNC(void)    MSKSetPlatform(Int32 cpu);

///
  MSK_FUNC(Bool32)  MSKInit( MemFunc* mem, const char *NameFile );
		// Start Initialization; TRUE - OK
		// for mem==NULL need used internal memory functions from DLL
    // New call - after close library without MSKDone

  MSK_FUNC(Bool32)  MSKSetAlphabet
                       (
                        char  char_tbl_put_to[] // char table[0-255]
                       );
			// Set alphabet for recognition

  MSK_FUNC(Bool32)  MSKRecogChar(
			int HndTab,
			RecRaster* raster, // raster description
			RecVersions*    MSKres            );  // acuracy


  MSK_FUNC(Bool32)  MSKRecogCharExp(
			int HndTab,
			RecRaster  *recraster, // raster description
			RecVersions *Indres    );
  MSK_FUNC(Bool32)  MSKRecogCharExpPuma(
			int HndTab,
			RecRaster  *recraster, // raster description
			RecVersions *Indres,
            Word32    Flags     );

  MSK_FUNC(Bool32)  MSKSetHndTab(int HndTab);

  MSK_FUNC(void)  MSKDone(void);
			// Stop function. Call after LEOInit()

  MSK_FUNC(Int16) MSKGetErr(void);
			// Err16.h defined codes or one of the next
			//
  
  MSK_FUNC(Bool32)  MSKRecogNDX(
      RecRaster  *recraster, // raster description
      RecVersions *Indres           );


   #ifdef __cplusplus
            }
   #endif

#endif

