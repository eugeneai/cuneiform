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

/**********  Title  **********/
/*  Author     :  Alexander Mikhailov                                        */
/*  Last Edit  :  02.09.98 (Almi)                                            */
/*  Source     :  'Table.H'                                                  */
/*  Means      :  Macros and Structures                                      */
/*  Aim        :  Description of Tables                                      */

#ifndef __TABLE_H__
#define __TABLE_H__

/*---------------------------------------------------------------------------*/
#include "cttypes.h"
/*---------------------------------------------------------------------------*/
#define    MaxTableUsers       5
typedef enum
{
		TABLE_USER_COMMON = 0,
		TABLE_USER_RLTABLE,
		TABLE_USER_RBLOCK,
		TABLE_USER_CPAGE,
		TABLE_USER_RBTABLE
} NAMES_TABLE_USER;
/*---------------------------------------------------------------------------*/
typedef struct tagTABLE_LINE_DESC
{
        Int32   Level;
#define TLT_UnKnown       0x00 //- ������ �� ��������
#define TLT_Rough         0x01 //- ���������� �����, �� �������� ���������
#define TLT_UnSure        0x02 //- ������ ���� �� ��������
	char    Type;              // need types will be described
	char    reserv[3];
}TABLE_LINE_DESC;
typedef struct tagTABLE_LEVEL_DESC
{
	char    Type;              // need types will be described
	char    reserv[3];
}TABLE_LEVEL_DESC;
/*---------------------------------------------------------------------------*/
typedef enum
{
		TABLE_CELL_LEF = 0,  // Beg_X
		TABLE_CELL_RIG,      // End_X
		TABLE_CELL_TOP,      // Beg_Y
		TABLE_CELL_BOT       // End_Y
} SIDES_TABLE_CELL;
typedef struct tagTABLE_CELL_DESC
{
	char    TypeOwn;           // need types will be described
	char    TypeBound[4];      // ��� - ���������� ����������
	char    reserv[3];
}TABLE_CELL_DESC;
/*---------------------------------------------------------------------------*/
typedef struct tagTABLE_SPECIAL_PROPERTIES
{//������ ���������� ������ 'RLTABLE'
//	char    reserv[16]; - ����
	char    nSpecVertex;   // ���-�� ������ �����
	char    Hori[5];       // ����� ��������� �����.�����
	char    Vert[5];       // ����� ��������� �����.�����
#define    NON_CELL_VERTEX          0x01
	char    Type[5];       // �������� ����������� ����
}TABLE_SPECIAL_PROPERTIES;
/*---------------------------------------------------------------------------*/
#define    MaxHorLines        99
#define    MaxVerLines        50
#define    MaxCells          (MaxHorLines-1)*(MaxVerLines-1)
typedef struct tagTABLE_DESC
{
	/*  ��� ������ �������  */
	Rect32  RectFieldSearch;
	Int32   SkewFieldSearch;   // at what units?
	char    TaskTableSearch;   // need types will be described
	/*  ������������ �������  */
		/*  Key[USER] - ���� ������������ "USER" �� ��������� ��� ���������  */
	    /*  � ���� �������� ������. ���� ����� 0 - ��������� �� ��������.    */
	Word32  Key[MaxTableUsers];
	/*  ����� �������� �������  */
	Rect32  RectTable;         // ��� - ���������� ����������
	Int32   SkewTable;         // at what units?
	char    LifeTable;         // need types will be described
	int     nHorLines;
	int     nVerLines;
	int     nCell;             // ��� - ���������� ���������� [(nH-1)*(nV-1)]
	/*  �������� ������� ����������� ��������� �������  */
	TABLE_LINE_DESC    HorLine [MaxHorLines];
	TABLE_LINE_DESC    VerLine [MaxVerLines];
	TABLE_LEVEL_DESC   HorLevel[MaxHorLines-1];
	TABLE_LEVEL_DESC   VerLevel[MaxVerLines-1];
	/*  �������� ������ ����������� ��������� �������  */
#define    CELL_BOUND_PSEVDO          0x01
	char    TypeHorBound[MaxHorLines*MaxVerLines];
	char    TypeVerBound[MaxHorLines*MaxVerLines];
	TABLE_CELL_DESC       Cell [MaxCells];
	/*  ������  */
	TABLE_SPECIAL_PROPERTIES   SpecProp;
	char    iSet; //����� ����, ��������
#define TTD_None          0x00 //- �������, � ���� ��� ����
#define TTD_AsInImage     0x01 //- �������
#define TTD_ByLogic       0x02 //- �������
#define TTD_Maximal       0x03 //- ����������� ���������
        char    TypeTablDetail; // ��� �����������
        char    Active; // 0 - ���������, 1 - �������� � ����
	char    reserv[253];
} TABLE_DESC;
/*---------------------------------------------------------------------------*/
#endif
