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

#include "internal.h"
#pragma hdrstop

#include <stdarg.h>

#include "std.h"

#ifdef WIN32
   #include <wingdi.h>
   #include <winuser.h>
#endif
   FILE *gStdOutputFile = 0;

static FTConsole _ConsoleHandler = NULL;
STD_FUNC( void ) stdSetConsoleHandler( FTConsole handler )
{
   _ConsoleHandler = handler;
}

static char _ConsoleFileName[256]={0};
STD_FUNC( void ) stdSetConsoleFile( char * file_name )
{
   _ConsoleFileName[0]=0;
   if (file_name)
      strcpy( _ConsoleFileName, file_name );
}

STD_FUNC( int ) stdConsole( char* str, ... )
{
   if (str==NULL) return 0;
   int count=0;

   char strbuf[4096];   // string to be put
   strbuf[0]='\n';
   //////////////////////////////////
   // external handler? - make string and pass it to handler
   if (_ConsoleHandler != NULL)
   {
      #if defined(__BORLANDC__)
         count=vsprintf( strbuf, str, (...) );
      #else
         {  va_list list;
            va_start(list, str );
            count=vsprintf( strbuf+1, str, list );
            va_end( list );
         }
      #endif
      return (*_ConsoleHandler)( strbuf );
   };

   //////////////////////////////////
   // internal handling
#if defined(__BORLANDC__)
   count=vsprintf( strbuf+1, str, (...) );
#else
   {  va_list list;
      va_start(list, str );
      count=vsprintf( strbuf+1, str, list );
      va_end( list );
   }
#endif
   char* res_str = strbuf[1]=='\n' ? strbuf+1 : strbuf;

#if defined( WIN32 )
   {
      if (res_str[0]!='\n')
         OutputDebugString("\n"); // cover MSVC Bug
      OutputDebugString(res_str);
   }
#endif

#if defined(__BORLANDC__)
      {  // send message to special window
			UINT mn = RegisterWindowMessage(CONSOLE_MESSAGE);
         SendMessage( HWND_BROADCAST,
                      mn,0,
                      (LONG)(res_str[0]=='\n' ?  res_str+1 : res_str )
						  );
      }
#endif

   if (_ConsoleFileName[0]!=0)
   {  // drop message to file
	   FILE *ff;
      #ifdef PPS_WIN
         AnsiToOem (res_str, res_str);
      #endif
      ff  = fopen (_ConsoleFileName, "a");
      if (ff)
      {  strcat(res_str,"\n");
         fprintf( ff, res_str);
         fclose (ff);
      }
   }
   return count;
} // stdConsole()

STD_FUNC( int ) stdConsole_( char* str, ... )   // ��� �������� ������
{
   if (str==NULL) return 0;
   int count=0;

   char strbuf[4096];   // string to be put
   strbuf[0]=0;
   //////////////////////////////////
   // external handler? - make string and pass it to handler
   if (_ConsoleHandler != NULL)
   {
      #if defined(__BORLANDC__)
         count=vsprintf( strbuf, str, (...) );
      #else
         {  va_list list;
            va_start(list, str );
            count=vsprintf( strbuf, str, list );
            va_end( list );
         }
      #endif
      return (*_ConsoleHandler)( strbuf );
   };

   //////////////////////////////////
   // internal handling
#if defined(__BORLANDC__)
   count=vsprintf( strbuf, str, (...) );
#else
   {  va_list list;
      va_start(list, str );
      count=vsprintf( strbuf, str, list );
      va_end( list );
   }
#endif
   char* res_str = strbuf;

#if defined( WIN32 )
   {
      if (res_str[0]!='\n')
         OutputDebugString("\n"); // cover MSVC Bug
      OutputDebugString(res_str);
   }
#endif

#if defined(__BORLANDC__)
      {  // send message to special window
			UINT mn = RegisterWindowMessage(CONSOLE_MESSAGE);
         SendMessage( HWND_BROADCAST,
                      mn,0,
                      (LONG)(res_str[0]=='\n' ?  res_str+1 : res_str )
						  );
      }
#endif

   if (_ConsoleFileName[0]!=0)
   {  // drop message to file
	   FILE *ff;
      #ifdef PPS_WIN
         AnsiToOem (res_str, res_str);
      #endif
      ff  = fopen (_ConsoleFileName, "a");
      if (ff)
      {  strcat(res_str,"\n");
         fprintf( ff, res_str);
         fclose (ff);
      }
   }
   return count;
} // stdConsole()

STD_FUNC(void) stdSetOutputFile ( FILE *theFile )
{
	gStdOutputFile = theFile;
}
