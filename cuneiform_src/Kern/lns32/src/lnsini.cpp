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

#include "lnslang.h"

/*#include <windows.h>*/
#include "compat_defs.h"

#include "lns.h"


char* ChangEx( char* szPath, char* szEx )
{
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   split_path(szPath, dir, fname, ext);
   make_path(szPath, dir, fname, szEx);
   return szPath;
}
char* ChangNameEx( char* szPath, char* szNameEx )
{
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   split_path(szPath, dir, fname, ext);
   make_path(szPath, dir, szNameEx, NULL);
   return szPath;
}

char   szIniFileName[_MAX_PATH]={0};
char   szSection[64] = "Default";

LNS_FUNC( void )   LnsSetSection( char* _szSection ) // 63 chars max
{
   strncpy(szSection, _szSection, sizeof(szSection)-1);
}

LNS_FUNC( Word32 ) LnsGetProfileInt( char* szKey, int nDefault )
{
   if (szIniFileName[0]==0)
   {
      GetModuleFileName(NULL, szIniFileName, sizeof(szIniFileName));
      ChangNameEx(szIniFileName, "lns32.ini");
   }

   return GetPrivateProfileInt(szSection, szKey, nDefault, szIniFileName);
}

LNS_FUNC( Word32 ) LnsGetProfileString(   char* szKey,
                                          char* szResult, int nResult,
                                          char* szDefault
                                       )
{
   if (szIniFileName[0]==0)
   {
      GetModuleFileName(NULL, szIniFileName, sizeof(szIniFileName));
      ChangNameEx(szIniFileName, "lns32.ini");
   }

   static char szDef[4]={0};
   if (szDefault == NULL)
   {
      szDefault = szDef;
   }

   return GetPrivateProfileString(szSection, szKey, szDefault, szResult, nResult, szIniFileName);
}

LNS_FUNC( Bool32 ) LnsWriteProfileInt( char* szKey, int nValue )
{
   char szValue[256]; sprintf( szValue, "%d", nValue );
   return LnsWriteProfileString( szKey, szValue );
}

LNS_FUNC( Bool32 ) LnsWriteProfileString( char* szKey, char* szValue )
{
   if (szIniFileName[0]==0)
   {
      GetModuleFileName(NULL, szIniFileName, sizeof(szIniFileName));
      ChangNameEx(szIniFileName, "Lns32.ini");
   }

   return WritePrivateProfileString(szSection, szKey, szValue, szIniFileName);
}
