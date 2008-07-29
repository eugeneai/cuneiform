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

#ifndef __R35_H
   #define __R35_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif
   #include "r35defs.h"
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __R35__
      #define R35_FUNC  FUN_EXPO
   #else
      #define R35_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
        #pragma export on
#endif
   R35_FUNC(Bool32)  R35InitNDX( MemFunc* mem);
   R35_FUNC(Bool32)  R35InitHND( MemFunc* mem);
   R35_FUNC(Bool32)  R35InitPRN( MemFunc* mem);
   R35_FUNC(Bool32)  R35Init( MemFunc* mem);
      // Start Initialization; TRUE - OK
      // for mem==NULL need used internal memory functions from DLL
      // New call - after close library without R35Done

   R35_FUNC(Bool32)  R35SetAlphabet(
        char*     char_tbl_put_to ); // char table[0-255]
      // Set alphabet for recognition

   R35_FUNC(Bool32)   R35Binarize(RecRaster *rRaster,
							   Word16 *CompImage,Int32 dx, Int32 dy);
   R35_FUNC(Bool32)   R35Binarize8(RecRaster *rRaster,
							   Word8 *CompImage,Int32 dx, Int32 dy);

   R35_FUNC(void)  R35SetPlatform( Int32 cpu );
   R35_FUNC(Bool32)   R35Pack(
       RecRaster*  raster,          // raster description
       Word16*  Image3x5,
       Int32 TO_X, Int32 TO_Y);       // result

   R35_FUNC(Bool32)   R35PackProport(
       RecRaster*  raster,          // raster description
       Word16*  Image3x5,
       Int32 TO_X, Int32 TO_Y);       // result

   R35_FUNC(Bool32)   R35PackProportHor16(
        RecRaster   *raster,
        Word16      *Image3x5, Int32    *to_x,  Int32   *to_y);

   R35_FUNC(Bool32)  R35RecogCharIm3x5(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res );

   R35_FUNC(Bool32)  R35RecogCharIm3x5_expert(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res );


   R35_FUNC(Bool32)  R35RecogPrintCharIm3x5(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res );

   R35_FUNC(Bool32)  R35RecogPrintCharIm3x5_expert(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res, Bool32 r5x3 );

   R35_FUNC(Bool32)  R35RecogNdxIm3x5(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res );

   R35_FUNC(Bool32)  R35RecogNdxIm3x5_expert(
      Word16*  Im3x5,         // image 3x5
      RecVersions* R35res );

   R35_FUNC(void)  R35Done(void);
      // Stop function. Call after R35Init()

   R35_FUNC(Int16) R35GetErr(void);
      // Err16.h defined codes or one of the next
  R35_FUNC(Bool32)  R35Init_learn( Int32 num, Word8 level, Int32 FontType );
  R35_FUNC(void)    R35Done_learn( Int32 FontType);
  R35_FUNC(Bool32)  R35RecogCharIm3x5_learn(
			Word8 Code,Word16* Im3x5/*, Bool32 r5x3*/, Int32 FontType  );
  R35_FUNC(Bool32)  R35RecogCharIm3x5_learn_expert(
            Word8 Code,Word16* Im3x5)  ;
  R35_FUNC(Bool32) R35Delete(Word8    let, Int32 num_del);
  R35_FUNC(Bool32) R35Add(Word8    let,Word16* Im3x5, Int32 FontType);
  R35_FUNC(void)   R35SetMTR(int fnt) ;
#ifdef PPS_MAC
        #pragma export off
#endif

// error code
#define ER_R35_NO_ERROR  0
#define ER_R35_NO_RECOG  1
#define ER_R35_TOO_SMALL 2
#define ER_R35_OPEN	     3
#define ER_R35_READ	     4
#define ER_R35_MEMORY	 5
#define ER_R35_NO_LOAD	 6
#define ER_R35_NO_LEVEL	 7
#define ER_R35_ALPHA     8
#define ER_R35_WRITE     9

   #ifdef __cplusplus
            }
   #endif

#endif

