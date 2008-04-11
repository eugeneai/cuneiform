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


/****************************************************************
*  This is Extention code of ED format.
*
*   Piter 01.08.96
*****************************************************************/
#ifndef __EDEXT__
#define __EDEXT__

#include "ctp.h"

#define SS_EXTENTION	0x1C

#pragma pack(push,1) 
struct edExtention
{
	Word8/*unsigned char   */  	code;   /* always SS_EXTENTION <0x1C> */
	Word16/*unsigned short int*/      Ecode;  /* New extention code */
	Word16/*unsigned short int*/      length; /* Length in bytes */
};
struct edExtentionNew
{
	Word8/*unsigned char   */  	code;   /* always SS_EXTENTION <0x1C> */
	Word16/*unsigned short int*/      Ecode;  /* New extention code */
	Word32/*unsigned short int*/      length; /* Length in bytes */
};
/* This structure is header all structs included in extention ED */
typedef struct edExtention EDEXT;

/* DESCRIPTIONS EXTENTION CODE */

/* 0x0000 - 0x00FF special code */
#define ITS_EDEXT_SPECIAL(a)   (a>=0x0000 && a<0x0100)
/* 0x0100 - 0x01FF table description */
#define ITS_EDEXT_TABLE(a)     (a>=0x0100 && a<0x0200)
/* 0x0200 - 0x02FF picture description */
#define ITS_EDEXT_PICTURE(a)   (a>=0x0200 && a<0x0300)
/* 0x0300 - 0xEFFF Your code please...*/

/* 0xF000 - 0xFFFF temporary code for debugging ( ! Not used in releas version !)*/

#define EDEXT_VERSION		0x0000

#define EDEXT_TABLE_START 	0x0100 // edTable struct
#define EDEXT_TABLE_VER         0x0101 // array horiz. coord of vert lines (x0,x1,...)
#define EDEXT_TABLE_HOR         0x0102 // array vert. coord of horiz. lines (y0,y1,...)
#define EDEXT_TABLE_TAB         0x0103 // array ID of items
#define EDEXT_TABLE_VERLINE     0x0104 // array not delete vert lines (x00,y00,x01,y01,...)

#define EDEXT_CTP	 	0x0200 // filename of CTP file
#define EDEXT_PICTURE           0x0201 // struct of <edPicture>
#define	EDEXT_TIFF_DESC	0x202	//��������� ��������� �����������

#define EDEXT_FONTS		0x300
#define EDEXT_BORDERS	0x301
#define EDEXT_SECTION	0x302
#define EDEXT_FRAME		0x303
#define EDEXT_PARAGRAPH 0x304
#define EDEXT_TABLE_ROW 0x305
//SS_EXTENTION ����� ���� 16 � 32 ����� ������� - ����� 32
#define EDEXT_PICS		(0x306|0x8000)
#define EDEXT_TABLE_CELL 0x307
#define EDEXT_CHAR		0x308
typedef struct sTable
{
 EDEXT 	  head;
 Int32      Sh;   	// count horizontal lines
 Int32      Sv;           // count vertical lines
 Int32      angle;        // angle of table 1/1024 rad
 Int32      VerCount;     // count not delete of vert lines
 Int32      ShiftX;       // shift tables in image
 Int32      ShiftY;       //
} edTable;

#define EDEXT_SIZE_FILENAME 256
#pragma pack(pop) 
#endif
