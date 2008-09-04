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

#ifndef __LNS_H
   #define __LNS_H

#ifndef __IMGACCS_H
   #include "imgaccs.h"
#endif

#ifndef __LNSDEFS_H
   #include "lnsdefs.h"
#endif

#ifndef __SNPDEFS_H
   #include "snpdefs.h"
#endif

   #ifdef __LNS__
      #define LNS_FUNC    FUN_EXPO
   #else
      #define LNS_FUNC    FUN_IMPO
   #endif
	#include "cline.h"
typedef struct tagLnsSetupStr
{
   Int32 nOptions;
#define LSS_NOVBORDER_FILTER     0x0001   // ���������� ������ �� �����-������ �������
#define LSS_NOHBORDER_FILTER     0x0002   // ���������� ������ �� �������-������ �������
#define LSS_NOFILLGAP3_FILTER    0x0004   // ���������� ������������ �� 3 ������� (����������)
   char  buffer[60]; // ������, ����������� 0
} LnsSetupStr;

   #ifdef __cplusplus
      extern "C" {
   #endif

   LNS_FUNC( void )            LnsPageStart( TImageAccess* img );

   LNS_FUNC( Bool16 )          LnsSetup( LnsSetupStr* ls ); // can call before LnsExtractLines

   LNS_FUNC( Bool16 )          LnsExtractLines( Int32   min_h_len,
                                                Int32   min_v_len,
                                                Int32*  result_h_count,
                                                Int32*  result_v_count
                                              );
/*   LNS_FUNC( Bool16 )          MyLnsExtractLines( Int32   min_h_len,
                                                Int32   min_v_len,
                                                Int32*  result_h_count,
                                                Int32*  result_v_count
                                              );*/
   //LNS_FUNC( Bool16 )			ExtractAllComponents( LinesTotalInfo          *lti );
   LNS_FUNC( Bool16 )			ExtractAllEvents(CLINE_handle hCLINE, LinesTotalInfo          *lti);
   LNS_FUNC( Bool16 )          LnsGetCount( Int32   min_h_len,
                                            Int32   min_v_len,
                                            Int32*  result_h_count,
                                            Int32*  result_v_count
                                          );

   //.....�������� ����������..............................
   LNS_FUNC( int ) LnsGetFragCount( Bool horisontal );
   LNS_FUNC( LnsFrag* ) LnsGetFragments( Bool horisontal );
   //......................................................

   LNS_FUNC( Bool16 )          LnsUpload( LinesTotalInfo* lti,
                                          Int32   min_h_len,
                                          Int32   min_v_len
                                        );

   LNS_FUNC( Rect16* )         LnsGetBlackSquares( Int32* count );
      // 04 dec 1998 - black squares upload
   LNS_FUNC( Rect16* )         LnsGetCheckBoxes( Int32* count );
      // 11 feb 1998 - checkboxes upload

   LNS_FUNC( TImageAccess* )   LnsGetSweepedImage( LinesTotalInfo* lti );
   LNS_FUNC( Err16 )           LnsGetError();
   LNS_FUNC( void )            LnsPageFinish();

   //////////////////////////////////////////////////////////////////////
   // set-get options from lns32.ini (located at the same place as .exe)
   LNS_FUNC( void )   LnsSetSection( char* szSection ); // 63 chars max
   LNS_FUNC( Word32 ) LnsGetProfileInt(const char* szKey, int nDefault );
   LNS_FUNC( Word32 ) LnsGetProfileString( char* szKey,
                            char* szResult, int nResult,
                            char* szDefault// = NULL
                          );
   LNS_FUNC( Bool32 ) LnsWriteProfileInt( char* szKey, int nValue );
   LNS_FUNC( Bool32 ) LnsWriteProfileString( char* szKey, char* szValue );
   //////////////////////////////////////////////////////////////////////
   LNS_FUNC( void   )      LnsRegisterSnpTree(
                     SnpTreeNode* parent,         // parent Snp Node, may be NULL
                     __SnpToolBox* p_snp_tools     // tools complect, may be NULL
                              );


   #ifdef __cplusplus
               }
   #endif

#endif



