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

#pragma message(__FILE__"(1)")
#ifndef __GLOBUS_H
#define __GLOBUS_H

   #ifdef DEBUG_HDRS
      #pragma message(__FILE__"(1) : START ")
   #endif

   #include "cttypes.h"    // portable basic types
   #include "err16.h"      // common use error values

/*** Modifiers ***/
   /*
      Here we define next call modifiers:
      CLA_IMPO    -  class imported from DLL
      CLA_EXPO    -  class exported from DLL
      FUN_IMPO( ret_type ) - function imported from DLL
      FUN_EXPO( ret_type ) - function exported from DLL
         ret_type - function return type
      PASCAL - pascal type of arguments retrieval
      CDECL  - C type of arguments retrieval (stack based)
      FAR - pointer & function call modifier

      Usage of modifiers:
         // imported from DLL class in context of class user:
         class CLA_IMPO SomeClass {...};
         // exported from DLL class in context of it's definition:
         class CLA_EXPO SomeClass {...};

         // exported from DLL functions in context of definition one:
         FUN_EXPO( char* ) SomeFunc1() {...};
         FUN_EXPO( char* ) PASCAL SomeFunc2() {...};
         // imported from DLL functions prototypes in context of usage:
         FUN_IMPO( char* ) SomeFunc1();
         FUN_IMPO( void  ) FAR PASCAL SomeFunc2();
   */

   #if      defined( __BORLANDC__ )    /* Borland C++ 3.1 **************/
      #define CLA_IMPO    _huge
      #define CLA_EXPO    _export
      #define FUN_IMPO__
      #define __FUN_IMPO            _far
      #define FUN_EXPO__
      #define __FUN_EXPO            _far _export
      #ifndef PASCAL
         #define PASCAL _pascal
      #endif
      #ifndef FAR
         #define FAR _far
      #endif
      #ifndef HUGE
         #define HUGE huge
      #endif
   	#ifndef NEAR
         #define NEAR      _near
        #endif
      #ifndef CDECL
         #define CDECL      _cdecl
      #endif
   #elif    defined( _MSC_VER )        /* Microsoft C/C++ compilers ******/
      #if  _MSC_VER > 800    /* MSVC 2.0 and later */
         #ifdef DEBUG_HDRS
            #pragma message( "Globus.h: make settings for MSVC 2.0 or later")
         #endif
         #define CLA_IMPO    __declspec( dllimport )
         #define CLA_EXPO    __declspec( dllexport )
         #define FUN_IMPO__  __declspec( dllimport )
         #define __FUN_IMPO
         #define FUN_EXPO__  __declspec( dllexport )
         #define __FUN_EXPO
         #ifndef PASCAL
            #define PASCAL __stdcall
            #ifdef DEBUG_HDRS
               #pragma message( "PASCAL->__stdcall")
            #endif
         #endif
         #ifndef FAR
            #define far
            #define FAR far
            #ifdef DEBUG_HDRS
               #pragma message( "FAR->far-><none>")
            #endif
         #endif
      	#ifndef NEAR
            #define near
            #define NEAR near
            #ifdef DEBUG_HDRS
               #pragma message( "NEAR->near-><none>")
            #endif
	      #endif
         #ifndef HUGE
            #define HUGE
            #ifdef DEBUG_HDRS
               #pragma message( "HUGE-><none>")
            #endif
         #endif
      #elif _MSC_VER == 800  /* MSVC 1.5 *********************************/
         /* ??
         #define CLA_IMPO    __declspec( dllimport )
         #define CLA_EXPO    __declspec( dllexport )
         */
         #define FUN_IMPO__
          #define __FUN_IMPO  __far _pascal
         #define FUN_EXPO__
          #define __FUN_EXPO  __far _pascal __export
         #ifndef PASCAL
            #define PASCAL _pascal
         #endif
         #ifndef FAR
            #define FAR     __far
         #endif
         #ifndef NEAR
            #define NEAR    __near
         #endif
         /*
         #ifndef HUGE
         #define HUGE
         #endif
         */
      #else    /* common definitions for all MS compilers */
         #ifndef CDECL
            #define CDECL      __cdecl
         #endif
      #endif
   #else /* unknown compiler ******************************************/
         #define CLA_IMPO
         #define CLA_EXPO
         #define FUN_IMPO__
         #define __FUN_IMPO
         #define FUN_EXPO__
         #define __FUN_EXPO
         #ifndef PASCAL
            #define PASCAL
         #endif
         #ifndef FAR
            #define FAR
         #endif
         #ifndef HUGE
            #define HUGE
         #endif
         #ifndef CDECL
            #define CDECL
         #endif
   #endif
   /*********************************************************/
   #define FUN_IMPO( ret_type )  FUN_IMPO__ ret_type __FUN_IMPO
   #define FUN_EXPO( ret_type )  FUN_EXPO__ ret_type __FUN_EXPO
   /*********************************************************/
   #ifdef DEBUG_HDRS
      #pragma message(__FILE__"(1) : FINISH ")
   #endif

#endif /* __GLOBUS_H */
