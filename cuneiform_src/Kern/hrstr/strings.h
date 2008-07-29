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


/****************************************************************************
 *                                                                          *
 *                                                                          *
 *              S T R I N G S   E X T R A C T I O N                         *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              STRINGS.H - the header file                                 *
 *                                                                          *
 ***************************************************************************/

# ifndef __STRINGS_H_INCLUDE
# define __STRINGS_H_INCLUDE

# include "ltconfig.h"
# include "nt_types.h"

struct _String;
typedef struct _String STRING;

/* Flags of string */

# define SF_NULL                       0x00

/* Internal flags */

# define SF_RECT_ACCOUNTED             0x01
# define SF_REPRESENTATION_ACCOUNTED   0x02
# define SF_NEED_UPDATE                0x04
# define SF_NEED_DELETE                0x08
# define SF_DONT_VBREAK                0x10

/* External flags */

# define SF_SPECIAL                    0x20
# define SF_VERTCUT                    0x40

struct _String
       {
           STRING *pNext;
           STRING *pPrev;

           STRING *pUp;
           STRING *pDown;

           unsigned uFlags;
           BYTE     language; // Pit 02-??-94
           int      nBlock;
	   int      nUserNum;// Piter 08-17-95 06:18pm

           int      xLeft;
           int      yTop;
           int      xRight;
           int      yBottom;

           WORD     wFirst;
           WORD     wLast;

           int      *pLettersList;
           int      nLetters;

           int      *pDustList;
           int      nDust;

           int      nRecognized;
           int      nSpecialsLetters;

           int      nMiddleHeight;

           int      yMiddleTop;
           int      yMiddleLine;
           int      yMiddleBottom;

           int      nTopDispersion;
           int      nBottomDispersion;

           int      yMin;
           int      yMax;
       };

# define String Tiger_String

extern STRING String;
extern BOOL bNeedFreeString;

extern STRING *pStringsList;
extern STRING *pStringsListEnd;
extern STRING *pStringsUpList;
extern STRING *pStringsDownList;
# endif
