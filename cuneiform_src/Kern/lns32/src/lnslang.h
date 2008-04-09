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

#ifndef __LNSLANG_H
   #define __LNSLANG_H

#define LNS_DEBUG // normally commented

   #include <stddef.h>
   #include <stdlib.h>
   #include <string.h>

#ifdef LNS_DEBUG
      #include <stdio.h>
#endif

#if defined( WIN16 )
   #include "__mmove.h"
   #define MEMMOVE   __mmove   // long blocks copy
#else
   #define MEMMOVE	memmove
#endif

#ifdef PPS_MAC
   // #include ??? NewPtr/DisposPtr
   #define MALLOC(size) 	((void*)NewPtr(size))
   #define FREE(p)  	(DisposePtr((Ptr)p))
#else
   #include <malloc.h>
   #define MALLOC 	malloc
   #define FREE   	free
#endif

   #include "globus.h"
   #include "myassert.h"

   #define min( a, b) ((a) < (b) ? (a) : (b))
   #define max( a, b) ((a) > (b) ? (a) : (b))
   
   #define BERROR( err )   ( assert(0), (Err16)(err) )
   #define THE (*this)

   #define _LOWORD(l)      ((Word16)(l))
   #define _HIWORD(l)      ((Word16)((Word32)(l) >> 16))
   #define SWAPBYTES(w)    ((Word16)(((w)<<8) | (((Word16)(w))>>8)))
   #define SWAPLONG(l)     \
      ((( (Int32)SWAPBYTES(_LOWORD(l))) <<16) | ( (Int32)SWAPBYTES(_HIWORD(l))) )

#ifndef HUGE
   #define HUGE
#endif

#ifndef FAR
   #define FAR
#endif

#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

//*******************Rom*****************
struct RomBubble{
	Int32		Column;
	Int32		Begin;
	Int32		End;
	RomBubble* next;
};
//***************************************

#endif
