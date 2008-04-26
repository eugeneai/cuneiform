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
 *              LTBLGLUE.C - Blocks glueing                                 *
 *                                                                          *
 ***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "c_memory.h"
# include "layout.h"
#include "minmax.h"

# define MIN_GLUED_COLUMN_HEIGHTES_WIDTH    4

# define COLUMN_SHIFT_FLUCTUATION_DIVIDER  20
# define COLUMN_SHIFT_SMALL_FLUCTUATION    16

# define IsCrossedIntervals(a1, a2, b1, b2)  (!((a2) < (b1) || (b2) < (a1)))

static BOOL IsColumn (BLOCK *p, BLOCK *q)
{
    int x1, x2;
    int nWidth1, nWidth2;
    int nHeight1, nHeight2;
    int nFluctuation;
    BLOCK *r;

    if (p -> Rect.yTop > q -> Rect.yTop)
    {
        r = p;
        p = q;
        q = r;
    }

    if (p -> Rect.yBottom > q -> Rect.yTop)
        return (FALSE);

    nHeight1 =  p -> Rect.yBottom - p -> Rect.yTop + 1;
    nHeight2 =  q -> Rect.yBottom - q -> Rect.yTop + 1;

    if (! (((p -> uFlags & BF_GLUED_FROM_ONE_LINE_BLOCKS) ||
            nHeight1 < 3 * p -> nAverageHeight)
           &&
           ((q -> uFlags & BF_GLUED_FROM_ONE_LINE_BLOCKS) ||
            nHeight2 < 3 * q -> nAverageHeight)))
    {
        return (FALSE);
    }

    if (q -> Rect.yTop - p -> Rect.yBottom >
            3 * MIN (p -> nAverageHeight, q -> nAverageHeight))
    {
        return (FALSE);
    }

    x1       = (p -> Rect.xRight + p -> Rect.xLeft) / 2;
    x2       = (q -> Rect.xRight + q -> Rect.xLeft) / 2;
    nWidth1  =  p -> Rect.xRight - p -> Rect.xLeft + 1;
    nWidth2  =  q -> Rect.xRight - q -> Rect.xLeft + 1;

    if (nWidth1 < p -> nAverageHeight * MIN_GLUED_COLUMN_HEIGHTES_WIDTH ||
        nWidth2 < q -> nAverageHeight * MIN_GLUED_COLUMN_HEIGHTES_WIDTH)
    {
        return (FALSE);
    }

    nFluctuation = MAX (MAX (nWidth1, nWidth2)
                          / COLUMN_SHIFT_FLUCTUATION_DIVIDER,
                        COLUMN_SHIFT_SMALL_FLUCTUATION);

    if (abs (p -> Rect.xLeft  - q -> Rect.xLeft)  > nFluctuation &&
        abs (p -> Rect.xRight - q -> Rect.xRight) > nFluctuation &&
        abs (x1               - x2)               > nFluctuation)
    {
        return (FALSE);
    }

    for (r = pBlocksList; r != NULL; r = r -> pNext)
    {
        if (r == p ||
            r == q ||
            r -> Type == BLOCK_TEXT && r -> nRoots == r -> nDust)
        {
            continue;
        }

        if ((IsCrossedIntervals (p -> Rect.xLeft, p -> Rect.xRight,
                                 r -> Rect.xLeft, r -> Rect.xRight) ||
             IsCrossedIntervals (q -> Rect.xLeft, q -> Rect.xRight,
                                 r -> Rect.xLeft, r -> Rect.xRight))
             &&
             IsCrossedIntervals (p -> Rect.yTop, q -> Rect.yBottom,
                                 r -> Rect.yTop, r -> Rect.yBottom))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}

static BOOL IsIncorrectBreaking (BLOCK *p, BLOCK *q)
{
    BLOCK *r;

    if (! IsCrossedIntervals (p -> Rect.yTop, p -> Rect.yBottom,
                              q -> Rect.yTop, q -> Rect.yBottom))
    {
        return (FALSE);
    }

    if (p -> Rect.xLeft > q -> Rect.xLeft)
    {
        r = p;
        p = q;
        q = r;
    }

    if (p -> Rect.xRight > q -> Rect.xLeft)
        return (FALSE);

    if (q -> Rect.xLeft - p -> Rect.xRight >=
                MIN (p -> nConditionalMinColumnWidth,
                     q -> nConditionalMinColumnWidth))
    {
        return (FALSE);
    }

    if (bOptionBusinessCardsLayout &&
        (p -> nAverageHeight >= q -> nAverageHeight * 2 ||
         q -> nAverageHeight >= p -> nAverageHeight * 3))
    {
        return (FALSE);
    }

    for (r = pBlocksList; r != NULL; r = r -> pNext)
    {
        if (r == p ||
            r == q ||
            r -> Type == BLOCK_TEXT && r -> nRoots == r -> nDust ||
            r -> Type == BLOCK_HORZ_SEPARATOR)
        {
            continue;
        }

        if ((IsCrossedIntervals (p -> Rect.yTop, p -> Rect.yBottom,
                                 r -> Rect.yTop, r -> Rect.yBottom) ||
             IsCrossedIntervals (q -> Rect.yTop, q -> Rect.yBottom,
                                 r -> Rect.yTop, r -> Rect.yBottom))
             &&
             IsCrossedIntervals (p -> Rect.xLeft, q -> Rect.xRight,
                                 r -> Rect.xLeft, r -> Rect.xRight))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}

static BOOL IsIncorrectSmartBreaking (BLOCK *p, BLOCK *q)
{
    register ROOT *pRoot;
    register int xLeft   = q -> Rect.xLeft;
    register int xRight  = q -> Rect.xRight;
    register int yTop    = q -> Rect.yTop;
    register int yBottom = q -> Rect.yBottom;
    int nDistance1;
    int nDistance2;
    BOOL bNearRootFound;
    int nMinDistance;

    if (! (p -> uFlags & BF_SMART_BREAKING_APPLIED) &&
        ! (q -> uFlags & BF_SMART_BREAKING_APPLIED))
    {
        return (FALSE);
    }

    if (! RectIsCrossed (& p -> Rect, & q -> Rect))
        return (FALSE);

    if (p -> Rect.yBottom - p -> Rect.yTop + 1 < 3 * p -> nAverageHeight)
    {
        BLOCK *r;

        r = p;
        p = q;
        q = r;
    }
    else if (q -> Rect.yBottom - q -> Rect.yTop + 1 < 3 * q -> nAverageHeight)
    {
    }
    else
    {
        return (FALSE);
    }

    if (p -> nAverageHeight >= q -> nAverageHeight * 2 ||
        q -> nAverageHeight >= p -> nAverageHeight * 2)
    {
        return (FALSE);
    }

    bNearRootFound = FALSE;
    nMinDistance = MAX (p -> nAverageHeight, q -> nAverageHeight) * 4;

    for (pRoot = p -> pRoots; pRoot != NULL; pRoot = pRoot -> u1.pNext)
    {
        if (! IsCrossedIntervals (pRoot -> yRow,
                                  pRoot -> yRow + pRoot -> nHeight - 1,
                                  yTop,
                                  yBottom))
        {
            continue;
        }

        nDistance1 = xLeft - (pRoot -> xColumn + pRoot -> nWidth - 1);
        nDistance2 = pRoot -> xColumn - xRight;

        if (nDistance1 <= 0 && nDistance2 <= 0 ||
            nDistance1 <= 0 && nDistance2 < nMinDistance ||
            nDistance2 <= 0 && nDistance1 < nMinDistance)
        {
            bNearRootFound = TRUE;
            break;
        }
    }

    return (bNearRootFound);
}

BLOCK *BlocksGlueTwo (BLOCK *p, BLOCK *q)
{

    if (p -> pRoots == NULL || p -> pEndRoots == NULL ||
        q -> pRoots == NULL || q -> pEndRoots == NULL)
    {
        ErrorInternal ("Empty blocks list in BlocksGlueTwo");
    }

    p -> pEndRoots -> u1.pNext = q -> pRoots;
    p -> pEndRoots          = q -> pEndRoots;

    RectAsgPlus (&(p -> Rect), &(q -> Rect));

    p -> nRoots       += q -> nRoots;
    p -> nLetters     += q -> nLetters;
    p -> nDust        += q -> nDust;
    p -> nHeightesSum += q -> nHeightesSum;

    BlockSetAverageHeight (p);
    BlockReCalculateBreakingParameters (p);
    BlocksRemoveDescriptor (q);

    return (p);
}


# define CANT_KNOWINGLY(p, q)     (p == q                             || \
                                   p -> Type != BLOCK_TEXT            || \
                                   q -> Type != BLOCK_TEXT            || \
                                   (p -> uFlags & BF_NOT_GLUE_BLOCK)  || \
                                   (q -> uFlags & BF_NOT_GLUE_BLOCK)  || \
                                   p -> nEmbedding != q -> nEmbedding)


/*
# define CANT_KNOWINGLY(p, q)     (p == q                             || \
                                   p -> Type != BLOCK_TEXT            || \
                                   q -> Type != BLOCK_TEXT            || \
                                   p -> nEmbedding != q -> nEmbedding)
*/


void BlocksGlue (void)
{
    BLOCK *p, *q;

    // Glue incorrect breakings

    for (p = pBlocksList; p != NULL; p = p -> pNext)
    {
        for (q = p -> pNext; q != NULL; q = q -> pNext)
        {
            if (CANT_KNOWINGLY (p, q))
                continue;

            if (IsIncorrectBreaking (p, q))
            {
                BlocksGlueTwo (p, q);
                q = pBlocksList;
            }
        }
    }

    // Glue columns

    for (p = pBlocksList; p != NULL; p = p -> pNext)
    {
        for (q = p -> pNext; q != NULL; q = q -> pNext)
        {
            if (CANT_KNOWINGLY (p, q))
                continue;

            if (IsColumn (p, q))
            {
                BlocksGlueTwo (p, q);
                p -> uFlags |= BF_GLUED_FROM_ONE_LINE_BLOCKS;
                q = pBlocksList;
            }
        }
    }

    // Glue incorrect breakings

    for (p = pBlocksList; p != NULL; p = p -> pNext)
    {
        for (q = p -> pNext; q != NULL; q = q -> pNext)
        {
            if (CANT_KNOWINGLY (p, q))
                continue;

            if (IsIncorrectSmartBreaking (p, q))
            {
                BlocksGlueTwo (p, q);
                q = pBlocksList;
            }
        }
    }
}
