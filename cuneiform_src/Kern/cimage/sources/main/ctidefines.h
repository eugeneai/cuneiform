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

# ifndef __CTIMAGE_DEFINES_H_
# define __CTIMAGE_DEFINES_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
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
         _SETTYPES( cls );
#else   /* not __cplusplus */
      #define _SETTYPES( name )                        \
         typedef const name         C##name;           \
         typedef name            *  P##name;           \
         typedef const name      *  PC##name;
#endif

typedef char                   Char8  ;   _SETTYPES( Char8  )
//      unicode char
typedef unsigned short         Char16 ;   _SETTYPES( Char16 )

#undef  _SETTYPES
/*
# define    CTIBOOL16          Bool16
# define    CTIWORD            Word16
*/
#define     CIMAGE_MAX_IMAGE_NAME           256
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define     CIMAGE_RGBQUDSSIZE(a, b)        a += ( (0x0001 << b) * sizeof(CIMAGERGBQUAD) )
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# define    CIMAGE_EXTENDBYTES(a,b)         (((a) + (b) - 1)/(b))*(b)  
# define    CIMAGE_EXTENDBITS(a,b)          (((a) + ((b)*8) - 1)/((b)*8))*(b)  
# define    CIMAGE_DIB_EXT                  4
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# define    CIMAGE_INCH_TO_METER(a)         ( ( (a) / 2.54 ) * 100)
# define    CIMAGE_METER_TO_INCH(a)         ( ( (a) / 100 ) * 2.54 + 1)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
# define    CIMAGE_STRING_LENGHT(a)         strlen(a)
# define    CIMAGE_STRING_COPY(a,b)         strcpy(a,b)
# define    CIMAGE_STRING_N_COPY(a,b,c)     strncpy(a,b,c)
# define    CIMAGE_STRING_CAT(a,b)          strcat(a,b)
# define    CIMAGE_STRING_COMPARE(a,b)      strcmp(a,b)
# define    CIMAGE_ABS(a)                   abs(a)
# define    CIMAGE_MEMSET(a,b,c)            memset(a,b,c)
# define    CIMAGE_MEMCOPY(a,b,c)           memcpy(a,b,c)
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined DLL_PROCESS_ATTACH || !defined DLL_THREAD_ATTACH || !defined DLL_THREAD_DETACH || !defined DLL_PROCESS_DETACH
#define DLL_PROCESS_ATTACH 1    
#define DLL_THREAD_ATTACH  2    
#define DLL_THREAD_DETACH  3    
#define DLL_PROCESS_DETACH 0    
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef APIENTRY
# define APIENTRY     __stdcall
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined BOOL
typedef int                 BOOL;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined DWORD
typedef unsigned long       DWORD;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined LPVOID
typedef void                *LPVOID;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# endif //__CTIMAGE_DEFINES_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
