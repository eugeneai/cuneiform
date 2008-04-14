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

#pragma message(__FILE__"(1)  :")
#ifndef __XFINDFIL_H
#define __XFINDFIL_H

// files enumeration: _finsfirst() - _findnext()..._findnext() - _findclose()
#include <io.h>
#include "XPath.h"
#include "SafeStr.h"

class XFindFile   // xff
{
   _finddata_t fileinfo;
   long hFind;
   Bool can_reply;
   XPath xpTpl;

public:
   XFindFile( void ): hFind(-1), can_reply(FALSE){};
   XFindFile( const char* name_template ): hFind(-1), can_reply(FALSE){ Restart(name_template); };
   
   const char* GetSource () { return xpTpl; } /*VMK*/
   
   Bool Restart( const char* name_template=NULL )
   {  
      if (name_template)
         xpTpl = name_template;
      if (hFind != -1)
         _findclose(hFind);
      hFind = _findfirst( xpTpl, &fileinfo );
      can_reply = (hFind != -1); 
      return can_reply;
   }

   XFindFile& operator ++(void) // prefix form:  use '++xff' to get next file
   { 
      can_reply = (_findnext(hFind, &fileinfo)==0);
      return *this;
   }

   operator char * (void) { return can_reply ? (char*)fileinfo.name : NULL; }
   char* SafeStr(void)    { return can_reply ? (char*)fileinfo.name : "";   }
   Word32 FileAttrib(void)    { return can_reply ? (Word32)fileinfo.attrib : 0;   }
   Bool  IsArchive (void) { return fileinfo.attrib & _A_ARCH  ; };//  Archive. Set whenever the file is changed, and cleared by the BACKUP command. Value: 0x20
   Bool  IsHidden  (void) { return fileinfo.attrib & _A_HIDDEN; };//  Hidden file. Not normally seen with the DIR command, unless the /AH option is used. Returns information about normal files as well as files with this attribute. Value: 0x02
   Bool  IsNormal  (void) { return fileinfo.attrib & _A_NORMAL; };//  Normal. File can be read or written to without restriction. Value: 0x00
   Bool  IsReadOnly(void) { return fileinfo.attrib & _A_RDONLY; };//  Read-only. File cannot be opened for writing, and a file with the same name cannot be created. Value: 0x01
   Bool  IsSubdir  (void) { return fileinfo.attrib & _A_SUBDIR; };//  Subdirectory. Value: 0x10
   Bool  IsSystem  (void) { return fileinfo.attrib & _A_SYSTEM; };//  System file. Not normally seen with the DIR command, unless the /A or /A:S option is used. Value: 0x04
   ~XFindFile(void)
   {
      if (hFind != -1)
         _findclose(hFind);
      hFind = -1;
   }
};

class XEnumDirs // xed  - directories enumeration
{
   _finddata_t fileinfo;
   long hFind;
   Bool can_reply;
   int nOptions;

#define XED_NO_PARENT   0x0001                           // no ..
#define XED_NO_CURRENT  0x0002                           // no .
#define XED_ONLY_SUBDIR (XED_NO_CURRENT|XED_NO_PARENT)   // no .  and  ..

   void Init(void)      { can_reply = FALSE; hFind = -1; nOptions=0; };

public:
   XEnumDirs( void )  { Init(); };
   XEnumDirs( const char* name_template, int options = 0 )
      { Init(); Restart(name_template, options); };

   void Restart( const char* name_template, int options = 0  )
   {  
      nOptions = options;
      if (hFind != -1)
      {
         _findclose(hFind);
         hFind = -1;
      }
      can_reply = FALSE;

      hFind = _findfirst( name_template, &fileinfo );
      if (hFind != -1)
      {  
         while (!IsAcceptable())
         {  
            if (_findnext(hFind, &fileinfo)!=0)
               return; // with can_reply == FALSE;
         }
         can_reply = TRUE;
      }
   }

   Bool32 IsAcceptable(void)
   {
      if (!(fileinfo.attrib & _A_SUBDIR))
         return FALSE;
      if (fileinfo.name[0]=='.')
      {
         if (nOptions & XED_NO_PARENT && strcmp(fileinfo.name, "..") == 0)
            return FALSE;
         if (nOptions & XED_NO_CURRENT && strcmp(fileinfo.name, ".") == 0)
            return FALSE;
      }
      return TRUE;
   }

   XEnumDirs& operator ++(void) // prefix form:  use '++xed' to get next subdirectory
   { 
      can_reply = FALSE;
      do 
      {  if (_findnext(hFind, &fileinfo)!=0)
            return *this; // with can_reply == FALSE;
      }  while (!IsAcceptable());
      can_reply = TRUE;
      return *this;
   }

   operator char * (void) { return can_reply ? (char*)fileinfo.name : NULL; }
   char* SafeStr(void)    { return can_reply ? (char*)fileinfo.name : "";   }

   ~XEnumDirs(void)
   {
      if (hFind != -1)
         _findclose(hFind);
      hFind = -1;
   }
};

class XEnumDirsRecursive // xedr  - ������������� ���������� � ���������������
{
   XEnumDirs xed;                 // ������������� ��� ������� ����������
   XEnumDirsRecursive* pxedr;     // ������������� �������������
   int nDir;                      // ����� ������ szDir ����� ������� � �������������

static char szReply[260];         // ����� ��� ������������ �������� ������
static char szNameTpl[260];       // ������ �����, ����. "*.*"
static char szDir[260];           // ����������� ���������� ��� ����� �� �����


   void Restart(void)                // �� �����: � szDir - ���������� ������� ����� �����������, 
                                     //           � szNameTpl - ������ ����� ����������
   {
      char tpl[260];
      sprintf(tpl, "%s\\%s", szDir, szNameTpl); 
      xed.Restart( tpl, XED_ONLY_SUBDIR );
      if (xed)
      {
         //strcpy(szReply, xed);        // ����������� ������ ����� (� szReply)
         sprintf(szReply, "%s\\%s", szDir, SafeStr(xed) );
      }
      else
         szReply[0]=0;
   }

public:
   XEnumDirsRecursive(void): pxedr(NULL){};
   XEnumDirsRecursive(                // ����������� ��� ���������� ������
      const char* root_dir,   // �������� "C:\WINDOWS" ��� "\\server\d\backup\" ��� "..\.."
      const char* name_tpl = "*.*" 
                     ):
      pxedr(NULL)
   { 
      Restart(root_dir, name_tpl);
   }

   void Restart(
      const char* root_dir,   // �������� "C:\WINDOWS" ��� "\\server\d\backup\" ��� "..\.."
      const char* name_tpl = "*.*" 
               )
   {
      szReply[0]=0;
      strcpy( szNameTpl, name_tpl ); 
      strcpy( szDir, root_dir);
      int n=strlen(szDir);
      if (n && szDir[n-1]=='\\')
         szDir[n-1]=0; // ������� ���� � �����
      Restart();
   }

   operator char * (void) const
   {
      return (szReply[0]) ? szReply : NULL;
   }


   XEnumDirsRecursive& operator ++(void) // prefix form:  use '++xed' to get next subdirectory
   {
      if (szReply[0] && pxedr == NULL) // �� ���������� ���� ����� �����, �� ������ ��� �� ����������
      {
         nDir = strlen( szDir ); // ���������� ����� ���������� ��� ������������ ��������������
         strcpy( szDir, szReply );
         pxedr = new XEnumDirsRecursive();
         pxedr->Restart();
         if (*pxedr) // ������ ���� ���� �������������, "����� �����!"
            return *this;
      }
      else if (pxedr != NULL) // �� � �������� ������������ ��������� �������������
      {
         ++(*pxedr); // �������� ���������� ������ ���
         if (*pxedr) // ������
            return *this;
      }

      if (pxedr)
      {  // ������������ ���� ������������� ����������� 
         delete pxedr;
         pxedr = NULL;
         szDir[nDir] = 0; // ��������������� ��� ����������
      }

      if (!xed) // ������������ � ������� ���������
         return *this;

      // ����, ������������ � ������� �� ���� ��������� 
      ++xed; // ����� ��������� ������������� � �������
      if (!xed) // ������ ������ ���
      {
         szReply[0]=0;
         return *this;
      }

      // ����, ����� ����� ������������� �� ������ ������, 
      // ������ �� � �����
      sprintf(szReply, "%s\\%s", szDir, xed.SafeStr());
      return *this;
   }

   ~XEnumDirsRecursive(void)
   {
      if (pxedr) // ���������� ��������� �������������
      {
         delete pxedr;
         pxedr = NULL;
      }
   }
};

#ifdef XEDR_INSTANTIATE   // turn on once per application or dll
char XEnumDirsRecursive::szReply[260]={0};         // ����� ��� ������������ �������� ������
char XEnumDirsRecursive::szNameTpl[260]={0};       // ������ �����, ����. "*.*"
char XEnumDirsRecursive::szDir[260]={0};           // ����������� ���������� ��� ����� �� �����
#endif XEDR_INSTANTIATE

class XFindFileRecursive
{
   XFindFile xff;             // ������������� ������ � ����������
   XEnumDirsRecursive xedr;   // ������������� ��������� �������������
   XPath xpReply;             // ��������� �����
   XText<260> xtNameTpl;
   XPath xpCurDir;

public:
   XFindFileRecursive(void){};
   XFindFileRecursive( const char* root_dir, const char* name_template = "*.*")
      { Restart( root_dir, name_template );}

   XFindFileRecursive& Restart( const char* root_dir, const char* name_template = "*.*" )
   {
      xtNameTpl = name_template;
      xpCurDir = root_dir;
      xpCurDir.StripSlash();
      xff.Restart( XText<256>().sprintf( "%s\\%s", SafeStr(xpCurDir), (char*)xtNameTpl) ); // ������������� ��������� ����-�����
      xedr.Restart(xpCurDir, "*.*"); // �������������� ������ �������������
      while (!xff && xedr) // � ������� ������������� ������ ���, �� ���� ������ �������������
      {
         xff.Restart(  XText<256>().sprintf( "%s\\%s", SafeStr(xedr), (char*)xtNameTpl ) ); // �������� ��������� ��������� ����-�����
         xpCurDir = SafeStr(xedr);
         ++xedr; // �������������� ��������� �������������
      }
      if (xff)
         xpReply.sprintf("%s\\%s", (char*)xpCurDir, SafeStr(xff));
      return *this;
   };


   operator char * (void) const { return (xpReply[0]) ? (char*)xpReply : NULL; }

   XFindFileRecursive& operator ++(void) // prefix form:  use '++xffr' to get next file
   {
      ++xff; // ��������� � ���������� �����
      while (!xff && xedr) // � ������� ������������� ����� ���������, �� ���� ������ �������������
      {
         xff.Restart( XText<256>().sprintf( "%s\\%s", SafeStr(xedr), (char*)xtNameTpl ) ); // �������� ��������� ��������� ����-�����
         xpCurDir = SafeStr(xedr);
         ++xedr; // �������������� ��������� �������������
      }
      if (xff)
         xpReply.sprintf("%s\\%s", (char*)xpCurDir, SafeStr(xff));
      else
         xpReply[0]=0;
      return *this;
   }
   Bool  IsArchive () { return xff.IsArchive (); };//  Archive. Set whenever the file is changed, and cleared by the BACKUP command. Value: 0x20
   Bool  IsHidden  () { return xff.IsHidden  (); };//  Hidden file. Not normally seen with the DIR command, unless the /AH option is used. Returns information about normal files as well as files with this attribute. Value: 0x02
   Bool  IsNormal  () { return xff.IsNormal  (); };//  Normal. File can be read or written to without restriction. Value: 0x00
   Bool  IsReadOnly() { return xff.IsReadOnly(); };//  Read-only. File cannot be opened for writing, and a file with the same name cannot be created. Value: 0x01
   Bool  IsSubdir  () { return xff.IsSubdir  (); };//  Subdirectory. Value: 0x10
   Bool  IsSystem  () { return xff.IsSystem  (); };//  System file. Not normally seen with the DIR command, unless the /A or /A:S option is used. Value: 0x04
};

#endif //__XFINDFIL_H