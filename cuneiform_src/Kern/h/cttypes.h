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

#ifndef __CTTYPES_H
#define __CTTYPES_H

#ifdef _MSC_VER

/*
MSVC does not come with stdint.h, even though it was standardized
way back in 1999. But what would you expect from the company that brought
you Internet Explorer?
*/

typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

typedef unsigned long intptr_t;

#else
#include <stdint.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/*** _SETTYPES() ***/
   #undef _SETTYPES
   #if defined( __cplusplus )
      #define _SETTYPES( name )                       \
         typedef const name         C##name;         \
         typedef name            *  P##name;         \
         typedef const name      *  PC##name;        \
         typedef name            &  R##name;         \
         typedef const name      &  RC##name;

      #define _SETCLASS( cls )       \
         class cls;                 \
         _SETTYPES( cls )
   #else   /* not __cplusplus */
      #define _SETTYPES( name )                        \
         typedef const name         C##name;           \
         typedef name            *  P##name;           \
         typedef const name      *  PC##name;
   #endif

/*** Base types ***/
   typedef unsigned int           Indx   ;   _SETTYPES( Indx   )
   typedef int32_t                Int32  ;   _SETTYPES( Int32  )
   typedef uint32_t               Word32 ;   _SETTYPES( Word32 )
   typedef int16_t                Int16  ;   _SETTYPES( Int16  )
   typedef uint16_t               Word16 ;   _SETTYPES( Word16 )
   typedef char                   Int8   ;   _SETTYPES( Int8   )
   typedef unsigned char          Word8  ;   _SETTYPES( Word8  )
   typedef float                  Float32;   _SETTYPES( Float32 )
   typedef double                 Float64;   _SETTYPES( Float64 )
   typedef long double            Float80;   _SETTYPES( Float80 )
   typedef int                    Bool   ;   _SETTYPES( Bool   )
   typedef int16_t                Bool16 ;   _SETTYPES( Bool16 )
   typedef int32_t                Bool32 ;   _SETTYPES( Bool32 )

   #ifndef   FALSE
      #define FALSE               0
   #endif
   #ifndef   TRUE
      #define TRUE                1
   #endif

#pragma pack(4)
/*** Derived types ***/
   typedef struct tagPoint16 { Int16 x,y; } Point16; _SETTYPES( Point16 )
   typedef struct tagPoint32 { Int32 x,y; } Point32; _SETTYPES( Point32 )
   typedef struct tagRect16 { Int16 left,top,right,bottom; } Rect16; _SETTYPES( Rect16 )
   typedef struct tagRect32 { Int32 left,top,right,bottom; } Rect32; _SETTYPES( Rect32 )
#pragma pack()
   //////////////////////////////
   // some of generic callbacks:
typedef void   (* FTVoid   )  ( void );
typedef void*  (* FTPVoid  )  ( void );
typedef Bool   (* FTBool   )  ( void );
typedef Bool16 (* FTBool16 )  ( void );
typedef Bool32 (* FTBool32 )  ( void );

typedef void   (* FTVoid_PVoid   )  ( void* );
typedef void*  (* FTPVoid_PVoid  )  ( void* );
typedef Bool   (* FTBool_PVoid   )  ( void* );
typedef Bool16 (* FTBool16_PVoid )  ( void* );
typedef Bool32 (* FTBool32_PVoid )  ( void* );

typedef void   (* FTVoid_Word32   )  ( Word32 );
typedef void*  (* FTPVoid_Word32  )  ( Word32 );
typedef Bool   (* FTBool_Word32   )  ( Word32 );
typedef Bool16 (* FTBool16_Word32 )  ( Word32 );
typedef Bool32 (* FTBool32_Word32 )  ( Word32 );

#ifdef __cplusplus
extern "C"
{
   typedef void   (* CFTVoid   )  ( void );
   typedef void*  (* CFTPVoid  )  ( void );
   typedef Bool   (* CFTBool   )  ( void );
   typedef Bool16 (* CFTBool16 )  ( void );
   typedef Bool32 (* CFTBool32 )  ( void );

   typedef void   (* CFTVoid_PVoid   )  ( void* );
   typedef void*  (* CFTPVoid_PVoid  )  ( void* );
   typedef Bool   (* CFTBool_PVoid   )  ( void* );
   typedef Bool16 (* CFTBool16_PVoid )  ( void* );
   typedef Bool32 (* CFTBool32_PVoid )  ( void* );

   typedef void   (* CFTVoid_Word32   )  ( Word32 );
   typedef void*  (* CFTPVoid_Word32  )  ( Word32 );
   typedef Bool   (* CFTBool_Word32   )  ( Word32 );
   typedef Bool16 (* CFTBool16_Word32 )  ( Word32 );
   typedef Bool32 (* CFTBool32_Word32 )  ( Word32 );
}
#endif   // __cplusplus

/* These definitions were originally scattered about the code tree.
 * Consolidating them all here.
 */

#ifdef WIN32

#include <windows.h>

#else

/* These elements are defined in Windows headers. */

typedef int32_t  LONG;
typedef uint32_t DWORD;

typedef uint16_t  WORD;
typedef uint32_t UINT;

typedef char* LPSTR;
typedef char* LPTSTR;
typedef const char* LPCSTR;
typedef const char* LPCWSTR;
typedef const char* LPCTSTR;

#endif

typedef int BOOL;

typedef char CHAR;
typedef char * PCHAR;

typedef unsigned char   BYTE;
typedef unsigned char * PBYTE;

typedef int16_t  SINT;

typedef LONG  * PLONG;
typedef DWORD * PDWORD;

typedef int16_t _INT;
typedef int16_t * _PINT;
#define INT  _INT
#define PINT _PINT
typedef WORD * PWORD;

typedef BYTE* LPBYTE;
typedef DWORD * LPDWORD;
typedef BOOL* LPBOOL;
typedef LONG* LPLONG;
typedef void* LPVOID;

#define PSTR  PCHAR

typedef unsigned long ULONG;

#include "cttypext.h"

#endif   // __CTTYPES_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
