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

//#define REXC_ERR_MIN                2048
//#define REXC_ERR_NO                 2048
//#define REXC_ERR_NOTOPERATE         2049
//#define REXC_ERR_NOMEMORY           2050
//#define REXC_ERR_NOTIMPLEMENT       2051
//#define REXC_ERR_INTERNAL           2052
//#define REXC_ERR_DUMPOPEN           2053
//#define REXC_ERR_DUMPWRITE          2054
//#define REXC_ERR_CALLBACK           2055
//#define REXC_ERR_PARAM              2056
//#define REXC_ERR_NOCOMP             2057
//#define REXC_ERR_NOINITEV           2058
//#define REXC_ERR_DIFVERSIONS        2059
//#define REXC_ERR_NOIMPORT           2060
//#define REXC_ERR_NOEXPORT           2061
//#define REXC_ERR_NOLANGUAGE         2062
//#define REXC_ERR_NOSETALPHABET      2063
//#define REXC_ERR_NOGRA              2064
//#define REXC_ERR_USE                2065
//#define REXC_ERR_NOTENOUGHTMEMORY   2066
//#define REXC_ERR_GETORIENT          2067
//#define REXC_ERR_IMAGEINFO          2068
//#define REXC_ERR_MAX                2068
static char *REXC_error_name[]={
  "No error",
  "Can't operate",
  "Not enough memory",
  "Not inmpement",
  "Internal error - call developer",
  "Can't open DumpFile",
  "DumpFile writing error",
  "External CallBack error",
  "Bad Parameters of call",
  "Empty Page",
  "Can't init eventual-library",
  "Different versions of REXC and CCOM",
  "Can't import",
  "Can't export",
  "Language not exist",
  "Can't init language",
  "Can't init networks",
  "Already init",
  "Not enough memory",
  "Failed to rotate page automatically. Rotate page manually and turn off Autorotate option, then recognize page again.",
  "Bad image information",
  ""
};