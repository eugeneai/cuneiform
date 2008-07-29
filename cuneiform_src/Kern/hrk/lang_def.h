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

#ifndef _LANGDEF_INCLUDED_
 #define _LANGDEF_INCLUDED_

 #if defined (__NT__) || defined (_WINNT_) // 06.09.00 E.P.
  #undef LANG_ENGLISH
  #undef LANG_GERMAN
  #undef LANG_FRENCH
  #undef LANG_RUSSIAN
  #undef LANG_SWEDISH
  #undef LANG_SPANISH
  #undef LANG_ITALIAN
  #undef LANG_UKRAINIAN
  #undef LANG_TOTAL
  #undef LANG_SERBIAN
  #undef LANG_CROATIAN
  #undef LANG_DANISH
  #undef LANG_PORTUGUESE
  #undef LANG_DUTCH
  #undef LANG_TOTAL
  #undef LANG_POLISH
  #undef LANG_UZBEK
  #undef LANG_KAZ
  #undef LANG_KAZ_ENG
  #undef LANG_CZECH
  #undef LANG_ROMAN
  #undef LANG_HUNGAR
  #undef LANG_BULGAR
  #undef LANG_SLOVENIAN
  #undef LANG_LATVIAN
  #undef LANG_LITHUANIAN
  #undef LANG_ESTONIAN
  #undef LANG_TURKISH
 #endif

 #define LANG_ENGLISH     0
 #define LANG_GERMAN      1
 #define LANG_FRENCH      2
 #define LANG_RUSSIAN     3
 #define LANG_SWEDISH     4
 #define LANG_SPANISH     5
 #define LANG_ITALIAN     6
 #define LANG_RUSENG      7
 #define LANG_UKRAINIAN   8
 #define LANG_SERBIAN     9
 #define LANG_CROATIAN   10
 #define LANG_POLISH     11
 #define LANG_DANISH     12
 #define LANG_PORTUGUESE 13
 #define LANG_DUTCH      14
 #define LANG_DIG        15
 #define LANG_UZBEK      16
 #define LANG_KAZ        17
 #define LANG_KAZ_ENG    18
 #define LANG_CZECH      19
 #define LANG_ROMAN      20
 #define LANG_HUNGAR     21
 #define LANG_BULGAR     22
 #define LANG_SLOVENIAN  23
 #define LANG_LATVIAN	 24
 #define LANG_LITHUANIAN 25
 #define LANG_ESTONIAN	 26
 #define LANG_TURKISH	 27

 #define LANG_TOTAL      28

 #define LG_LAT          1
 #define LG_CYR          2


#endif


