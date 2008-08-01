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

# ifndef __CRIMAGE_DEFINES_H_
# define __CRIMAGE_DEFINES_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//

//# define    Char8               char
//# define    PChar8              char *
/*
# define    CTIBOOL16          Bool16
# define    CTIWORD            Word16
*/
#define     RIMAGE_MAX_IMAGE_NAME           256
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define     RIMAGE_RGBQUDSSIZE(a, b)        a += ( (0x0001 << b) * sizeof(RIMAGERGBQUAD) )
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# define    RIMAGE_EXTENDBYTES(a,b)         (((a) + (b) - 1)/(b))*(b)
# define    RIMAGE_EXTENDBITS(a,b)          (((a) + ((b)*8) - 1)/((b)*8))*(b)
# define    RIMAGE_DIB_EXT                  4
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# define    RIMAGE_INCH_TO_METER(a)         ( ( (a) / 2.54 ) * 100 )
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
# define    RIMAGE_STRING_LENGHT(a)         strlen(a)
# define    RIMAGE_STRING_COPY(a,b)         strcpy(a,b)
# define    RIMAGE_STRING_N_COPY(a,b,c)     strncpy(a,b,c)
# define    RIMAGE_STRING_CAT(a,b)          strcat(a,b)
# define    RIMAGE_STRING_COMPARE(a,b)      strcmp(a,b)
# define    RIMAGE_ABS(a)                   abs(a)
# define    RIMAGE_MEMSET(a,b,c)            memset(a,b,c)
# define    RIMAGE_MEMCOPY(a,b,c)           memcpy(a,b,c)
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
#ifdef WIN32
# define APIENTRY     __stdcall
#endif
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined BOOL
typedef int                 BOOL;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
# endif //__CRIMAGE_DEFINES_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
