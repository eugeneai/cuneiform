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

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#define _DEFAULTMODE 0
#define _VRES16COLOR 1
void _setvideomode (int mode);
#define _GCLEARSCREEN 0
void _clearscreen (int mode);
void _setcolor (int color);
#define _GFILLINTERIOR 0
#define _GBORDER 1
//#define _GPIXELBORDER _GBORDER
//#define _GSCREENBORDER 2
void _rectangle (int t,int left,int top,int right,int bottom);
void _getfillmask (char * OldMask);
void _setfillmask (char * OldMask);
void _moveto (int x,int y);
void _lineto (int x,int y);
void _setlinestyle (int style);

struct textsettings {
	int height;
	int width;
};
void _gettextsettings (struct textsettings *ts);
#define _RIGHT 0
#define _TOP 1
#define _CENTER 2
#define _HALF 3
void _settextalign (int right,int top);
void _setcharsize (int n1, int n2);
void _grtext (int x, int y, const char * text);
unsigned _getlinestyle ();
void break_point_data (char * c);
void write_prot ();
BOOL snapAutofont(BYTE a); // Andrew Theer
int LT_Getch (void);
// 16.10.2001 (George Fedorov)
// 16 ������ � �������, �������� DOS (��. ���� � MENUCOLOR )
   #define	_COLOR_BLACK	     0   // ������
   #define	_COLOR_DBLUE       1   // �����-�����
   #define	_COLOR_DGREEN      2   // �����-�������
   #define	_COLOR_DCYAN       3   // �����-��������� (dark cyan)
   #define	_COLOR_DRED 	     4   // �����-�������
   #define	_COLOR_DMAGENTA 	 5   // �����-������� (/���������/����������)
   #define	_COLOR_BROWN  		 6   // ����������
   #define	_COLOR_GRAY   		 7   // ������-�����
   #define	_COLOR_DGRAY  		 8   // �����-�����
   #define	_COLOR_BLUE   		 9   // �����
   #define	_COLOR_GREEN  		 10  // ����-�������
   #define	_COLOR_CYAN   		 11  // ������-���������
   #define	_COLOR_RED    		 12  // ����-�������
   #define	_COLOR_MAGENTA		 13  // ��������� (/�������)
   #define	_COLOR_YELLOW 		 14  // ������
   #define	_COLOR_WHITE  		 15  // �����

#define _COLOR_BACKGROUND _COLOR_DMAGENTA
#define _COLOR_TEXT       _COLOR_DCYAN

#endif // #ifndef __GRAPHICS_H__
