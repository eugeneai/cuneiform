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

#ifndef __XPATH_H
#define __XPATH_H

#ifndef __XTEXT_H
#include "xtext.h"
#endif

#include "compat_defs.h"

class XPath : public XText< _MAX_PATH >
{
public:
   XPath(void):
      XText< _MAX_PATH >(""){};

   XPath(const char* path ):
      XText< _MAX_PATH >(path)
   {};

   XPath& operator = (const char * path )
      {
         *(XText< _MAX_PATH >*)this = path;
         return *this;
      }

   XPath& operator = (const XText< _MAX_PATH >& path )
      {
         *(XText< _MAX_PATH >*)this = path;
         return *this;
      }

   XPath(const char* dir, const char* name, const char* ext):
      XText< _MAX_PATH >()
   {
      make_path(buf, dir, name, ext);
   };

   XPath& GetModuleFileName(HMODULE hModule = NULL)
   {
      ::GetModuleFileName( hModule, buf, sizeof(buf) );
      return *this;
   };

   XPath& GetCurrentDirectory(void)
   {
      curr_dir( sizeof(buf), buf );
      return *this;
   };

   XPath& GetTempPath(void)
   {
      ::GetTempPath( sizeof(buf), buf );
      return *this;
   }

   XPath& CutPath(void) // ��������� ������ ���� (��� ����� � ����������)
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];

      split_path(buf, dir, name, ext);
      make_path(buf, dir, NULL, NULL);
      return *this;
   }

   XPath& CutName(void) // ��������� ������ ��� (��� ����������)
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];

      split_path(buf, dir, name, ext);
      make_path(buf, NULL, name, NULL);
      return *this;
   }

   XPath& CutNameEx(void) // ��������� ������ ��� (� �����������)
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];

      split_path(buf, dir, name, ext);
      make_path(buf, NULL, name, ext);
      return *this;
   }

   XPath& CutExt(void)
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];

      split_path(buf, dir, name, ext);
      make_path(buf, NULL, NULL, ext);
      return *this;
   }


   XPath& SetExt(const char* new_ext) // �������� ��� ��������� ����� ����������
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];

      split_path(buf, dir, name, NULL);
      make_path(buf, dir, name, new_ext);
      return *this;
   };

   XPath& CheckSlash(void)        // ��������� � ��������� ���� � ����� ���� ���
   {
      int len=strlen(buf);
      if (buf[0] && buf[len-1] != '/' )
      {
         buf[len]='/';
         buf[len+1]=0;
      }

      return *this;
   }

   XPath& StripSlash(void)        // ��������� � ������� ���� � ����� ���� ����
   {
      int len=strlen(buf);
      if (buf[0] && buf[len-1] == '/' )
      {
         buf[len-1]=0;
      }

      return *this;
   }

   XPath& SetName(const char* new_name) // �������� ��� ��������� ����� ���+����
   {
      char dir[_MAX_DIR];

      split_path(buf, dir, NULL, NULL);
      make_path(buf, dir, new_name,NULL);
      return *this;
   };

   XPath& EraseDrive() // ������� �������� �����
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];
      split_path(buf, dir, name, ext);
      make_path(buf, dir, name,ext);
      return *this;
   };

   XPath& SetDrive(const char* pDrive) // ������� �������� �����
   {
      char dir[_MAX_DIR];
      char name[_MAX_FNAME];
      char ext[_MAX_EXT];
      split_path(buf, dir, name, ext);
      make_path(buf, dir, name,ext);
      return *this;
   };

   void Split(char* pDir, char* pFileName, char* pExt) // ��������� ���� �� ����������
   {
      split_path(buf, pDir, pFileName, pExt);
   };

};

#endif // XPath
