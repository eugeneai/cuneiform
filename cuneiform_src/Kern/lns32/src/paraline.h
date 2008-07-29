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

#ifndef __PARALINE_H
#	define __PARALINE_H

	/*    Lines Extractor parameters and restrictions
	 *    09-07-93 07:32pm, Basil
	 */


	/* integral page restrictions */
// #define MAX_H_LINES_COUNT     4095 //2047       // result lines
// #define MAX_H_LINES_COUNT     8000 //2047       // result lines
   #define MAX_H_LINES_COUNT     16000             // result lines

//	#define MAX_H_RASTERS_COUNT   5400 // << max possible! 4095       // line fragments (filtred rasters)
//	#define MAX_H_RASTERS_COUNT   8000 // << max possible! 4095       // line fragments (filtred rasters)
	#define MAX_H_RASTERS_COUNT   16000 // << max possible! 4095       // line fragments (filtred rasters)

//	#define MAX_H_DASHES_COUNT    8192      // dashes at rasters
	#define MAX_H_DASHES_COUNT    16000     // dashes at rasters


#ifndef WIN32
	#define MAX_H_SEGMENTS_COUNT  16000     // filtred segments on page
#else // WIN32
	#define MAX_H_SEGMENTS_COUNT  32000     // filtred segments on page
#endif

	#define MAX_H_STRINGS_COUNT   4095      // rows/columns on page

// #define MAX_V_LINES_COUNT     4095 //2047      // result lines
//	#define MAX_V_LINES_COUNT     8000  //2047      // result lines
	#define MAX_V_LINES_COUNT     16000 //2047      // result lines

//	#define MAX_V_RASTERS_COUNT   5400 // << max possible! 4095      // line fragments (filtred rasters)
//	#define MAX_V_RASTERS_COUNT   8000 // << max possible! 4095      // line fragments (filtred rasters)
	#define MAX_V_RASTERS_COUNT   16000                              // line fragments (filtred rasters)
//	#define MAX_V_DASHES_COUNT    8192      // dashes at rasters
	#define MAX_V_DASHES_COUNT    16000     // dashes at rasters

#ifndef WIN32
	#define MAX_V_SEGMENTS_COUNT  16000     // filtred segments on page
#else // WIN32
	#define MAX_V_SEGMENTS_COUNT  32000     // filtred segments on page
#endif

	#define MAX_V_STRINGS_COUNT   4095      // rows/columns on page

   /* lines restrictions */
	#define MAX_ABS_INCLINE       0.2      // 11 may 99; old = 0.1 ~ 5.7 grad
	#define MAX_MyyMxx_RATIO      (int) 100	//


	/* fragment first pass linkage restrictions */
   // maximum level delta when fragments checked to be linked
	#define CHECK_FRAGMENTS_DELTA 24 // 15
	// Longitudinal restriction: unfilled space len * RATIO < summary fragments length
	#define LINK_FRAGMENTS_RATIO 		10
	// Crossline restriction: level delta < DELTA
	#define LINK_FRAGMENTS_DELTA 		5        	// maximum delta when fragments can be linked
   // Maximum gap between fragments
   #define LINK_FRAGMENTS_GAP          40

	#define UPDATE_LINES_STRICT_RATIO   20
	#define UPDATE_LINES_STRICT_DELTA   3

	#define UPDATE_LINES_RATIO          5
	#define UPDATE_LINES_DELTA          7

	//obsolete #define MIN_H_LINE_LEN				80
	//obsolete #define MIN_V_LINE_LEN				60


#endif
