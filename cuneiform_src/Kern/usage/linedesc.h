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

/**********  ���������  **********/
/*  Author     :  Alexander Mikhailov                                        */
/*  Last Edit  :  09.12.98                                                   */
/*  Source     :  'LineDesc.H'                                               */
/*  ���������� :  ��������� � ������� ������������.                          */
/*  ���������� :  �������� ������� (��� ���������� ����������) ����� ������. */
/*---------------------------------------------------------------------------*/
#include "cttypes.h"
/*---------------------------------------------------------------------------*/
typedef enum
{// ������ ������� ����������� �����
	RLT_LDIR_Horiz = 0,
	RLT_LDIR_Verti,
	RLT_LDIR_Kosa1,
	RLT_LDIR_Kosa2
}RLT_LINEDIR_TYPE;

typedef struct tagRLT_LINEATDIR
{// � ������ ����������� - �� ������� "RLT_LINEDIR_TYPE"
	int   nLine;           // ����� ����� 
	int   nLongLine;       // ����� ������� �����
	int   nLongNoAtPool;   // ����� ������� �����, �������������� ����
	int   nShortContrPool; // ����� �������� �����, �������������� ����
	int   SkewPool;        // ����������� ���� ����
	int   WeightSkew;      // ������ �� ����� ������� �� ���� (� ��������)
	int   LightSkew;       // �������������� ������� (� pro2miles)
}RLT_LINEATDIR;

typedef struct tagRLT_LINE
{
	/*  primary values  */
	Point16  Beg;
	Point16  End;
	int      Wid;
	Int16    nSeg;
	Word8    Plot;
	/*  derivative values  */
	int      Len;
	int      Skew;
	int      Skew2Delta;  // ������ ������� ��������� ��������� ����
	/*  decision about line  */
#define    RLT_LT_Initial      0x00
#define    RLT_LT_Vertic       0x01
#define    RLT_LT_Kosaya       0x02
	/***   V & !K : ������������    :  90' - 22.5' < Skew <  90' + 22.5'  ***/
	/***  !V & !K : ��������������  :   0' - 22.5' < Skew <   0' + 22.5'  ***/
	/***   V &  K : �����-1�������� :  45' - 22.5' < Skew <  45' + 22.5'  ***/
	/***  !V &  K : �����-2�������� : 135' - 22.5' < Skew < 135' + 22.5'  ***/
#define    RLT_LT_SkewConflict 0x04
	/***   ������������ �� ���� ���� "������" ����������  ***/
#define    RLT_LT_Long         0x08
	/***   ������� �����  ***/
#define    RLT_LT_Line         0x10
	/***   �����  ***/
#define    RLT_LT_Ssel         0x20
	/***   ����� ������  ***/
#define    RLT_LT_Pointed      0x40
	/***   �������  ***/
#define    RLT_LT_Doubt        0x80
	/***   ����� ������ ������� ����������  ***/
	char   Type;
}RLT_LINE;

typedef struct tagRLT_LINEPOOL
{
	RLT_LINEATDIR  Pool[4];
	int      nLine;
	RLT_LINE  *pLine;
}RLT_LINEPOOL;
/*---------------------------------------------------------------------------*/
void AnalOfMyLines (RLT_LINEPOOL *pLinePool, const Int32 Skew);
RLT_LINEDIR_TYPE LineSect (const char Type);
bool FindLinesReg ( const void *p_vB, Rect16 *pRcLin,  const Int32 SkewReg);
