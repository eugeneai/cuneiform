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


#ifndef PPS_MAC
#pragma message(__FILE__)
#endif
#ifndef __p2_H
   #define __p2_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

   #include "p2defs.h"
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __P2__
      #define P2_FUNC  FUN_EXPO
   #else
      #define P2_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif
#ifdef PPS_MAC
        #pragma export on
#endif

	// return < 0 - error
    P2_FUNC(Int32)  p2_proc(CSTR_line lineRaw,CSTR_line lineOne,P2GLOBALS *P2globals);
	P2_FUNC(Int32)  p2_recog(RecRaster *recRast,RecVersions *vers,void *specInfo,Int32 testSelf);
	// ���������� ���������� � �������� �������������
    P2_FUNC(Int32)  p2_RecogCompLp(Int16 sizeLp,Word8 *lp,Int16 w,Int16 h,
					 Int16 col,Int16 row,RecVersions *vers);
	P2_FUNC(Int32)  p2_rotate(RecRaster *recRast);

	P2_FUNC(Bool32) p2_Comp2Raster(Int16 sizeLP,Word8 *lp,Int16 w,Int16 h,RecRaster *rec);

	P2_FUNC(void)   p2_SetShowWords(Bool32 val);
	P2_FUNC(Bool32) p2_GetShowWords(void);
    P2_FUNC(void)   p2_SetStopBound(int stopCol);
	P2_FUNC(Bool32) p2_stopPlace(void);

	P2_FUNC(void) P2_SetRSTR( Handle RecogCutGlu,
                             Handle setAlpha,Handle GetPage,Handle Decode,
                             Handle NoStopSnapLEO, Handle monitor_ori,
                              Handle activity,     Handle show_text,
                              Handle spell,
							  Handle setupPage, Handle setupField,
							  Handle specRecog);

///////////////////////
// error code
#define ER_P2_NO_ERROR  0
#define ER_P2_NO_RECOG  1
#define ER_P2_MEMORY    4

#ifdef PPS_MAC
        #pragma export off
#endif

   #ifdef __cplusplus
            }
   #endif

#endif

