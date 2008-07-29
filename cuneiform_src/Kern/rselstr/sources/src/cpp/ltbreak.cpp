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
 *                   P A G E   L A Y O U T                                  *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              LTBREAK.C - Blocks breaking                                 *
 *                                                                          *
 ***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "c_memory.h"
# include "layout.h"
# include "func.h"
# include "my_mem.h"

# include "dpuma.h"

extern Handle hNotWholeLine ;
extern Handle hHystogramNull ;
extern Word32 ZagolovokBreakingCoeff;


# define MIN_BREAKED_BLOCK_HEIGHTES_WIDTH  4
# define MAX_NARROW_COLUMN_DISTANCE        4
# define MAX_BULLET_DISTANCE               8

void BlockHorzHystogramBuild (BLOCK *p)
{
    int *pHystogram;
    int nHystColumns;

    ROOT *pRoot;
    int iTopColumn, iBottomColumn;
    int iColumn;
    int nSum;

    nHystColumns = p -> Rect.yBottom - p -> Rect.yTop + 1;

    pHystogram =(int*) malloc ((nHystColumns + 1) * sizeof (int));

    if (pHystogram == NULL)
        ErrorNoEnoughMemory ((Word8*)"in LTBREAK.C,BlockHorzHystogramBuild,part 1");

    memset (pHystogram, 0, (nHystColumns + 1) * sizeof (int));

    for (pRoot = p -> pRoots; pRoot != NULL; pRoot = pRoot -> u1.pNext)
    {
        if (IS_LAYOUT_DUST (* pRoot))
            continue;

        iTopColumn    = (pRoot -> yRow - p -> Rect.yTop);
        iBottomColumn = (pRoot -> yRow + pRoot -> nHeight - 1
                            - p -> Rect.yTop);

        pHystogram [iTopColumn] ++;
        pHystogram [iBottomColumn + 1] --;
    }

    nSum = 0;

    for (iColumn = 0; iColumn < nHystColumns; iColumn++)
    {
        nSum += pHystogram [iColumn];
        pHystogram [iColumn] = nSum;
    }

    p -> nActualHeight = 0;

    for (iColumn = 0; iColumn < nHystColumns; iColumn++)
    {
        if (pHystogram [iColumn] != 0)
            p -> nActualHeight++;
    }

    if (p -> pHorzHystogram != NULL)
    {
        free (p -> pHorzHystogram);
        p -> pHorzHystogram = NULL;
    }

    p -> pHorzHystogram = pHystogram;
}

void BlockCalculateBreakingParameters (BLOCK *p)
{
    int nBlockHeights;

    BlockHorzHystogramBuild (p);

    nBlockHeights = p -> nActualHeight / p -> nAverageHeight;

    switch (nBlockHeights)
    {
        case 0:
        case 1:
            p -> nStartColumnWidth            = p -> nAverageHeight * 4;
            p -> nUnconditionalMinColumnWidth = p -> nStartColumnWidth;
            p -> nConditionalMinColumnWidth   = p -> nStartColumnWidth;
            break;

        case 2:
        case 3:
        case 4:
        case 5:
            p -> nStartColumnWidth            = p -> nAverageHeight * 2;
            p -> nUnconditionalMinColumnWidth = p -> nStartColumnWidth;
            p -> nConditionalMinColumnWidth   = p -> nStartColumnWidth;
            break;

        case 6:
        case 7:
        case 8:
        case 9:
            p -> nStartColumnWidth            = p -> nAverageHeight;
            p -> nUnconditionalMinColumnWidth = p -> nStartColumnWidth;
            p -> nConditionalMinColumnWidth   = p -> nStartColumnWidth / 2;
            break;

        default:
            p -> nStartColumnWidth            = p -> nAverageHeight;
            p -> nUnconditionalMinColumnWidth = p -> nAverageHeight;
            p -> nConditionalMinColumnWidth   = p -> nAverageHeight / 4;
            break;
    }

    if (p -> nStartColumnWidth == 0)
        p -> nStartColumnWidth = 1;

    if (p -> nUnconditionalMinColumnWidth == 0)
        p -> nUnconditionalMinColumnWidth = 1;

    if (p -> nConditionalMinColumnWidth == 0)
        p -> nConditionalMinColumnWidth = 1;
}

