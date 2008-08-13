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

#ifndef __CPAGETYPS_H__
#define __CPAGETYPS_H__

#include "table.h"
#include "polyblock.h"


// PAGES
#define PT_EMPTY    CPAGE_GetInternalType("__Page__")
#define PT_PAGEINFO CPAGE_GetInternalType("__PageInfo__")

typedef struct {
	Int8	szImageName[CPAGE_MAXNAME];// ��� ����� ��������������� ����������� � ���������� RIMAGE
	Word32	Page; // ����� ��������
	Word32	DPIX;
	Word32	DPIY;
	Word32	BitPerPixel;
	Int32	X; // �������� ������������ ���������� ���������
	Int32	Y;
	Word32	Width; // ������� � ��������
	Word32	Height;
	Int32	Incline2048; // ������ �������� � ����� �� 2048
	Word32  Angle;// ���� �������� �������� 0, 90, 180, 270
	Int32   SkewLocVerLin2048;//������������ ���������� � ����� 2048
#define IMAGE_USER		1
#define IMAGE_BINARIZE  2
#define IMAGE_DELLINE	4
#define IMAGE_ROTATE	8
#define IMAGE_ORTOMOVE  16
#define IMAGE_TURN		32
	Word16   Images;//������������ �����������
	Word32	status;
#define PINFO_USERTEMPLATE	1;	// �������� ���������� �������������
#define PINFO_AUTOTEMPLATE	2;	// �������� ���������� �������������
} PAGEINFO;
typedef PAGEINFO * LPPAGEINFO;

#define CreateEmptyPage() CPAGE_CreatePage(PT_EMPTY,NULL,0)
#define CreatePageWithPageInfo(a) CPAGE_CreatePage(PT_PAGEINFO,&a,sizeof(a))
#define GetPageInfo(a,b) CPAGE_GetPageData(a,PT_PAGEINFO,b,sizeof(*b))
#define SetPageInfo(a,b) CPAGE_SetPageData(a,PT_PAGEINFO,&b,sizeof(b))


// BLOCKS

#define	BT_EMPTY CPAGE_GetInternalType("__Block__")
#define	BT_TABLE CPAGE_GetInternalType("__Table__")

#define CreateEmptyBlock(a) CPAGE_CreateBlock(a,BT_EMPTY,0,0,NULL,0)
#define CreateBlockNumber(a,b) CPAGE_CreateBlock(a,BT_EMPTY,b,0,NULL,0)

#define TYPE_CPAGE_TABLE	CPAGE_GetInternalType("TYPE_CPAGE_TABLE")
#define TYPE_CPAGE_PICTURE	CPAGE_GetInternalType("TYPE_CPAGE_PICTURE")

typedef struct tagCellInfo
{
	Int32	Number; // ����� ������ ���������� ������� ( ������� � 1 )
	Point32 PhCoord;// ���������� �������� � ���������� ������
	Int32   Block;  // ����� ���������
	Int32	GeCount;// ����� �������������� �����, �������� � ����������
	Word32	wFlags[16];// ������
	Int32   reserv[48];

} CellInfo;

typedef struct tagCPAGE_TABLE
{
	TABLE_DESC	prop; // �������� ���������� � �������
	CellInfo	cell[MaxHorLines-1][MaxVerLines-1];// ����� ���������������
	Word32      PhNumber; // ����� ���������� �����
	Word32		wFlags[16];// ������


} CPAGE_TABLE;

#define CPAGE_MAXCORNER  1000

typedef struct tagCPAGE_PICTURE
{
	Word16  Number;
	Point32 Corner[CPAGE_MAXCORNER];

} CPAGE_PICTURE;

#endif
