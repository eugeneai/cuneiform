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

#ifndef __EVN_H
   #define __EVN_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif
   #include "evndefs.h"
//   #include "excdefs.h" 
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"
   #include "ccomdefs.h"

   #ifdef __EVN__
      #define EVN_FUNC  FUN_EXPO
   #else
      #define EVN_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
   #pragma export on
#endif
   
   EVN_FUNC(Bool32)  EVNInitHND( MemFunc* mem );
   EVN_FUNC(Bool32)  EVNInitPRN( MemFunc* mem );
   EVN_FUNC(Bool32)  EVNInit( MemFunc* mem );
      // Start Initialization; FALSE - ��㤠�
      // for mem==NULL need used inter nal memory functions from DLL
      // New call - after close library without EVNDone

  EVN_FUNC(Bool32)  EVNSetAlphabet(
                        char*     char_tbl_put_to // char table[0-255]
                   );
      // Set alphabet for recognition

   EVN_FUNC(Bool32)  EVNRecogChar(   RecRaster  * rRaster, 
      RecVersions* EVNres       );  
   EVN_FUNC(Bool32)  EVNRecogCharPRN(   RecRaster  * rRaster, 
      RecVersions* EVNres       );   

   
   EVN_FUNC(void)  EVNDone(void);
      // Stop function. Call after EVNInit()

   EVN_FUNC(Int16) EVNGetErr(void);
      // Err16.h defined codes or one of the next
      //

   EVN_FUNC(Word8*) EVNMakeLine( RecRaster   *rRaster,Int32 parm);
   EVN_FUNC(MN *)   EVN_CLocomp (Word8* raster, Int32 bw, Int32 h, 
        Int16 upper,Int16 left);
   EVN_FUNC(Int32)  EVNGetNumComp(   RecRaster   *rRaster  )  ;
   EVN_FUNC(Int32)  EVNGetRepresent(  RecRaster   *rRaster,
        Word8 *evn, Word8 *evn_rot, Int32 font       );
   EVN_FUNC(Int32)  EVNRecog_lp( /* ExtComponent*/CCOM_comp *ec, Word8   *lp, 
        Word16 lth, Word8   *res);
   EVN_FUNC(Word8*) EVN_GetSegmentPool(void);
   EVN_FUNC(Bool32) EVNInitLanguage( char *tabevn1, char *tabevn2,Word8 lang);
   EVN_FUNC(Bool32) EVNSetLanguage( Word8 lang);
#ifdef PPS_MAC
   #pragma export off
#endif


// error code
#define ER_EVN_NO_ERROR 0
#define ER_EVN_NO_RECOG 1
#define ER_EVN_OPEN     2
#define ER_EVN_MEMORY   3
#define ER_EVN_READ     4

   #ifdef __cplusplus
            }
   #endif

#endif
